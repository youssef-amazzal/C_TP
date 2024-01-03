cmake_minimum_required(VERSION 3.22)
project(conv)

include_directories(.)

add_executable(conv
        main.c)

set_target_properties(conv PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})