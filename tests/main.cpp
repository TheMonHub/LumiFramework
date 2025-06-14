// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

// error_handler_test.cpp
#include <Lumi/Core/Core.h>
#include <Lumi/Core/ErrorHandler.h>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <vector>

class ErrorHandlerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    lumi::LumiSetTestMode(true);
    lumi::error_handler::LumiSetLogEnabled(true);
    lumi::error_handler::LumiSetLogLevel(
        lumi::error_handler::LOG_SEVERITY::INFO);
    lumi::error_handler::LumiSetFunnyErrorBool(false);
    lumi::error_handler::LumiSetFatalSeverity(
        lumi::error_handler::LOG_SEVERITY::FATAL);
    lumi::error_handler::LumiClearLogCallbacks();
    lumi::error_handler::LumiClearLogMessages();
    captured_logs_.clear();
  }

  void TearDown() override { lumi::error_handler::LumiClearLogCallbacks(); }

  std::vector<lumi::error_handler::LogData> captured_logs_;

  void RegisterCaptureCallback() {
    lumi::error_handler::LumiRegisterLogCallback(
        [this](const lumi::error_handler::LogData &data) {
          captured_logs_.push_back(data);
        });
  }
};

TEST_F(ErrorHandlerTest, BasicLogging) {
  RegisterCaptureCallback();

  lumi::error_handler::LumiLog("Test message",
                               lumi::error_handler::LOG_CODE::SUCCESS,
                               lumi::error_handler::LOG_SEVERITY::INFO);

  ASSERT_EQ(captured_logs_.size(), 1);
  EXPECT_EQ(captured_logs_[0].message_, "Test message");
  EXPECT_EQ(captured_logs_[0].code_, lumi::error_handler::LOG_CODE::SUCCESS);
  EXPECT_EQ(captured_logs_[0].severity_,
            lumi::error_handler::LOG_SEVERITY::INFO);
}

TEST_F(ErrorHandlerTest, LogLevelFiltering) {
  RegisterCaptureCallback();

  lumi::error_handler::LumiSetLogLevel(lumi::error_handler::LOG_SEVERITY::ERROR);

  // This should not be logged
  lumi::error_handler::LumiLog("Info message",
                               lumi::error_handler::LOG_CODE::SUCCESS,
                               lumi::error_handler::LOG_SEVERITY::INFO);

  // This should be logged
  lumi::error_handler::LumiLog("Error message",
                               lumi::error_handler::LOG_CODE::kINTERNAL_ERROR,
                               lumi::error_handler::LOG_SEVERITY::kERROR);

  ASSERT_EQ(captured_logs_.size(), 2);
  EXPECT_EQ(captured_logs_[1].message_, "Error message");
}

TEST_F(ErrorHandlerTest, FunnyErrorMessages) {
  RegisterCaptureCallback();
  lumi::error_handler::LumiSetFunnyErrorBool(true);
  const std::vector<std::string> k_funny_messages = {"Oops!", "Oh no!",
                                                   "What happened?"};
  lumi::error_handler::LumiRegisterLogMessages(k_funny_messages);

  lumi::LumiSetTestMode(true);
  lumi::error_handler::LumiSetFatalCrash(false);
  lumi::error_handler::LumiLog("Fatal error",
                               lumi::error_handler::LogCode::kINTERNAL_ERROR,
                               lumi::error_handler::LogSeverity::kFATAL);

  ASSERT_EQ(captured_logs_.size(), 1);
  EXPECT_FALSE(captured_logs_[0].funny_message_.empty());

  bool const found_message = false;
  for (const auto &msg : k_funny_messages) {
    if (msg == captured_logs_[0].funny_message_) {
      found_message = true;
      break;
    }
  }
  EXPECT_TRUE(found_message);
}

TEST_F(ErrorHandlerTest, AssertionTests) {
  RegisterCaptureCallback();

  // Test equal assertion
  EXPECT_TRUE(lumi::error_handler::LumiAssert(
      5, 10, lumi::error_handler::AssertType::kEQUAL));

  EXPECT_TRUE(lumi::error_handler::LumiAssert(
      10, 11, lumi::error_handler::AssertType::kGREATER_EQUAL));
  EXPECT_FALSE(lumi::error_handler::LumiAssert(
      10, 11, lumi::error_handler::AssertType::kLOWER_EQUAL));

  // Test greater than assertion
  EXPECT_TRUE(lumi::error_handler::LumiAssert(
      5, 10, lumi::error_handler::AssertType::kGREATER));

  // Test less than assertion
  EXPECT_FALSE(lumi::error_handler::LumiAssert(
      5, 10, lumi::error_handler::AssertType::kLOWER));

  ASSERT_EQ(captured_logs_.size(), 3);
  EXPECT_EQ(captured_logs_[0].code_,
            lumi::error_handler::LogCode::kASSERTION_FAILED);
  EXPECT_EQ(captured_logs_[1].code_,
            lumi::error_handler::LogCode::kASSERTION_FAILED);
}

TEST_F(ErrorHandlerTest, MultipleLogs) {
  RegisterCaptureCallback();

  constexpr int kNumLogs = 100;

  for (int i = 0; i < kNumLogs; ++i) {
    lumi::error_handler::LumiLog("Message " + std::to_string(i),
                                 lumi::error_handler::LogCode::kSUCCESS,
                                 lumi::error_handler::LogSeverity::kINFO);
  }

  EXPECT_EQ(captured_logs_.size(), kNumLogs);
}

TEST_F(ErrorHandlerTest, CallbackExceptionHandling) {
  // Redirect cerr to capture the warning message
  const std::stringstream k_cerr_buffer;
  std::streambuf *old_cerr = std::cerr.rdbuf(k_cerr_buffer.rdbuf());

  // Register a callback that throws
  lumi::error_handler::LumiRegisterLogCallback(
      [](const lumi::error_handler::LogData &) {
        throw std::runtime_error("Test exception");
      });

  // This should not crash
  EXPECT_NO_THROW(lumi::error_handler::LumiLog(
      "Test message", lumi::error_handler::LogCode::kSUCCESS,
      lumi::error_handler::LogSeverity::kINFO));

  // Verify that the warning message was printed
  const std::string k_error_output = k_cerr_buffer.str();
  EXPECT_TRUE(
      k_error_output.find(
          "WARNING: A registered log callback threw a std::exception") !=
      std::string::npos);
  EXPECT_TRUE(k_error_output.find("Test exception") != std::string::npos);

  // Restore cerr
  std::cerr.rdbuf(old_cerr);
}

TEST_F(ErrorHandlerTest, FatalErrorDeathTest) {
  lumi::error_handler::LumiSetFatalCrash(true);  // Enable fatal crash
  lumi::error_handler::LumiSetFatalSeverity(
      lumi::error_handler::LogSeverity::kFATAL);

  // Test that the program terminates with fatal error
  ASSERT_DEATH(
      {
        lumi::error_handler::LumiLog(
            "Fatal error test", lumi::error_handler::LogCode::kINTERNAL_ERROR,
            lumi::error_handler::LogSeverity::kFATAL);
      },
      "Fatal Error Occurred, Can not proceed. Exiting...");
}

TEST_F(ErrorHandlerTest, NonFatalSeverityDoesNotDie) {
  lumi::error_handler::LumiSetFatalCrash(true);
  lumi::error_handler::LumiSetFatalSeverity(
      lumi::error_handler::LogSeverity::kFATAL);

  // This should not crash
  ASSERT_NO_FATAL_FAILURE({
    lumi::error_handler::LumiLog("Non-fatal error",
                                 lumi::error_handler::LogCode::kINTERNAL_ERROR,
                                 lumi::error_handler::LogSeverity::kERROR);
  });
}

TEST_F(ErrorHandlerTest, FatalErrorWithCrashDisabledDoesNotDie) {
  lumi::error_handler::LumiSetFatalCrash(false);  // Disable fatal crash
  lumi::error_handler::LumiSetFatalSeverity(
      lumi::error_handler::LogSeverity::kFATAL);

  // This should not crash when fatal crash is disabled
  ASSERT_NO_FATAL_FAILURE({
    lumi::error_handler::LumiLog("Fatal error with crash disabled",
                                 lumi::error_handler::LogCode::kINTERNAL_ERROR,
                                 lumi::error_handler::LogSeverity::kFATAL);
  });
}

// Test fatal severity threshold
TEST_F(ErrorHandlerTest, CustomFatalSeverityDeathTest) {
  lumi::error_handler::LumiSetFatalCrash(true);
  lumi::error_handler::LumiSetFatalSeverity(
      lumi::error_handler::LogSeverity::kWARNING);

  // Should die because Warning is now considered fatal
  ASSERT_DEATH(
      {
        lumi::error_handler::LumiLog(
            "Warning becomes fatal",
            lumi::error_handler::LogCode::kINTERNAL_ERROR,
            lumi::error_handler::LogSeverity::kWARNING);
      },
      "Fatal Error Occurred, Can not proceed. Exiting...");
}
