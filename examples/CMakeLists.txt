cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
project(
        LumiExamples
        LANGUAGES CXX
)

add_executable(LumiExamples
        "main.cpp"
)
target_include_directories(LumiExamples
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
target_link_libraries(LumiExamples
        PRIVATE
        Lumi::Lumi
)