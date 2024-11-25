# image_tools

## build and install
```bash
cd image_tools
colcon build
source ./install/local_setup.bash
```

## run
1. spin cam2image and showimage in separate processes.
```bash
ros2 launch rosec_image_tools separation.launch.py
```
2. spin cam2image and showimage in a single process.
```bash
ros2 launch rosec_image_tools composition.launch.py
```

## evaluation
```bash
cd scripts
./test.py
```

## configure
if you want to change configures such as video resolution or refresh rate(freq.) <br> 
modify src/cam2image.cpp <br> <br>
default resolution : 320x240 <br>
default frequency : 30 (hz)
