# Intrasniff

## Project Build and Execution Guide

### 1. Create Build Directory and Build the Project
To build the project, use `colcon`. Run the following command in the Intrasniff directory:
>colcon build

### 2. Source the Environment Setup File After Build
After the build is complete, you need to source the environment setup file to use the installed environment. Use one of the following commands:
- **If using Zsh**:
  >source install/local_setup.zsh

- **If using Bash**:
  >source install/local_setup.bash

### 3. Run the Nodes
Once the build is complete and the environment is sourced, you can run the nodes using the following commands:
- **Run the `secretserver` node**:
  >ros2 run secretserver secretserver

- **Run the `dbinteract` node**:
  >ros2 run secretserver dbinteract
  
