// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

#include <vector>
#include "Lumi/Core/ErrorHandler.h"
#include "gtest/gtest.h"

#include "Lumi/Core/Core.h"

class ErrorHandlerTest : public ::testing::Test {
protected:
	void SetUp() override {
		// Reset to default settings before each test
		Lumi::ErrorHandler::LUMI_SET_LOG_LEVEL(Lumi::ErrorHandler::LogSeverity::Info);
		Lumi::ErrorHandler::LUMI_SET_ERROR_SEVERITY(Lumi::ErrorHandler::LogSeverity::Warning);
		Lumi::ErrorHandler::LUMI_SET_FATAL_SEVERITY(Lumi::ErrorHandler::LogSeverity::Fatal);
		Lumi::ErrorHandler::LUMI_SET_FUNNY_ERROR_BOOL(false);
		Lumi::ErrorHandler::LUMI_SET_LOG_ENABLED(true);
		Lumi::ErrorHandler::LUMI_CLEAR_LOG_CALLBACKS();
		Lumi::ErrorHandler::LUMI_CLEAR_LOG_MESSAGES();
		Lumi::LUMI_SET_TEST_MODE(true);
	}
};

// Test severity settings
TEST_F(ErrorHandlerTest, SeveritySettings) {
	Lumi::ErrorHandler::LUMI_SET_LOG_LEVEL(Lumi::ErrorHandler::LogSeverity::Warning);
	EXPECT_EQ(Lumi::ErrorHandler::LUMI_GET_LOG_LEVEL(), Lumi::ErrorHandler::LogSeverity::Warning);

	Lumi::ErrorHandler::LUMI_SET_ERROR_SEVERITY(Lumi::ErrorHandler::LogSeverity::Error);
	EXPECT_EQ(Lumi::ErrorHandler::LUMI_GET_ERROR_SEVERITY(), Lumi::ErrorHandler::LogSeverity::Error);

	// Test that Info cannot be set as fatal severity without the allow flag
	Lumi::ErrorHandler::LUMI_SET_FATAL_SEVERITY(Lumi::ErrorHandler::LogSeverity::Info, false);
	EXPECT_NE(Lumi::ErrorHandler::LUMI_GET_FATAL_SEVERITY(), Lumi::ErrorHandler::LogSeverity::Info);

	// Test that Info can be set as fatal severity with the allow flag
	Lumi::ErrorHandler::LUMI_SET_FATAL_SEVERITY(Lumi::ErrorHandler::LogSeverity::Info, true);
	EXPECT_EQ(Lumi::ErrorHandler::LUMI_GET_FATAL_SEVERITY(), Lumi::ErrorHandler::LogSeverity::Info);
}

// Test assertion functionality
TEST_F(ErrorHandlerTest, Assertions) {
	EXPECT_TRUE(Lumi::ErrorHandler::LUMI_ASSERT(false, true));
	EXPECT_FALSE(Lumi::ErrorHandler::LUMI_ASSERT(true, true));

	// Test numeric assertions
	EXPECT_TRUE(Lumi::ErrorHandler::LUMI_ASSERT(5, 10, Lumi::ErrorHandler::AssertType::GREATER));
	EXPECT_FALSE(Lumi::ErrorHandler::LUMI_ASSERT(15, 10, Lumi::ErrorHandler::AssertType::GREATER));

	EXPECT_TRUE(Lumi::ErrorHandler::LUMI_ASSERT(10, 5, Lumi::ErrorHandler::AssertType::LOWER));
	EXPECT_FALSE(Lumi::ErrorHandler::LUMI_ASSERT(5, 10, Lumi::ErrorHandler::AssertType::LOWER));
}

// Test callback functionality
TEST_F(ErrorHandlerTest, LogCallbacks) {
	bool callbackCalled = false;
	auto callback = [&callbackCalled](const Lumi::ErrorHandler::LogData &data) {
		callbackCalled = true;
		EXPECT_EQ(data.code, Lumi::ErrorHandler::LogCode::Success);
	};

	Lumi::ErrorHandler::LUMI_REGISTER_LOG_CALLBACK(callback);
	Lumi::ErrorHandler::LUMI_LOG("Test message", Lumi::ErrorHandler::LogCode::Success);
	EXPECT_TRUE(callbackCalled);
}

// Test funny error messages
TEST_F(ErrorHandlerTest, FunnyErrorMessages) {
	const std::vector<std::string_view> messages = {"Funny message 1", "Funny message 2"};
	Lumi::ErrorHandler::LUMI_REGISTER_LOG_MESSAGES(messages);
	Lumi::ErrorHandler::LUMI_SET_FUNNY_ERROR_BOOL(true);
	EXPECT_TRUE(Lumi::ErrorHandler::LUMI_GET_FUNNY_ERROR_BOOL());

	// Clear messages and verify
	Lumi::ErrorHandler::LUMI_CLEAR_LOG_MESSAGES();
	EXPECT_EXIT(Lumi::ErrorHandler::LUMI_LOG("Test message", Lumi::ErrorHandler::LogCode::UnknownError,
											 Lumi::ErrorHandler::LogSeverity::Fatal),
				::testing::ExitedWithCode(1), "Fatal Error Occurred");
}

// Test log enable/disable functionality
TEST_F(ErrorHandlerTest, LogEnableDisable) {
	Lumi::ErrorHandler::LUMI_SET_LOG_ENABLED(false);
	EXPECT_FALSE(Lumi::ErrorHandler::LUMI_GET_LOG_ENABLED());

	Lumi::ErrorHandler::LUMI_SET_LOG_ENABLED(true);
	EXPECT_TRUE(Lumi::ErrorHandler::LUMI_GET_LOG_ENABLED());
}

// Test random seed setting
TEST_F(ErrorHandlerTest, RandomSeed) {
	// Verify that setting seed doesn't crash
	Lumi::ErrorHandler::LUMI_LOG_SET_RANDOM_SEED(69420); // Funni number ADM@QIOEMDAS
}
