#!/usr/bin/python3
from my_utils import * 

# test standalone nodes
def test_standalone_nodes(params = {},debug = False):
    # launch
    node_processes = launch_standalone_nodes()
    cpu_percent,memory_percent = performace_test(node_processes,time_sec=300,enable_ouput=debug)
    print("cpu:",cpu_percent,"memory:", memory_percent)
    for p in node_processes:
        p.kill()

# test composition nodes
def test_composed_nodes(params = {},debug = False):
    # launch
    node_processes = launch_composed_nodes()
    cpu_percent,memory_percent = performace_test(node_processes,time_sec=300,enable_ouput=debug)
    print("cpu:",cpu_percent,"memory:", memory_percent)
    for p in node_processes:
        p.kill()

# param
#test_params={}
#test_params["enable_output_delay"]=False
#test_params["enable_output_address"]=False
#test_params["rate"]=100
#test_params["point_num"]=10000

killall()
# case1
print("case 1: spin cam2image and showimage separately")
test_standalone_nodes()
# case2
print("case 2: spin cam2image and showimage together - composition")
test_composed_nodes()
