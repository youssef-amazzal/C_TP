cmake_minimum_required(VERSION 3.22)
project(image)

include_directories(.)

add_executable(image
        main.c)

set_target_properties(image PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})