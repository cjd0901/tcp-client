cmake_minimum_required(VERSION 3.23)
project(tcp_client)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads)
add_executable(tcp_client main.cpp include/tcp_client.cc include/tcp_client.h include/timer.cc include/timer.h)
target_link_libraries(tcp_client ${CMAKE_THREAD_LIBS_INIT})