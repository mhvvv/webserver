cmake_minimum_required(VERSION 3.16.3)

project(webserver)

set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)

add_subdirectory(sync)

add_executable(webserver main.cpp)

target_link_libraries(webserver sync)
