/*
 * This is an automatically generated file. Do not modify.
 * 
 * This file contains the ros2_automatic_fuzzer implementation
 * for the `{{ FILE_NAME }}` composition source file.
 */
#include <iostream>

#include <string>
#include <istream>
#include <ostream>
#include <iterator>
#include <chrono>
#include <functional>
#include <memory>
#include <unistd.h>
#include <signal.h>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using namespace std;

{{ IMPORTS }}

{{ FUZZING_API }}

/* 
{{ REQUEST_CODE }}
*/

class FuzzerComposition : public rclcpp::Node
{
public:
	FuzzerComposition(int parent_pid)
	: Node("fuzzer__composition_"), parent_pid_(parent_pid)
	{
		RCLCPP_INFO(this->get_logger(), "Started composition from fuzz_target");
		timerTimeout_ = this->create_wall_timer(
			10000ms, std::bind(&FuzzerComposition::timer_timeout, this));
		timer_ = this->create_wall_timer(
			1ms, std::bind(&FuzzerComposition::timer_callback, this));
	}

private:

	// Kill parent and ourselves if time is up 
	void timer_timeout()
	{
		RCLCPP_INFO(this->get_logger(), "Time is up. Good job! Killing parent.");
		kill(parent_pid_, SIGUSR1);
		rclcpp::shutdown();
		exit(EXIT_SUCCESS);
	} 

	void timer_callback()
	{
		detect_crash();
		{{ REQUEST_CODE }}

		if (howMuch == 0) {
			std::cout << "No more input in the fuzz target!" << std::endl;
			timer_timeout();
		}

		// RCLCPP_INFO(this->get_logger(), "Executing composition callback");
	}

	void detect_crash()
	{
		// A crash happens if the parent id is different from the original one
		// or simply if there is no PID running. Note that kill 0 doesn't send any signal!
		if (getppid() != parent_pid_ || 0 != kill(parent_pid_, 0)) {
			RCLCPP_INFO(this->get_logger(), "The node under test has crashed.\n"
				"Last input may have produced a crash.\n"
				"Stopping fuzzer.\n" );
			rclcpp::shutdown();
			exit(EXIT_SUCCESS);
		}
	}

	// Private fields
	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::TimerBase::SharedPtr timerTimeout_;
	
	pid_t parent_pid_;
	std::string input_;
};

static void fuzz_target(int argc, char* argv[], pid_t parent_pid)
{
	std::cout << "Fuzzer started" << std::endl;
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<FuzzerComposition>(parent_pid));
	rclcpp::shutdown();
}


static void treat_timeout_signal(int signum)
{
	if (signum == SIGUSR1) {
		std::cout << "It is time to finish!" << std::endl;
		rclcpp::shutdown();
		exit(EXIT_SUCCESS);
	}
}

static void __attribute__((constructor)) __injector_init()
{
	pid_t parent_pid = getpid();
	pid_t pid = fork();

	if (pid < 0) {
		std::cout << "Something crashed" << std::endl;
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		int argc = 1;
		char* argv[] = {"./my_fuzz_target", NULL};
		fuzz_target(argc, argv, parent_pid);
		exit(EXIT_FAILURE);
	}

	// Parent's code
	signal(SIGUSR1, treat_timeout_signal);

	// Close standard input in the node
	close(0);

	// Continue normal system under test code
	std::cout << "Continuing normal code" << std::endl;
}
