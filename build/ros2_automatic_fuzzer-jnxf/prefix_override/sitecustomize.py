import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/emkim/projects/ros2/static_fuzz/install/ros2_automatic_fuzzer-jnxf'
