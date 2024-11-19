#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <sstream>
#include <functional>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"


class dbinteract : public rclcpp::Node {
	public:
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub;
	rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub;

	/*
        before modification

	pub = this->create_publisher<std_msgs::msg::String>("dbquery", 10);
	sub = this->create_subscription<std_msgs::msg::String>(
	"dbreply", 10, std::bind(&dbinteract::print_reply, this, std::placeholders::_1)
	);
	*/

	dbinteract(const rclcpp::NodeOptions & options) : Node("dbinteract", options) {
            pub = this->create_publisher<std_msgs::msg::String>("dbquery", rclcpp::QoS(10));
            sub = this->create_subscription<std_msgs::msg::String>(
                "dbreply", rclcpp::QoS(10), [this](const std_msgs::msg::String::SharedPtr msg) {
                    RCLCPP_INFO(this->get_logger(), "Reply: %s", msg->data.c_str());
                    query(get_query());
                });
        }

	void query(const std::string & msg){
		std_msgs::msg::String output;
		output.data = msg;
		RCLCPP_INFO(this->get_logger(), "Sending: %s", msg.c_str());
		pub->publish(output);
	}

	void print_reply(const std_msgs::msg::String::SharedPtr msg){
		RCLCPP_INFO(this->get_logger(), "Reply: %s", msg->data.c_str());

		query(get_query());
	}

	std::string get_query(){
		std::stringstream qin;
		
		while(true){
			qin.str(std::string());

			std::cout << "Command 1: alloc" << std::endl;
			std::cout << "Command 2: free" << std::endl;
			std::cout << "Command 3: read" << std::endl;
			std::cout << "Command 4: write" << std::endl;
			std::cout << "Command 5: exit" << std::endl;

			std::cout << "Command: ";
			int cmd;
			std::cin >> cmd;
			qin << cmd;

			switch(cmd){
				case 1: {
					std::cout << "input alloc size: ";
					int size;
					std::cin >> size;

					qin << ' ' << size;
					goto do_send;
				} break;
				case 2: {
					std::cout << "input free index: ";
					int index;
					std::cin >> index;

					qin << ' ' << index;
					goto do_send;
				} break;
				case 3: {
					std::cout << "input directory (k, i): ";
					int k, i;
					std::cin >> k >> i;

					qin << ' ' << k << ' ' << i;
					goto do_send;
				} break;
				case 4: {
					std::cout << "input directory (k, i): ";
					int k, i;
					std::cin >> k >> i;

					std::cout << "input value: ";
					unsigned x;
					std::cin >> x;

					qin << ' ' << k << ' ' << i << ' ' << x;
					goto do_send;
				} break;
				case 5: { exit(0); } break;
				default: break;
			}

		}

		do_send:
		return qin.str();
	}
};

int main(int argc, char * argv[]){
	std::cout << "Server Starting" << std::endl;

	rclcpp::init(argc, argv);

	auto interactor = std::make_shared<dbinteract>(rclcpp::NodeOptions());
	interactor->query(interactor->get_query());
	rclcpp::spin(interactor);
	rclcpp::shutdown();
}
