cmake_minimum_required(VERSION 3.5)
project(ros2_fuzz)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(OpenCV REQUIRED)
find_package(cv_bridge REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# add library & exe file
add_library(image_pub_component SHARED ./image_pub_component.cpp)
ament_target_dependencies(image_pub_component rclcpp rclcpp_components sensor_msgs OpenCV cv_bridge)
rclcpp_components_register_nodes(image_pub_component "composition::ImagePubComponent")

add_library(image_sub_component SHARED ./image_sub_component.cpp)
ament_target_dependencies(image_sub_component rclcpp rclcpp_components sensor_msgs cv_bridge)
rclcpp_components_register_nodes(image_sub_component "composition::ImageSubComponent")

add_executable(manual_composition ./manual_composition.cpp)
ament_target_dependencies(manual_composition rclcpp rclcpp_components)
target_link_libraries(manual_composition image_pub_component image_sub_component)

install(TARGETS
  image_pub_component
  image_sub_component
  manual_composition
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()

