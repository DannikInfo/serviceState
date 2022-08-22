cmake_minimum_required(VERSION 3.21)
project(serviceState)

find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 23)

add_executable(serviceState main.cpp logger.h logger.cpp config.h config.cpp)

target_link_libraries(serviceState ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(serviceState mysqlcppconn)