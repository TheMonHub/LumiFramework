// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

// error_handler_test.cpp
#include <Lumi/Core/Core.h>
#include <Lumi/Core/ErrorHandler.h>
#include <algorithm>
#include <gtest/gtest.h>
#include <string>
#include <vector>

class ErrorHandlerTest : public ::testing::Test {
protected:
	void SetUp() override {
		Lumi::LUMI_SET_TEST_MODE(true);
		Lumi::ErrorHandler::LUMI_SET_LOG_ENABLED(true);
		Lumi::ErrorHandler::LUMI_SET_LOG_LEVEL(Lumi::ErrorHandler::LogSeverity::Info);
		Lumi::ErrorHandler::LUMI_SET_FUNNY_ERROR_BOOL(false);
		Lumi::ErrorHandler::LUMI_SET_FATAL_SEVERITY(Lumi::ErrorHandler::LogSeverity::Fatal);
		Lumi::ErrorHandler::LUMI_CLEAR_LOG_CALLBACKS();
		Lumi::ErrorHandler::LUMI_CLEAR_LOG_MESSAGES();
		captured_logs.clear();
	}

	void TearDown() override { Lumi::ErrorHandler::LUMI_CLEAR_LOG_CALLBACKS(); }

	std::vector<Lumi::ErrorHandler::LogData> captured_logs;

	void RegisterCaptureCallback() {
		Lumi::ErrorHandler::LUMI_REGISTER_LOG_CALLBACK(
				[this](const Lumi::ErrorHandler::LogData &data) { captured_logs.push_back(data); });
	}
};

TEST_F(ErrorHandlerTest, BasicLogging) {
	RegisterCaptureCallback();

	Lumi::ErrorHandler::LUMI_LOG("Test message", Lumi::ErrorHandler::LogCode::Success,
								 Lumi::ErrorHandler::LogSeverity::Info);

	ASSERT_EQ(captured_logs.size(), 1);
	EXPECT_EQ(captured_logs[0].message, "Test message");
	EXPECT_EQ(captured_logs[0].code, Lumi::ErrorHandler::LogCode::Success);
	EXPECT_EQ(captured_logs[0].severity, Lumi::ErrorHandler::LogSeverity::Info);
}

TEST_F(ErrorHandlerTest, LogLevelFiltering) {
	RegisterCaptureCallback();

	Lumi::ErrorHandler::LUMI_SET_LOG_LEVEL(Lumi::ErrorHandler::LogSeverity::Error);

	// This should not be logged
	Lumi::ErrorHandler::LUMI_LOG("Info message", Lumi::ErrorHandler::LogCode::Success,
								 Lumi::ErrorHandler::LogSeverity::Info);

	// This should be logged
	Lumi::ErrorHandler::LUMI_LOG("Error message", Lumi::ErrorHandler::LogCode::InternalError,
								 Lumi::ErrorHandler::LogSeverity::Error);

	ASSERT_EQ(captured_logs.size(), 2);
	EXPECT_EQ(captured_logs[1].message, "Error message");
}

TEST_F(ErrorHandlerTest, FunnyErrorMessages) {
	RegisterCaptureCallback();
	Lumi::ErrorHandler::LUMI_SET_FUNNY_ERROR_BOOL(true);
	const std::vector<std::string> funny_messages = {"Oops!", "Oh no!", "What happened?"};
	Lumi::ErrorHandler::LUMI_REGISTER_LOG_MESSAGES(funny_messages);

	Lumi::LUMI_SET_TEST_MODE(true);
	Lumi::ErrorHandler::LUMI_SET_FATAL_CRASH(false);
	Lumi::ErrorHandler::LUMI_LOG("Fatal error", Lumi::ErrorHandler::LogCode::InternalError,
								 Lumi::ErrorHandler::LogSeverity::Fatal);

	ASSERT_EQ(captured_logs.size(), 1);
	EXPECT_FALSE(captured_logs[0].funnyMessage.empty());

	bool found_message = false;
	for (const auto &msg: funny_messages) {
		if (msg == captured_logs[0].funnyMessage) {
			found_message = true;
			break;
		}
	}
	EXPECT_TRUE(found_message);
}

TEST_F(ErrorHandlerTest, AssertionTests) {
	RegisterCaptureCallback();

	// Test equal assertion
	EXPECT_TRUE(Lumi::ErrorHandler::LUMI_ASSERT(5, 10, Lumi::ErrorHandler::AssertType::EQUAL));

	EXPECT_TRUE(Lumi::ErrorHandler::LUMI_ASSERT(10, 11, Lumi::ErrorHandler::AssertType::GREATER_EQUAL));
	EXPECT_FALSE(Lumi::ErrorHandler::LUMI_ASSERT(10, 11, Lumi::ErrorHandler::AssertType::LOWER_EQUAL));

	// Test greater than assertion
	EXPECT_TRUE(Lumi::ErrorHandler::LUMI_ASSERT(5, 10, Lumi::ErrorHandler::AssertType::GREATER));

	// Test less than assertion
	EXPECT_FALSE(Lumi::ErrorHandler::LUMI_ASSERT(5, 10, Lumi::ErrorHandler::AssertType::LOWER));

	ASSERT_EQ(captured_logs.size(), 3);
	EXPECT_EQ(captured_logs[0].code, Lumi::ErrorHandler::LogCode::AssertionFailed);
	EXPECT_EQ(captured_logs[1].code, Lumi::ErrorHandler::LogCode::AssertionFailed);
}

TEST_F(ErrorHandlerTest, MultipleLogs) {
	RegisterCaptureCallback();

	constexpr int num_logs = 100;

	for (int i = 0; i < num_logs; ++i) {
		Lumi::ErrorHandler::LUMI_LOG("Message " + std::to_string(i), Lumi::ErrorHandler::LogCode::Success,
									 Lumi::ErrorHandler::LogSeverity::Info);
	}

	EXPECT_EQ(captured_logs.size(), num_logs);
}

TEST_F(ErrorHandlerTest, CallbackExceptionHandling) {
	// Redirect cerr to capture the warning message
	const std::stringstream cerr_buffer;
	std::streambuf *old_cerr = std::cerr.rdbuf(cerr_buffer.rdbuf());

	// Register a callback that throws
	Lumi::ErrorHandler::LUMI_REGISTER_LOG_CALLBACK(
			[](const Lumi::ErrorHandler::LogData &) { throw std::runtime_error("Test exception"); });

	// This should not crash
	EXPECT_NO_THROW(Lumi::ErrorHandler::LUMI_LOG("Test message", Lumi::ErrorHandler::LogCode::Success,
												 Lumi::ErrorHandler::LogSeverity::Info));

	// Verify that the warning message was printed
	const std::string error_output = cerr_buffer.str();
	EXPECT_TRUE(error_output.find("WARNING: A registered log callback threw a std::exception") != std::string::npos);
	EXPECT_TRUE(error_output.find("Test exception") != std::string::npos);

	// Restore cerr
	std::cerr.rdbuf(old_cerr);
}

TEST_F(ErrorHandlerTest, FatalErrorDeathTest) {
	Lumi::ErrorHandler::LUMI_SET_FATAL_CRASH(true); // Enable fatal crash
	Lumi::ErrorHandler::LUMI_SET_FATAL_SEVERITY(Lumi::ErrorHandler::LogSeverity::Fatal);

	// Test that the program terminates with fatal error
	ASSERT_DEATH(
			{
				Lumi::ErrorHandler::LUMI_LOG("Fatal error test", Lumi::ErrorHandler::LogCode::InternalError,
											 Lumi::ErrorHandler::LogSeverity::Fatal);
			},
			"Fatal Error Occurred, Can not proceed. Exiting...");
}

TEST_F(ErrorHandlerTest, NonFatalSeverityDoesNotDie) {
	Lumi::ErrorHandler::LUMI_SET_FATAL_CRASH(true);
	Lumi::ErrorHandler::LUMI_SET_FATAL_SEVERITY(Lumi::ErrorHandler::LogSeverity::Fatal);

	// This should not crash
	ASSERT_NO_FATAL_FAILURE({
		Lumi::ErrorHandler::LUMI_LOG("Non-fatal error", Lumi::ErrorHandler::LogCode::InternalError,
									 Lumi::ErrorHandler::LogSeverity::Error);
	});
}

TEST_F(ErrorHandlerTest, FatalErrorWithCrashDisabledDoesNotDie) {
	Lumi::ErrorHandler::LUMI_SET_FATAL_CRASH(false); // Disable fatal crash
	Lumi::ErrorHandler::LUMI_SET_FATAL_SEVERITY(Lumi::ErrorHandler::LogSeverity::Fatal);

	// This should not crash when fatal crash is disabled
	ASSERT_NO_FATAL_FAILURE({
		Lumi::ErrorHandler::LUMI_LOG("Fatal error with crash disabled", Lumi::ErrorHandler::LogCode::InternalError,
									 Lumi::ErrorHandler::LogSeverity::Fatal);
	});
}

// Test fatal severity threshold
TEST_F(ErrorHandlerTest, CustomFatalSeverityDeathTest) {
	Lumi::ErrorHandler::LUMI_SET_FATAL_CRASH(true);
	Lumi::ErrorHandler::LUMI_SET_FATAL_SEVERITY(Lumi::ErrorHandler::LogSeverity::Warning);

	// Should die because Warning is now considered fatal
	ASSERT_DEATH(
			{
				Lumi::ErrorHandler::LUMI_LOG("Warning becomes fatal", Lumi::ErrorHandler::LogCode::InternalError,
											 Lumi::ErrorHandler::LogSeverity::Warning);
			},
			"Fatal Error Occurred, Can not proceed. Exiting...");
}
