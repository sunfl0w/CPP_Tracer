cmake_minimum_required(VERSION 3.1)

project(CPP_Tracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -DENABLE_OPENGL_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -Wall -O3 -fopenmp -march=native -flto -mpopcnt -fwhole-program")

find_package(SDL2 REQUIRED SDL2)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

file(STRINGS "includelist.cmake" includes)
file(STRINGS "sourcelist.cmake" sources)

include_directories(${includes} ${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRs})

add_executable(CPP_Tracer_Starter ${sources})

if(OpenGL_FOUND)
    target_link_libraries(CPP_Tracer_Starter ${OPENGL_LIBRARIES})
endif(OpenGL_FOUND)

if (SDL2_FOUND)
    target_link_libraries(CPP_Tracer_Starter SDL2::SDL2)
endif (SDL2_FOUND)