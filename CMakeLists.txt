
cmake_minimum_required(VERSION 2.8)
PROJECT(TCPSERVER)
message("build with debug mode")
# aux_source_directory ( . DIR_SRCS)
# ADD_EXECUTABLE(tcp main.cpp ${DIR_SRCS})
add_executable(tcp main.cpp ChatServer.cpp ChatSocket.cpp Epoll.cpp protocol.cpp)
# 你当然可以add_executable(Demo main.cpp operation.cpp multiple.cpp)
include_directories(.)