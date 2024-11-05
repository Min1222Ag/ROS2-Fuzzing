#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"  // 이미지 메시지 타입 포함

namespace composition
{

class ImageSubComponent : public rclcpp::Node
{
public:
  explicit ImageSubComponent(const rclcpp::NodeOptions & options)
  : Node("image_sub_component", options)
  {
    // 이미지 구독자 생성
    sub_ = this->create_subscription<sensor_msgs::msg::Image>(
      "camera_image", 10,
      [this](const sensor_msgs::msg::Image::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "Received image with resolution: %dx%d", msg->width, msg->height);
      });
  }

private:
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_;
};

}  // namespace composition

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(composition::ImageSubComponent)

