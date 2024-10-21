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
#include "class_loader/class_loader.hpp"
#include "rclcpp_components/node_factory.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using namespace std;

{{ IMPORTS }}

{{ FUZZING_API }}

/* 
{{ REQUEST_CODE }}
*/

class FuzzerNode : public rclcpp::Node
{
public:
    FuzzerNode(int parent_pid, std::shared_ptr<rclcpp::Node> node)
    : Node("fuzzer__composition_node_"), parent_pid_(parent_pid), node_(node)
    {
        RCLCPP_INFO(this->get_logger(), "Started composition node fuzzer");
        timerTimeout_ = this->create_wall_timer(
            10000ms, std::bind(&FuzzerNode::timer_timeout, this));
        timer_ = this->create_wall_timer(
            1ms, std::bind(&FuzzerNode::timer_callback, this));
    }

private:
    void timer_timeout()
    {
        RCLCPP_INFO(this->get_logger(), "Time is up. Killing parent.");
        kill(parent_pid_, SIGUSR1);
        rclcpp::shutdown();
        exit(EXIT_SUCCESS);
    }

    void timer_callback()
    {
        detect_crash();
        
        {{ REQUEST_CODE }}

        // Simulate node interaction
        RCLCPP_INFO(this->get_logger(), "Node interaction fuzzing");

        if (howMuch == 0) {
            timer_timeout();
        }
    }

    void detect_crash()
    {
        if (getppid() != parent_pid_ || 0 != kill(parent_pid_, 0)) {
            RCLCPP_INFO(this->get_logger(), "Node under test crashed.");
            rclcpp::shutdown();
            exit(EXIT_SUCCESS);
        }
    }

    // Private fields
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::TimerBase::SharedPtr timerTimeout_;
    pid_t parent_pid_;
    std::shared_ptr<rclcpp::Node> node_;
    std::string input_;
};

static void fuzz_target(int argc, char* argv[], pid_t parent_pid)
{
    std::cout << "Fuzzer started for composition" << std::endl;
    rclcpp::init(argc, argv);
    
    rclcpp::executors::SingleThreadedExecutor exec;
    std::vector<std::shared_ptr<rclcpp::Node>> nodes;

    // Load and fuzz each node dynamically
    std::vector<class_loader::ClassLoader*> loaders;
    std::vector<rclcpp_components::NodeInstanceWrapper> node_wrappers;

    // Assume libraries are passed in argv
    for (int i = 1; i < argc; ++i) {
        std::string library = argv[i];
        auto loader = new class_loader::ClassLoader(library);
        auto classes = loader->getAvailableClasses<rclcpp_components::NodeFactory>();
        for (auto clazz : classes) {
            auto node_factory = loader->createInstance<rclcpp_components::NodeFactory>(clazz);
            auto wrapper = node_factory->create_node_instance({});
            auto node = wrapper.get_node_base_interface();
            nodes.push_back(std::shared_ptr<rclcpp::Node>(node));
            exec.add_node(node);
        }
        loaders.push_back(loader);
    }

    for (auto& node : nodes) {
        exec.spin_node_once(node);
        fuzz_target(argc, argv, parent_pid); // Fuzz each node
    }

    rclcpp::shutdown();
}


static void treat_timeout_signal(int signum)
{
    if (signum == SIGUSR1) {
        std::cout << "Time to finish!" << std::endl;
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

    signal(SIGUSR1, treat_timeout_signal);

    close(0);

    std::cout << "Continuing normal code" << std::endl;
}
