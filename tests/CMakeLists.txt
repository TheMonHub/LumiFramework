if (NOT BUILD_TESTING)
    enable_testing()
endif ()

add_executable(LumiTests
        main.cpp
        main.h
)

target_link_libraries(LumiTests
        PRIVATE
        Lumi::LumiStatic
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(LumiTests)