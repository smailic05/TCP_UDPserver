cmake_minimum_required(VERSION 3.17)
project(TCP_UDPserver)

set(CMAKE_CXX_STANDARD 20)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(TCP_UDPserver server.cpp TCPServer.cpp TCPServer.h UDPServer.cpp UDPServer.h   )
target_link_libraries(TCP_UDPserver PRIVATE Threads::Threads)
add_executable(TCP_UDPclient client.cpp  TCPClient.cpp TCPClient.h  UDPClient.cpp UDPClient.h)