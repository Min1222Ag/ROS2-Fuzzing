import launch
import launch_ros.actions

def generate_launch_description():
    cam2image = launch_ros.actions.Node(
        package='rosec_image_tools',
        node_executable='cam2image',
        #parameters=[{'width':1280, 'height':720, 'burger_mode':True, 'history': 'keep_last'}],
        #remappings=[('/image', '/burgerimage')],
        output='screen'
    )

    showimage = launch_ros.actions.Node(
        package='rosec_image_tools',
        node_executable='showimage',
        #parameters=[{'history': 'keep_last'}],
        #remappings=[('/image', '/burgerimage')],
        output='screen'
    )

    return launch.LaunchDescription([cam2image, showimage])
