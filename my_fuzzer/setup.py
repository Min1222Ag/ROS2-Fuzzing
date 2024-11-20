from setuptools import setup, find_packages

setup(
    name="my_fuzzer",
    version="0.1.0",
    packages=find_packages(),
    install_requires=[
        "rclpy",
        "pyyaml",
    ],
    entry_points={
        "console_scripts": [
            "my_fuzzer = my_fuzzer.__main__:main",  # Maps the `fuzzer` command to `__main__.py`
        ],
    },
)