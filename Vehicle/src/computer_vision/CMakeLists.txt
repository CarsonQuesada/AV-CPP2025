cmake_minimum_required(VERSION 3.16)
project(computer_vision)

set(CMAKE_CXX_STANDARD 17)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)
find_package(rclcpp_components REQUIRED)

add_library(computer_vision_node SHARED
  src/computer_vision_node.cpp
)

target_include_directories(computer_vision_node PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

ament_target_dependencies(computer_vision_node
  rclcpp
  sensor_msgs
  std_msgs
  cv_bridge
  rclcpp_components
)

target_link_libraries(computer_vision_node
  ${OpenCV_LIBRARIES}
)

rclcpp_components_register_nodes(computer_vision_node "vehicle_core::ComputerVisionNode")

install(TARGETS computer_vision_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include
)

ament_package()