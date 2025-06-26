cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
project(
        LumiInstallTests
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_SCAN_FOR_MODULES ON)
cmake_policy(SET CMP0155 NEW)

find_package(lumi REQUIRED CONFIG)

add_executable(LumiInstallTests
        main.cpp
        main.h
)

target_link_libraries(LumiInstallTests
        PRIVATE
        Lumi::Lumi
)