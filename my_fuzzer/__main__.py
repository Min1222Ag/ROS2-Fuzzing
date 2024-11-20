import argparse
import yaml
import rclpy
from .fuzzer import Fuzzer
from .type_parser import parse_fuzz_yaml

def main():
    # Load fuzz.yaml
    parser = argparse.ArgumentParser(description="Fuzzer CLI for ROS 2")
    parser.add_argument("--path", required=True, help="Path to fuzz.yaml")
    args = parser.parse_args()

    fuzz_file = f"{args.path.rstrip('/')}/fuzz.yaml"
    with open(fuzz_file, 'r') as file:
        fuzz_config = yaml.safe_load(file)

    topics, services = parse_fuzz_yaml(fuzz_config)

    rclpy.init()
    fuzzer = Fuzzer(topics)
    try:
        rclpy.spin(fuzzer)
    except KeyboardInterrupt:
        print("Shutting down fuzzer...")
    finally:
        if rclpy.ok():  # Prevent duplicate shutdown
            rclpy.shutdown()

if __name__ == '__main__':
    main()
