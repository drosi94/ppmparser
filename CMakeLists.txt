cmake_minimum_required(VERSION 3.6)
project(PPMParser)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Image.cpp PPM_format.cpp)
add_executable(PPMParser ${SOURCE_FILES})