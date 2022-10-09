cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_NAME "she_thread_pool_test")

#
get_filename_component(a_demo ${CMAKE_SOURCE_DIR} DIRECTORY)
message(STATUS "a_demo's path:${a_demo}")#/Users/shecannotsee/Desktop/AllCode/testcode/a-demo
get_filename_component(testcode ${a_demo} DIRECTORY)
message(STATUS "testcode's path:${testcode}")# /Users/shecannotsee/Desktop/AllCode/testcode

set(CMAKE_CXX_FLAGS "-g")# 断点无效处理方案
project(${PROJECT_NAME})

# include
include_directories(
)
# lib
link_directories(
)

# aux_source_directory(. SOURCE)
file(GLOB_RECURSE SRC "${CMAKE_SOURCE_DIR}/src/*")
add_executable(${PROJECT_NAME}
        ${SRC}
        )

# 链接库
target_link_libraries(${PROJECT_NAME} pthread)
