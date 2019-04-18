cmake_minimum_required(VERSION 3.13)
project(pathfinder)

set(CMAKE_CXX_STANDARD 14)
#set(GOOGLETEST_VERSION 1.8.1)

add_subdirectory(googletest)

add_executable(pathfinder_test cpp/pathfinder_test.cpp)

include_directories(../main/public)
include_directories(googletest/include)

target_link_libraries(pathfinder_test pathfinderlib gtest_main)
add_test(NAME example_test COMMAND example)
