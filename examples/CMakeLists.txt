cmake_minimum_required(VERSION 3.16)
project(
        EXAMPLES
        LANGUAGES CXX
)

find_package(glfw3 REQUIRED)
find_package(Lumi REQUIRED)
add_executable(ExampleWindow
        main.cpp
)
link_libraries(ExampleWindow
        glfw
        Lumi::LumiStatic
)