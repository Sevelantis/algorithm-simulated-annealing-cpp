cmake_minimum_required(VERSION 3.14)
project(CODE)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -DDEFINED_IN_CMAKELISTS")

add_executable(CODE main.cpp FileHandler.cpp SW.cpp SW.h Timer.h)
