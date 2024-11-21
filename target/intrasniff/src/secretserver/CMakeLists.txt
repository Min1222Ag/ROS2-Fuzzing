cmake_minimum_required(VERSION 3.8)
project(secretserver)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20) 
endif()

# compiler option
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# AFL++ instrumentation compile flag
set(AFL_SANITIZE_FLAGS "-fsanitize=address")
set(AFL_DEBUG_FLAGS "-g")
set(AFL_COVERAGE_FLAGS "-fsanitize-coverage=trace-pc-guard")

add_compile_options(${AFL_SANITIZE_FLAGS} ${AFL_DEBUG_FLAGS} ${AFL_COVERAGE_FLAGS})
add_link_options(${AFL_SANITIZE_FLAGS} ${AFL_DEBUG_FLAGS} ${AFL_COVERAGE_FLAGS})

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

add_executable(secretserver src/secretserver.cpp)
ament_target_dependencies(secretserver rclcpp std_msgs)
add_executable(dbinteract src/dbinteract.cpp)
ament_target_dependencies(dbinteract rclcpp std_msgs)

target_include_directories(secretserver PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(secretserver PUBLIC c_std_99 cxx_std_20)  # Require C99 and C++17


install(TARGETS secretserver dbinteract
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
