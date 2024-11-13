#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>

using namespace std::chrono_literals;

namespace composition
{

class ImagePubComponent : public rclcpp::Node
{
public:
  explicit ImagePubComponent(const rclcpp::NodeOptions & options)
  : Node("image_pub_component", options)
  {
    // Create Image Publisher
    pub_ = this->create_publisher<sensor_msgs::msg::Image>("camera_image", 10);

    // Open Camera
    cap_.open(0);
    if (!cap_.isOpened()) {
      RCLCPP_ERROR(this->get_logger(), "Failed to open camera");
      return;
    }

    // Set Resolution
    cap_.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap_.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    RCLCPP_INFO(this->get_logger(), "Camera opened with resolution: 640x480");

    // Publishing Image every 100ms 
    timer_ = this->create_wall_timer(
      100ms, std::bind(&ImagePubComponent::publish_image, this));
  }

private:
  void publish_image()
  {
    cv::Mat frame;
    cap_ >> frame;  // Capture Frame
    if (frame.empty()) {
      RCLCPP_WARN(this->get_logger(), "Captured empty frame");
      return;
    }

    auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", frame).toImageMsg();

    RCLCPP_INFO(this->get_logger(), "Publishing image with resolution: %dx%d", frame.cols, frame.rows);

    pub_->publish(*msg);  //Publish
  }

  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  cv::VideoCapture cap_;
};

}

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(composition::ImagePubComponent)

