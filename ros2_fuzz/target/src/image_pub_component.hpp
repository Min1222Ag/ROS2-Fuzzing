#ifndef COMPOSITION__IMAGE_PUB_COMPONENT_HPP_
#define COMPOSITION__IMAGE_PUB_COMPONENT_HPP_

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>

namespace composition
{

class ImagePubComponent : public rclcpp::Node
{
public:
  explicit ImagePubComponent(const rclcpp::NodeOptions & options);

private:
  void publish_image();
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  cv::VideoCapture cap_;
};

} // namespace composition 

#endif  // COMPOSITION__IMAGE_PUB_COMPONENT_HPP_

