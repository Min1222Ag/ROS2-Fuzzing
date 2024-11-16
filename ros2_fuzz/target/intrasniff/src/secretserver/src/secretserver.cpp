#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <sstream>
#include <functional>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class secretholder : public rclcpp::Node {
	public:
	rclcpp::TimerBase::SharedPtr timer;

	unsigned secret;

	secretholder(const rclcpp::NodeOptions & options) : Node("secretholder",options) {
		std::random_device rd;
		secret = rd();
		RCLCPP_INFO(this->get_logger(), "info: generated secret %u", secret);

		timer = this->create_wall_timer(std::chrono::seconds(1), [this]() {this->task();});
	}

	void task(){
		using packet_t = struct{
			std::string name;
			unsigned secret;
		};

		packet_t * p = new packet_t;
		p->name = "secretholder";
		p->secret = secret;

		/* assume some task is performed */
		RCLCPP_INFO(this->get_logger(), "info: task happened on pointer %p", (void *)p);

		delete p;
	}
};

/*
	database
	allocate data of fixed size
	read data 
	store data
*/
class database : public rclcpp::Node {
	public:
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub;
	rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub;

	std::vector<unsigned *> arrs;

	database(const rclcpp::NodeOptions & options) : Node("database",options) {
		pub = this->create_publisher<std_msgs::msg::String>("dbreply", rclcpp::QoS(10));
		sub = this->create_subscription<std_msgs::msg::String>(
				"dbquery", rclcpp::QoS(10), [this](const std_msgs::msg::String::SharedPtr msg){
					this->query(msg);
				});
	}
	~database(){
		for(auto arr : arrs) {
			delete[] arr;
		}
	}

	void query(const std_msgs::msg::String::SharedPtr msg){
		RCLCPP_INFO(this->get_logger(), "Subscription: '%s'", msg->data.c_str());

		std::stringstream qin, qout;
		qin << msg->data;

		int cmd;
		qin >> cmd;

		switch(cmd){
			case 1: {
				int size;
				qin >> size;

				alloc(size);
				qout << "allocated at index " << arrs.size() - 1 << " : " << arrs.back();
			} break;
			case 2: {
				int index;
				qin >> index;

				free(index);
		 		qout << "free";
			} break;
			case 3: {
				int k, i;
				qin >> k >> i;

				qout << "value: " << read(k, i);
			} break;
			case 4: {
				int k, i;
				qin >> k >> i;

				unsigned x;
				qin >> x;

				write(k, i, x);
				qout << "write";
			} break;
			case 5: { return; } break;
			default: break;
		}

		std_msgs::msg::String output;
		output.data = qout.str();
		RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", output.data.c_str());
		pub->publish(output);
	}

	void alloc(int sz){
		arrs.push_back(new unsigned[sz]);
	}

	void free(int index){
		unsigned * delp = arrs[index];
		arrs.erase(arrs.begin() + index);
		delete[] delp;
	}
	
	unsigned read(int k, int i){
		return arrs[k][i];
	}

	void write(int k, int i, unsigned x){
		arrs[k][i] = x;
	}
};

int main(int argc, char * argv[]){
	std::cout << "Server Starting" << std::endl;

	rclcpp::init(argc, argv);

	auto db = std::make_shared<database>(rclcpp::NodeOptions());
	auto sh = std::make_shared<secretholder>(rclcpp::NodeOptions());

	rclcpp::executors::SingleThreadedExecutor ex;

	ex.add_node(db);
	ex.add_node(sh);
	ex.spin();

	rclcpp::shutdown();
}
