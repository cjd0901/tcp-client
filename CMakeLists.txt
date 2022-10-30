cmake_minimum_required(VERSION 3.23)
project(tcp_client)

set(CMAKE_CXX_STANDARD 14)

add_executable(tcp_client main.cpp include/tcp_client.cc include/tcp_client.h)
