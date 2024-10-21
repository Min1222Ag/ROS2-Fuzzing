import sys
import os

sys.path.append("..")

from ros2_fuzzer.fuzzing_utils.type_parser import TypeParser
from ros2_fuzzer.fuzzing_utils.fuzzing_descriptor import FuzzTargetProcessor
from ros2_fuzzer.fuzzing_utils.generate_cpp_file import generate_cpp_file


def generate_composition_template(source: str, ros_type_str: str, headers_file: str) -> str:
    original_file = os.path.basename(source)
    composition_name = ros_type_str.replace("::", "/")
    ros_type = TypeParser.parse_type(composition_name)

    fuzz_target = FuzzTargetProcessor().process(
        ros_type,
        headers_file=headers_file,
        original_file=original_file,
        ros_type_str=ros_type_str,
    )

    return generate_cpp_file(
        fuzz_target=fuzz_target,
        source_file=source,
        template_name="composition_template.jinx.cpp",
    )
