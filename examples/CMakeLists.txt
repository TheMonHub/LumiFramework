cmake_minimum_required(VERSION 3.16)
project(
        EXAMPLES
        LANGUAGES CXX
)

find_package(Lumi REQUIRED)

add_executable(Example
        main.cpp
)
target_include_directories(Example
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${Lumi_INCLUDE_DIRS}"
)
target_link_libraries(Example
        PRIVATE
        glfw
        ${Lumi_LIBRARIES}
)