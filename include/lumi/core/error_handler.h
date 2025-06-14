// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 7/6/2025.
//

#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <functional>
#include <string>
#include <string_view>

namespace lumi::error_handler {
enum class LOG_CODE {
  /** General */
  SUCCESS = 0,
  UNKNOWN_ERROR = 1,

  /** Internal Errors */
  INTERNAL_ERROR = 200,
  ASSERTION_FAILED = 201,

  /** Application Errors */
  INVALID_ARGUMENT = 300,
  INACCESSIBLE_REFERENCE = 301,
};

enum class LOG_SEVERITY {
  INFO = 0,
  UNKNOWN = 1,
  WARNING = 2,
  ERROR = 3,
  FATAL = 4,
  NONE = 5
};

enum class ASSERT_TYPE {
  EQUAL,
  GREATER,
  LOWER,
  GREATER_EQUAL,
  LOWER_EQUAL,
  NONE
};

struct LogData {
  std::string message_;
  LOG_CODE code_;
  LOG_SEVERITY severity_;
  std::string expected_;
  std::string actual_;
  unsigned long pid_;
  unsigned long long tid_;
  const std::string k_timestamp_;
  std::string funny_message_;
  ASSERT_TYPE assert_type_;
};

using LogCallback = std::function<void(LogData data)>;

std::string_view LumiLogString(LOG_CODE code = LOG_CODE::UNKNOWN_ERROR) noexcept;
std::string_view LumiSeverityString(
    LOG_SEVERITY severity = LOG_SEVERITY::UNKNOWN) noexcept;

void LumiSetFatalSeverity(LOG_SEVERITY severity = LOG_SEVERITY::FATAL,
                          bool allow_set_info = false) noexcept;
LOG_SEVERITY LumiGetFatalSeverity() noexcept;

void LumiSetFatalCrash(bool enabled) noexcept;
bool LumiGetFatalCrash() noexcept;

void LumiSetLogLevel(LOG_SEVERITY severity = LOG_SEVERITY::UNKNOWN) noexcept;
LOG_SEVERITY LumiGetLogLevel() noexcept;

void LumiSetLogEnabled(bool enabled) noexcept;

void LumiSetErrorSeverity(LOG_SEVERITY severity = LOG_SEVERITY::ERROR) noexcept;
LOG_SEVERITY LumiGetErrorSeverity() noexcept;

void LumiSetFunnyErrorBool(bool funny = false) noexcept;
bool LumiGetFunnyErrorBool() noexcept;

bool LumiGetLogEnabled() noexcept;

LOG_SEVERITY LumiMapLogSeverity(LOG_CODE code) noexcept;

void LumiLogSetRandomSeed(unsigned int seed) noexcept;

std::string LumiGetRandomMessage();

void LumiRegisterLogMessages(const std::vector<std::string> &messages);
void LumiClearLogMessages() noexcept;

void LumiRegisterLogCallback(LogCallback callback);
void LumiClearLogCallbacks() noexcept;

void LumiLog(std::string_view message = "",
             LOG_CODE code = LOG_CODE::UNKNOWN_ERROR,
             LOG_SEVERITY severity = LOG_SEVERITY::UNKNOWN,
             std::string_view expected = "", std::string_view actual = "",
             ASSERT_TYPE k_assert_type = ASSERT_TYPE::NONE);

std::string LumiAssertString(ASSERT_TYPE type) noexcept;

bool LumiAssert(bool k_actual_value, bool k_expected_value);
bool LumiAssert(int k_actual_value, int k_expected_value,
                ASSERT_TYPE type = ASSERT_TYPE::EQUAL);
}  // namespace lumi::error_handler

#endif  // ERRORHANDLER_H
