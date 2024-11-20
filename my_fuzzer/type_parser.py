import importlib

def parse_fuzz_yaml(fuzz_config):
    """
    Parse the fuzz.yaml configuration file.
    Extract topics and services for fuzzing.
    """
    topics = fuzz_config.get('topics', {})
    services = fuzz_config.get('services', {})
    return topics, services

def dynamic_import(type_name):
    """
    Dynamically import a ROS 2 message or service type based on its full name.

    :param type_name: ROS 2 type name, e.g., "std_msgs::msg::String"
    :return: Imported Python class
    """
    type_parts = type_name.split('::')
    module_path = '.'.join(type_parts[:-1])  # e.g., "std_msgs.msg"
    class_name = type_parts[-1]             # e.g., "String"

    try:
        module = importlib.import_module(module_path)
        return getattr(module, class_name)
    except (ModuleNotFoundError, AttributeError) as e:
        raise ImportError(f"Failed to import {type_name}: {e}")
