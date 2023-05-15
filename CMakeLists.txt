cmake_minimum_required(VERSION 3.16.3)

project(webserver)

set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)


include_directories(sync)
file(GLOB sync_srcs sync/*.cpp)
add_library (sync SHARED ${sync_srcs})

include_directories(log)
file(GLOB log_srcs log/*.cpp)
add_library(log SHARED ${log_srcs})
target_link_libraries(log sync)

include_directories(connpool)
file(GLOB connpool_srcs connpool/*.cpp)
add_library(connpool SHARED ${connpool_srcs})
target_link_libraries(connpool sync log)


add_executable(webserver main.cpp)

target_link_libraries(webserver sync log connpool pthread mysqlclient)
