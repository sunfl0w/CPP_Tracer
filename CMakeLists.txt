cmake_minimum_required(VERSION 3.1)

project(OpenCG)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -Wall -O3")

file(STRINGS "includelist.cmake" includes)

include_directories(${includes})
include(sourcelist.cmake)

add_executable(OpenCG_Starter ${sources})