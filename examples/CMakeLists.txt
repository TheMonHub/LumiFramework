cmake_minimum_required(VERSION 3.16)
project(
        EXAMPLES
        LANGUAGES CXX
)

add_executable(Example
        main.cpp
)
target_include_directories(Example
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
target_link_libraries(Example
        PRIVATE
        glfw
        Lumi::LumiStatic
)