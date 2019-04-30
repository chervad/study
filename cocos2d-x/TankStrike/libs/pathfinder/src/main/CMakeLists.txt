cmake_minimum_required(VERSION 3.13)
project(pathfinder)

set(CMAKE_CXX_STANDARD 14)

add_library(pathfinderlib cpp/pathfinder.cpp public/pathfinder.h)

include_directories(../main/public)
include_directories(../main/headers)