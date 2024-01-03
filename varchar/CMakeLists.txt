cmake_minimum_required(VERSION 3.22)
project(varchar)

include_directories(.)

add_executable(varchar
        main.c)

set_target_properties(varchar PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})