if (NOT BUILD_TESTING)
    enable_testing()
endif ()

add_executable(LumiTests
        main.cpp
)

target_link_libraries(LumiTests
        PRIVATE
        Lumi::Lumi
        GTest::gtest_main
        GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(LumiTests)