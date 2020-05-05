cmake_minimum_required(VERSION 3.1)

project(CPP_Tracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -Wall -O3 -fopenmp -march=native -flto -mpopcnt -fwhole-program")

set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system network audio)

file(STRINGS "includelist.cmake" includes)
file(STRINGS "sourcelist.cmake" sources)

include_directories(${includes})

add_executable(CPP_Tracer_Starter ${sources})

if (SFML_FOUND)
    target_link_libraries(CPP_Tracer_Starter sfml-graphics)
endif (SFML_FOUND)