/*
 * This is an automatically generated file. Do not modify.
 * 
 * This file contains the ros2_automatic_fuzzer implementation
 * for the `dbinteract.cpp` publisher source file.
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

#include "std_msgs/msg/string.hpp"
#include "dbinteract.cpp"

#include <cstdint>
#include <cstdlib>
#include <string>

/* Fuzzing API */
bool getBool(bool& b);
bool getByte(uint8_t& b);
bool getChar(char& c);

bool getFloat32(float& f);
bool getFloat64(double& d);

bool getInt8(int8_t& i);
bool getUInt8(uint8_t& ui);

bool getInt16(int16_t& i);
bool getUInt16(uint16_t& ui);

bool getInt32(int32_t& i);
bool getUInt32(uint32_t& ui);

bool getInt64(int64_t& i);
bool getUInt64(uint64_t& ui);

bool getString(std::string& s, uint8_t size);

/* Implementation */
bool getBool(bool& b)
{
    int c = getchar();
    if (c == EOF) return false;
    b = (c % 2 == 0);
    return true;
}

bool getByte(uint8_t& b)
{
    int c = getchar();
    if (c == EOF) return false;
    b = c;
    return true;
}

bool getChar(char& c)
{
    int gc = getchar();
    if (gc == EOF) return false;
    c = gc;
    return true;
}

bool getFloat32(float& f)
{
    char* bytes = (char *)& f;
    for (size_t i = 0; i < sizeof (float); ++i) {
        int c = getchar ();
        if (c == EOF) return false;
        bytes[i] = (char) c;
    }
    return true;
}

bool getFloat64(double& d)
{
    char* bytes = (char *)& d;
    for (size_t i = 0; i < sizeof (double); ++i) {
        int c = getchar ();
        if (c == EOF) return false;
        bytes[i] = (char) c;
    }
    return true;
}

bool getInt8(int8_t& i)
{
    int c = getchar();
    i = c;
    return (c != EOF);
}

bool getUInt8(uint8_t& ui)
{
    return getInt8((int8_t& )ui);
}

bool getInt16(int16_t& i) {
    char* bytes = (char *)& i;
    for (size_t i = 0; i < sizeof(int16_t); ++i)
    {
        int c = getchar();
        if (c == EOF) return false;
        bytes[i] = (char) c;
    }
    return true;
}

bool getUInt16(uint16_t& ui) {
    return getInt16((int16_t&) ui);
}

bool getInt32(int32_t& i) {
    char* bytes = (char *)& i;
    for (size_t i = 0; i < sizeof(int32_t); ++i)
    {
        int c = getchar();
        if (c == EOF) return false;
        bytes[i] = (char) c;
    }
    return true;
}

bool getUInt32(uint32_t& ui) {
    return getInt32((int32_t&) ui);
}

bool getInt64(int64_t& i)
{
    char* bytes = (char *)& i;
    for (size_t i = 0; i < sizeof(int64_t); ++i)
    {
        int c = getchar();
        if (c == EOF) return false;
        bytes[i] = (char) c;
    }
    return true;
}

bool getUInt64(uint64_t& ui)
{
    return getInt64((int64_t&) ui);
}

bool getString(std::string& s, uint8_t size)
{
    s = "";
    for (size_t i = 0; i < size; ++i)
    {
        int c = getchar();
        if (c == EOF) return false;
        s += (char)c;
    }
    return true;
}

/* 
    // data
    std::string _v0;
    if (!getString(_v0)) return;
    request->data = _v0;

*/

class FuzzerPublisher : public rclcpp::Node
{
public:
	FuzzerPublisher(int parent_pid)
	: Node("fuzzer__publisher_"), parent_pid_(parent_pid)
	{
		RCLCPP_INFO(this->get_logger(), "Started publisher from fuzz_target");
		publisher_ = this->create_publisher<std_msgs::msg::String>("string", 10);
		timerTimeout_ = this->create_wall_timer(
			10000ms, std::bind(&FuzzerPublisher::timer_timeout, this));
		timer_ = this->create_wall_timer(
			1ms, std::bind(&FuzzerPublisher::timer_callback, this));
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
		/*
        char v_char[256];
		int howMuch = read(0, v_char, 256);
		std::string s(v_char);
		if (!s.empty() && s[s.length()-1] == '\n') {
		    s.erase(s.length()-1);
		}
		input_ = s;
        */

           // data
    std::string _v0;
    if (!getString(_v0)) return;
    request->data = _v0;


		if (howMuch == 0) {
			std::cout << "No more input in the fuzz target!" << std::endl;
			timer_timeout();
		}

		auto message = std_msgs::msg::String(); 
		message.data = input_; 
		// RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
		publisher_->publish(message);
	}

	void detect_crash()
	{
		// A crash happens if the parent id is different from the original one
		// or simply if there is no PID running. Note that kill 0 doesn't send any signal!
		if (getppid() != parent_pid_ || 0 != kill(parent_pid_, 0)) {
			RCLCPP_INFO(this->get_logger(), "The node under test has crashed.\n"
				"Last input `%s` may have produced a crash.\n"
				"Stopping fuzzer.\n", input_.c_str() );
			rclcpp::shutdown();
			exit(EXIT_SUCCESS);
		}
	}
 
	static std::string get_all_input()
	{
	  std::cin >> std::noskipws;
	  std::istream_iterator<char> it(std::cin);
	  std::istream_iterator<char> end;
	  std::string results(it, end);
	  results.pop_back();
	  return results;
	}

	// Private fields
	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::TimerBase::SharedPtr timerTimeout_;
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
	
	pid_t parent_pid_;
	std::string input_;
};

static void fuzz_target(int argc, char* argv[], pid_t parent_pid)
{
	std::cout << "Fuzzer started" << std::endl;
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<FuzzerPublisher>(parent_pid));
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