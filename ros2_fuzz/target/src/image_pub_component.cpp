#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"  // 이미지 메시지 타입 포함

namespace composition
{

class ImagePubComponent : public rclcpp::Node
{
public:
  explicit ImagePubComponent(const rclcpp::NodeOptions & options)
  : Node("image_pub_component", options)
  {
    // 이미지 퍼블리셔 생성
    pub_ = this->create_publisher<sensor_msgs::msg::Image>("camera_image", 10);

    // 타이머로 주기적으로 퍼블리시
    timer_ = this->create_wall_timer(
      1s, std::bind(&ImagePubComponent::publish_image, this));
  }

private:
  void publish_image()
  {
    auto msg = std::make_unique<sensor_msgs::msg::Image>();
    msg->header.stamp = this->now();
    msg->header.frame_id = "camera_frame";
    msg->height = 480;  // 예시 높이
    msg->width = 640;   // 예시 너비
    msg->encoding = "rgb8";
    msg->is_bigendian = false;
    msg->step = msg->width * 3;

    // 데이터 배열 초기화 (임의의 이미지 데이터로 채움)
    msg->data.resize(msg->height * msg->step);

    RCLCPP_INFO(this->get_logger(), "Publishing image with resolution: %dx%d", msg->width, msg->height);

    pub_->publish(std::move(msg));
  }

  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

}  // namespace composition

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(composition::ImagePubComponent)

