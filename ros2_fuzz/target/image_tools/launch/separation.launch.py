import launch
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    cam2image = Node(
        package='rosec_image_tools',
        executable='cam2image',
        #parameters=[{'width':1280, 'height':720, 'burger_mode':True, 'history': 'keep_last'}],
        #remappings=[('/image', '/burgerimage')],
        output='screen'
    )

    showimage = Node(
        package='rosec_image_tools',
        executable='showimage',
        #parameters=[{'history': 'keep_last'}],
        #remappings=[('/image', '/burgerimage')],
        output='screen'
    )

    return LaunchDescription([cam2image, showimage])
