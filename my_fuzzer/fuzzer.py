import os
import random
import rclpy
from rclpy.node import Node
from rclpy.timer import Timer
from .type_parser import dynamic_import

class Fuzzer(Node):
    def __init__(self, topics):
        super().__init__('fuzzer')

        self.topics = topics
        self.topic_publishers = {}
        self.random_data = self.generate_random_data()
        self.seed_dir = './seeds'

        # Ensure seed directory exists
        os.makedirs(self.seed_dir, exist_ok=True)

        # Initialize topic_publishers for topics
        for topic_name, topic_info in self.topics.items():
            msg_type = dynamic_import(topic_info['type'])
            self.topic_publishers[topic_name] = self.create_publisher(msg_type, topic_name, 10)
        
        # Add a timer to periodically fuzz topics
        self.timer = self.create_timer(1.0, self.fuzz_topics)  # 1-second interval
        self.get_logger().info("Fuzzer initialized with periodic fuzzing.")

        self.generate_seed_files()

    def generate_random_data(self):
        """Generate random fuzzing data."""
        return [
            b"A" * random.randint(1, 256),
            b"",  # Empty payload
            b"A" * 10000,
            b"\x00" * random.randint(1, 256),
            b"HelloWorld\x00"
        ]

    def generate_seed_files(self):
        """Save random data to seed files for AFL++."""
        for i, data in enumerate(self.random_data):
            seed_path = os.path.join(self.seed_dir, f'seed_{i}.bin')
            with open(seed_path, 'wb') as seed_file:
                seed_file.write(data)

    def fuzz_topics(self):
        """Fuzz all identified topics."""
        for topic_name, topic_info in self.topics.items():
            payload = random.choice(self.random_data).decode('utf-8', errors='ignore')
            msg_type = dynamic_import(topic_info['type'])
            msg = msg_type()
            if hasattr(msg, 'data'):  # Check if the message has a 'data' field
                msg.data = payload
            self.topic_publishers[topic_name].publish(msg)
            self.get_logger().info(f"Fuzzed topic '{topic_name}' with data: {payload}")
