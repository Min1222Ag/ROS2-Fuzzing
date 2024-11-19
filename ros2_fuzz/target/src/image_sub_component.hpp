#ifndef COMPOSITION__IMAGE_SUB_COMPONENT_HPP_
#define COMPOSITION__IMAGE_SUB_COMPONENT_HPP_

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"

namespace composition
{

class ImageSubComponent : public rclcpp::Node
{
public:
  explicit ImageSubComponent(const rclcpp::NodeOptions & options);

private:
  void image_callback(const sensor_msgs::msg::Image::SharedPtr msg);
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_;
};

}  // namespace composition

#endif  // COMPOSITION__IMAGE_SUB_COMPONENT_HPP_

