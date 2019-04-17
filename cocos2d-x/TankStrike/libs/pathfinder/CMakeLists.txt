cmake_minimum_required(VERSION 3.13)
project(pathfinder)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(src/main)
add_subdirectory(src/test)

add_dependencies(pathfinder_test pathfinderlib)