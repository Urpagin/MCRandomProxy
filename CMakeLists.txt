cmake_minimum_required(VERSION 3.29)
project(MCRandomProxy)

set(CMAKE_CXX_STANDARD 23)

include_directories(dependencies/asio-1.30.2/include)

add_executable(MCRandomProxy src/main.cpp
        src/Server.cpp
        src/RandomServer.cpp
        src/Session.cpp)
