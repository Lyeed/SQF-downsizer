cmake_minimum_required(VERSION 3.0)

project(downsizer)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

include_directories(src/includes)

add_executable(downsize main.cpp src/trim.cpp src/downsize.cpp)
