cmake_minimum_required(VERSION 3.31)
project(Lumi)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(test
               src/test.cpp)