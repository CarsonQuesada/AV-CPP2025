#include <rclcpp/rclcpp.hpp>
#include "rclcpp_components/component_manager.hpp"

int main(int argc, char ** argv) {
  rclcpp::init(argc, argv);
  auto exec = std::make_shared<rclcpp::executors::MultiThreadedExecutor>();
  auto manager = std::make_shared<rclcpp_components::ComponentManager>(exec);
  exec->add_node(manager);
  exec->spin();
  rclcpp::shutdown();
  return 0;
}