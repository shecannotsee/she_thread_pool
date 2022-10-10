cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "thread_pool_test")
set(CMAKE_CXX_FLAGS "-g")# 断点无效处理方案
project(${PROJECT_NAME})

get_filename_component(now ${CMAKE_SOURCE_DIR} DIRECTORY)
message(STATUS "now's path:${now}")
get_filename_component(project_path ${now} DIRECTORY)
message(STATUS "project_path's path:${project_path}")

set(source_src "${project_path}/src")

include_directories(${source_src}/SafeQueue)
link_directories()
# aux_source_directory(. SOURCE)
file(GLOB_RECURSE SRC "${CMAKE_SOURCE_DIR}/main.cpp")
add_executable(${PROJECT_NAME} ${SRC})
# 链接库
target_link_libraries(${PROJECT_NAME} "-pthread")