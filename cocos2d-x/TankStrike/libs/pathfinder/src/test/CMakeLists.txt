cmake_minimum_required(VERSION 3.13)
project(pathfinder)

set(CMAKE_CXX_STANDARD 14)

add_executable(pathfinder_test cpp/pathfinder_test.cpp)

include_directories(../main/public)

target_link_libraries(pathfinder_test pathfinderlib)
