import launch
from launch import LaunchDescription
import launch_ros.actions 
import launch_ros.descriptions

def generate_launch_description():
    container = launch_ros.actions.ComposableNodeContainer(
        name='rosec_container',
        namespace='',
        package='rclcpp_components',
        executable='component_container',
        composable_node_descriptions=[
            launch_ros.descriptions.ComposableNode(
                package='rosec_image_tools',
                plugin='rosec_image_tools::Cam2Image',
                name='cam2image',
                remappings=[('image', 'burgerimage')],
                extra_arguments=[{'use_intra_process_comms': False}]
            ),
            launch_ros.descriptions.ComposableNode(
                package='rosec_image_tools',
                plugin='rosec_image_tools::ShowImage',
                name='showimage',
                remappings=[('image', 'burgerimage')],
                extra_arguments=[{'use_intra_process_comms': False}]
            ),
        ],
        output='screen',
    )

    return launch.LaunchDescription([container])

