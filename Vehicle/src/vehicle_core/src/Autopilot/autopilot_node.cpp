#include "vehicle_core/Autopilot/autopilot_node.hpp"
#include <chrono>

namespace vehicle_core {

    AutopilotNode::AutopilotNode(const rclcpp::NodeOptions& opts)
        : Node("autopilot_node", opts), pure_pursuit_(1.0) { 
        
        // Params
        control_rate_hz_ = this->declare_parameter<double>("control_rate_hz", 20.0);
        wheelbase_m_ = this->declare_parameter<double>("wheelbase_m", 1.0);
        kml_path_ = this->declare_parameter<std::string>("path_file", "");
        
        // Subscribers
        sub_odom_ = create_subscription<nav_msgs::msg::Odometry>(
            "/odometry/filtered", 10, std::bind(&AutopilotNode::onOdom, this, std::placeholders::_1));

        // Publishers
        pub_drive_ = create_publisher<vehicle_core::msg::InternalDriveCommand>(
            "/vehicle/internal_drive_cmd", 10);

        // Clients
        control_cb_group_ = this->create_callback_group(
        rclcpp::CallbackGroupType::MutuallyExclusive);
        cli_req_ = this->create_client<vehicle_core::srv::RequestInternalControl>(
            "/drive_arbiter/request_internal_control", rmw_qos_profile_services_default, control_cb_group_);
        cli_rel_ = create_client<vehicle_core::srv::ReleaseInternalControl>(
            "/drive_arbiter/release_internal_control");
        cli_notify_ready_ = create_client<std_srvs::srv::Trigger>(
            "/state_manager/mark_auto_ready");

        // Services
        srv_start_ = create_service<std_srvs::srv::Trigger>(
            "/autopilot/start", std::bind(&AutopilotNode::handleStart, this, std::placeholders::_1, std::placeholders::_2));
        srv_cancel_ = create_service<std_srvs::srv::Trigger>(
            "/autopilot/cancel", std::bind(&AutopilotNode::handleCancel, this, std::placeholders::_1, std::placeholders::_2));

        // Timers
        control_timer_ = create_wall_timer(
            std::chrono::duration<double>(1.0 / control_rate_hz_),
            std::bind(&AutopilotNode::generateDriveCommand, this));
        control_timer_->cancel(); // Start inactive

        pure_pursuit_ = PurePursuit(wheelbase_m_);
    }

    void AutopilotNode::onOdom(const nav_msgs::msg::Odometry::SharedPtr msg) {
        // Handle odometry message and update pure pursuit controller
        last_odom_ = msg;
        static bool first = true;
        if (first) {
            first = false;
            RCLCPP_INFO(
                get_logger(),
                "Autopilot: received first odom: position=(%.2f, %.2f)",
                msg->pose.pose.position.x,
                msg->pose.pose.position.y);
        }
    }

    void AutopilotNode::handleStart(
        const std::shared_ptr<std_srvs::srv::Trigger::Request> req,
        std::shared_ptr<std_srvs::srv::Trigger::Response> res) {
        if (startAutopilot()) {
            res->success = true;
            res->message = "Autopilot started";
        } else {
            res->success = false;
            res->message = "Failed to start autopilot";
        }
    }

    void AutopilotNode::handleCancel(
        const std::shared_ptr<std_srvs::srv::Trigger::Request> req,
        std::shared_ptr<std_srvs::srv::Trigger::Response> res) {
        stopAutopilot();
        res->success = true;
        res->message = "Autopilot stopped";
    }

    void AutopilotNode::generateDriveCommand() {
        if (!autopilot_active_ || !control_) {
            return;
        }

        auto odom = last_odom_;
        if (!odom) {
            RCLCPP_DEBUG_THROTTLE(
                get_logger(), *get_clock(), 2000,
                "No odometry yet, skipping control");
            return;
        }

        const auto & pose_msg = odom->pose.pose;
        double px = pose_msg.position.x;
        double py = pose_msg.position.y;

        const auto & q = pose_msg.orientation;
        double siny_cosp = 2.0 * (q.w * q.z + q.x * q.y);
        double cosy_cosp = 1.0 - 2.0 * (q.y * q.y + q.z * q.z);
        double yaw = std::atan2(siny_cosp, cosy_cosp);

        // Build PurePursuit pose
        Pose2D pose{px, py, yaw};

        // You should ideally get speed from odom->twist.twist.linear.x.
        // For now you can approximate with nominal speed:
        double current_speed = 2.0;

        Command cmd = pure_pursuit_.update(pose, current_speed);

        // If we’ve reached the goal, you might want to stop:
        if (cmd.reached_goal) {
            RCLCPP_INFO(get_logger(), "Pure pursuit reached goal, stopping autopilot");
            publishZero();
            stopAutopilot();
            return;
        }

        publishDrive(cmd.target_speed, cmd.steering_rad);
    }

    bool AutopilotNode::startAutopilot() {
        // Logic to start the autopilot
        cancel_ = false;
        ready_notified_ = false;

        if (!requestControl()) {
            RCLCPP_WARN(get_logger(), "Failed to obtain control for autopilot");
            return false;
        }

        if (kml_path_.empty()) {
            RCLCPP_WARN(get_logger(), "path_file parameter is empty");
            return false;
        }

        auto path = loader_.loadXY(kml_path_);
        if (path.empty()) {
            RCLCPP_WARN(get_logger(), "Failed to obtain path from file: %s", kml_path_.c_str());
            return false;
        }
        pure_pursuit_.setPath(path);

        notifyReady();
        control_timer_->reset();
        autopilot_active_ = true;
        return autopilot_active_;
    }

    void AutopilotNode::stopAutopilot() {
        // Logic to stop the autopilot
        releaseControl();
        ready_notified_ = false;
        control_timer_->cancel();
        cancel_ = true;
        autopilot_active_ = false;
    }

    bool AutopilotNode::requestControl() {
        using namespace std::chrono_literals;

        if (control_) {
            return true;  // already have control
        }

        if (!cli_req_->wait_for_service(5s)) {
            RCLCPP_WARN(get_logger(),
                        "requestControl: /drive_arbiter/request_internal_control not available");
            return false;
        }

        auto req = std::make_shared<vehicle_core::srv::RequestInternalControl::Request>();
        req->controller = controller_name_;

        auto future = cli_req_->async_send_request(req);

        // Now the response callback can run on a different thread,
        // because the client is in its own callback group.
        if (future.wait_for(5s) != std::future_status::ready) {
            RCLCPP_WARN(get_logger(), "requestControl: timeout waiting for DriveArbiter");
            return false;
        }

        auto resp = future.get();
        if (resp && resp->success) {
            control_ = true;
            RCLCPP_INFO(get_logger(), "[autopilot] control granted: %s",
                        resp->message.c_str());
        } else {
            std::string message = resp ? resp->message : "no response";
            RCLCPP_WARN(get_logger(), "[autopilot] control denied: %s", message.c_str());
            control_ = false;
        }

        return control_;
    }

    void AutopilotNode::releaseControl() {
        if (!control_) return;

        if (cli_rel_->wait_for_service(std::chrono::seconds(1))) {
            auto req = std::make_shared<vehicle_core::srv::ReleaseInternalControl::Request>();
            req->controller = controller_name_;
            (void)cli_rel_->async_send_request(req);
        } else {
            RCLCPP_WARN(get_logger(), "[heading] release service not available");
        }
        control_ = false;
    }

    void AutopilotNode::notifyReady() {
        if (ready_notified_) return;

        if (!cli_notify_ready_->wait_for_service(std::chrono::seconds(1))) {
            RCLCPP_WARN(get_logger(), "mark_auto_ready service not available");
            return;
        }

        auto req = std::make_shared<std_srvs::srv::Trigger::Request>();
        auto future = cli_notify_ready_->async_send_request(req,
            [this](rclcpp::Client<std_srvs::srv::Trigger>::SharedFuture f) {
                try {
                    auto resp = f.get();
                    if (resp && resp->success) {
                        RCLCPP_INFO(get_logger(), "StateManager: auto ready acknowledged");
                        ready_notified_ = true;
                    } else {
                        RCLCPP_WARN(get_logger(), "StateManager: auto ready rejected");
                    }
                } catch (const std::exception& e) {
                    RCLCPP_ERROR(get_logger(), "mark_auto_ready error: %s", e.what());
                }
            });
    }

    void AutopilotNode::publishDrive(double speed, double steer) {
        vehicle_core::msg::InternalDriveCommand m;
        m.stamp = now();
        m.controller = controller_name_;
        m.brake = 0;
        m.gear = 2; // Forward
        m.speed_mps = speed;
        m.steer_rad = steer;
        pub_drive_->publish(m);
    }

    void AutopilotNode::publishZero() {
        publishDrive(0.0, 0.0);
    }

} // namespace vehicle_core

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(vehicle_core::AutopilotNode)