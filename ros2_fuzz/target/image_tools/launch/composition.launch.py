import launch
import launch_ros.actions
import launch_ros.descriptions

def generate_launch_description():
    container = launch_ros.actions.ComposableNodeContainer(
        node_name='rosec_container',
        node_namespace='',
        package='rclcpp_components',
        node_executable='component_container',
        composable_node_descriptions=[
            launch_ros.descriptions.ComposableNode(
                package='rosec_image_tools',
                node_plugin='rosec_image_tools::Cam2Image',
                node_name='cam2image',
                remappings=[('image', 'burgerimage')],
                extra_arguments=[{'use_intra_process_comms': False}]
            ),
            launch_ros.descriptions.ComposableNode(
                package='rosec_image_tools',
                node_plugin='rosec_image_tools::ShowImage',
                node_name='showimage',
                remappings=[('image', 'burgerimage')],
                extra_arguments=[{'use_intra_process_comms': False}]
            ),
        ],
        output='screen',
    )

    return launch.LaunchDescription([container])

