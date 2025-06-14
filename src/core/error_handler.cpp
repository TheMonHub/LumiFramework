// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

#include "lumi/core/error_handler.h"

#include <cstdint>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <mutex>
#include <random>
#include <shared_mutex>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "lumi/core/core.h"
#include "lumi/core/info.h"
class NullBuffer final : public std::streambuf {
 protected:
  int overflow(const int k_c) override { return k_c; }
};

std::ostream& GetNullStream() {
  static NullBuffer null_buffer;
  static std::ostream null_stream(&null_buffer);
  return null_stream;
}

namespace {
std::mt19937& GetRandomEngine() {
  static std::mutex mutex;
  std::lock_guard<std::mutex> const k_lock(mutex);
  static std::mt19937 rng{std::random_device{}()};
  return rng;
}
}  // namespace

namespace lumi::error_handler {
static std::mutex rng_mutex;
static std::mutex log_mutex;
static std::shared_mutex config_mutex;
static std::shared_mutex callback_mutex;
static std::mutex message_mutex;

static auto lumi_fatal_severity = LOG_SEVERITY::FATAL;
static auto lumi_log_level = LOG_SEVERITY::INFO;
static auto lumi_error_severity = LOG_SEVERITY::WARNING;
static auto lumi_funny_error = false;
static auto lumi_log_enabled = true;
static auto lumi_fatal_crash = true;

static std::vector<std::string> s_message_storage;
static std::vector<std::string_view> s_message_views;

static std::vector<LogCallback> s_callbacks;

std::string_view LumiLogString(const LOG_CODE code) noexcept {
  switch (code) {
    case LOG_CODE::INTERNAL_ERROR:
      return "Internal error occurred";
    case LOG_CODE::ASSERTION_FAILED:
      return "Assertion failed";
    case LOG_CODE::INVALID_ARGUMENT:
      return "Invalid argument";
    case LOG_CODE::INACCESSIBLE_REFERENCE:
      return "Inaccessible reference";
    case LOG_CODE::SUCCESS:
      return "Success";
    default:
      return "Unknown error occurred";
  }
}

std::string_view LumiSeverityString(const LOG_SEVERITY severity) noexcept {
  switch (severity) {
    case LOG_SEVERITY::INFO:
      return "Info";
    case LOG_SEVERITY::WARNING:
      return "Warning";
    case LOG_SEVERITY::ERROR:
      return "Error";
    case LOG_SEVERITY::FATAL:
      return "Fatal";
    default:
      return "Unknown severity";
  }
}

LOG_SEVERITY LumiMapLogSeverity(const LOG_CODE k_code) noexcept {
  switch (k_code) {
    case LOG_CODE::INTERNAL_ERROR:
      return LOG_SEVERITY::ERROR;
    case LOG_CODE::ASSERTION_FAILED:
      return LOG_SEVERITY::ERROR;
    case LOG_CODE::INVALID_ARGUMENT:
      return LOG_SEVERITY::ERROR;
    case LOG_CODE::INACCESSIBLE_REFERENCE:
      return LOG_SEVERITY::ERROR;
    case LOG_CODE::SUCCESS:
      return LOG_SEVERITY::INFO;
    default:
      return LOG_SEVERITY::UNKNOWN;
  }
}

void LumiLogSetRandomSeed(const unsigned int seed) noexcept {
  std::lock_guard<std::mutex> const k_lock(rng_mutex);
  GetRandomEngine().seed(seed);
}

std::string LumiGetRandomMessage() {
  std::lock_guard<std::mutex> const k_rng_lock(rng_mutex);
  return std::string(s_message_views.empty()
                         ? "Error: No funny messages available"
                         : s_message_views[std::uniform_int_distribution<>(
                               0, static_cast<int>(s_message_views.size() - 1))(
                               GetRandomEngine())]);
}

void LumiSetFatalSeverity(const LOG_SEVERITY severity,
                          const bool allow_set_info) noexcept {
  std::unique_lock<std::shared_mutex> const k_lock(config_mutex);
  if (severity == LOG_SEVERITY::INFO && !allow_set_info) {
    return;
  }
  lumi_fatal_severity = severity;
}

void LumiSetLogEnabled(const bool enabled) noexcept {
  std::unique_lock<std::shared_mutex> const k_lock(config_mutex);
  lumi_log_enabled = enabled;
}

LOG_SEVERITY LumiGetFatalSeverity() noexcept {
  std::shared_lock<std::shared_mutex> const k_lock(config_mutex);
  return lumi_fatal_severity;
}

void LumiSetFatalCrash(const bool k_enabled) noexcept {
  std::shared_lock<std::shared_mutex> const k_lock(config_mutex);
  lumi_fatal_crash = k_enabled;
}

bool LumiGetFatalCrash() noexcept {
  std::shared_lock<std::shared_mutex> const k_lock(config_mutex);
  return lumi_fatal_crash;
}

void LumiSetLogLevel(const LOG_SEVERITY k_severity) noexcept {
  std::unique_lock<std::shared_mutex> const k_lock(config_mutex);
  lumi_log_level = k_severity;
}

void LumiSetErrorSeverity(const LOG_SEVERITY k_severity) noexcept {
  std::unique_lock<std::shared_mutex> const k_lock(config_mutex);
  lumi_error_severity = k_severity;
}

LOG_SEVERITY LumiGetErrorSeverity() noexcept {
  std::shared_lock<std::shared_mutex> const k_lock(config_mutex);
  return lumi_error_severity;
}

LOG_SEVERITY LumiGetLogLevel() noexcept {
  std::shared_lock<std::shared_mutex> const k_lock(config_mutex);
  return lumi_log_level;
}

void LumiSetFunnyErrorBool(const bool k_funny) noexcept {
  std::unique_lock<std::shared_mutex> const k_lock(config_mutex);
  lumi_funny_error = k_funny;
}

bool LumiGetFunnyErrorBool() noexcept {
  std::shared_lock<std::shared_mutex> const k_lock(config_mutex);
  return lumi_funny_error;
}

bool LumiGetLogEnabled() noexcept {
  std::shared_lock<std::shared_mutex> const k_lock(config_mutex);
  return lumi_log_enabled;
}

void LumiRegisterLogMessages(const std::vector<std::string>& messages) {
  std::lock_guard<std::mutex> const k_lock(message_mutex);
  s_message_storage.clear();
  s_message_views.clear();

  s_message_storage.reserve(messages.size());
  s_message_views.reserve(messages.size());

  for (const auto& msg : messages) {
    s_message_storage.emplace_back(msg);
    s_message_views.emplace_back(s_message_storage.back());
  }
}

void LumiClearLogMessages() noexcept {
  s_message_storage.clear();
  s_message_views.clear();
}

void LumiRegisterLogCallback(LogCallback callback) {
  std::unique_lock<std::shared_mutex> const k_lock(callback_mutex);
  s_callbacks.push_back(std::move(callback));
}

void LumiClearLogCallbacks() noexcept {
  std::unique_lock<std::shared_mutex> const k_lock(callback_mutex);
  s_callbacks.clear();
}

std::string LumiAssertString(const ASSERT_TYPE k_type) noexcept {
  switch (k_type) {
    case ASSERT_TYPE::GREATER:
      return "Value greater than ";
    case ASSERT_TYPE::LOWER:
      return "Value lower than ";
    case ASSERT_TYPE::GREATER_EQUAL:
      return "Value greater equal than ";
    case ASSERT_TYPE::LOWER_EQUAL:
      return "Value lower equal than ";
    case ASSERT_TYPE::EQUAL:
    case ASSERT_TYPE::NONE:
    default:
      return "Value equal to ";
  }
}

bool LumiAssert(const bool k_actual_value, const bool k_expected_value) {
  return k_actual_value != k_expected_value;
}

bool LumiAssert(const int k_actual_value, const int k_expected_value,
                const ASSERT_TYPE type) {
  bool assertion_met = false;
  switch (type) {
    case ASSERT_TYPE::GREATER:
      assertion_met = k_actual_value > k_expected_value;
      break;
    case ASSERT_TYPE::LOWER:
      assertion_met = k_actual_value < k_expected_value;
      break;
    case ASSERT_TYPE::GREATER_EQUAL:
      assertion_met = k_actual_value >= k_expected_value;
      break;
    case ASSERT_TYPE::LOWER_EQUAL:
      assertion_met = k_actual_value <= k_expected_value;
      break;
    case ASSERT_TYPE::EQUAL:
    case ASSERT_TYPE::NONE:
    default:
      assertion_met = k_actual_value == k_expected_value;
      break;
  }

  if (assertion_met) {
    return false;
  }

  const std::string k_expected_str =
      LumiAssertString(type) + std::to_string(k_expected_value);
  const std::string k_actual_str = std::to_string(k_actual_value);

  LumiLog("Assertion failed", LOG_CODE::ASSERTION_FAILED, LOG_SEVERITY::ERROR,
          k_expected_str, k_actual_str, type);
  return true;
}
}  // namespace lumi::error_handler
namespace lumi::error_handler {
void HandleLogCallbacks(const LogData& k_data) {
  std::shared_lock<std::shared_mutex> const k_callback_lock(callback_mutex);
  for (const auto& callback : s_callbacks) {
    if (callback) {
      try {
        callback(k_data);
      } catch (const std::exception& e) {
        std::cerr << "[lumi::ErrorHandler] WARNING: A registered log "
                  << "callback threw a std::exception: " << e.what()
                  << ". (Original log code: " << static_cast<int>(k_data.code_)
                  << ")\n";
      } catch (...) {
        std::cerr << "[lumi::ErrorHandler] WARNING: A registered log "
                  << "callback threw an unknown exception. "
                  << "(Original log code: " << static_cast<int>(k_data.code_)
                  << ")\n";
      }
    }
  }
}

std::ostream& GetAppropriateLogger(const bool k_is_test_mode,
                                   const bool k_log_enabled,
                                   const LOG_SEVERITY k_final_severity,
                                   const LOG_SEVERITY k_error_severity) {
  if (k_is_test_mode || !k_log_enabled) {
    return GetNullStream();
  }
  return k_final_severity <= k_error_severity ? std::cout : std::cerr;
}

void WriteLogMessage(
    std::ostream& logger, const std::string& k_timestamp, const uint64_t k_pid,
    const uint64_t k_tid, const std::string_view k_severity_string,
    const bool k_is_funny_error, const LOG_SEVERITY k_final_severity,
    const LOG_SEVERITY k_fatal_severity, const std::string& k_funny_message,
    const std::string_view k_message, const std::string_view k_code_string,
    const LOG_CODE k_code, const std::string_view k_expected,
    const std::string_view k_actual) {
  logger << "[" << k_timestamp << " PID:" << k_pid << " TID:" << k_tid << " | "
         << k_severity_string << "] ";

  if (k_is_funny_error && k_final_severity >= k_fatal_severity) {
    logger << k_funny_message << " But seriously, ";
  }

  logger << k_message << " : " << k_code_string
         << " (Code: " << static_cast<int>(k_code);

  if (k_code == LOG_CODE::ASSERTION_FAILED) {
    logger << " | Expected: " << k_expected << " | Value: " << k_actual;
  }

  logger << ")" << '\n';
  logger.flush();
}

void LumiLog(const std::string_view message, LOG_CODE code,
             const LOG_SEVERITY severity, const std::string_view expected,
             const std::string_view actual, const ASSERT_TYPE k_assert_type) {
  LOG_SEVERITY const final_severity =
      severity == LOG_SEVERITY::UNKNOWN ? LumiMapLogSeverity(code) : severity;

  const LOG_SEVERITY k_current_fatal_severity = LumiGetFatalSeverity();
  const bool k_is_funny_error = LumiGetFunnyErrorBool();
  
  std::string funny_message_str;
  if (k_is_funny_error && final_severity >= k_current_fatal_severity) {
    funny_message_str = LumiGetRandomMessage();
  }

  const LogData k_data = {std::string(message),
                          code,
                          final_severity,
                          std::string(expected),
                          std::string(actual),
                          info::application::GetProcessId(),
                          info::application::GetThreadId(),
                          info::application::GetCurrentTimestamp(),
                          funny_message_str,
                          k_assert_type};

  HandleLogCallbacks(k_data);

  if (static_cast<int>(final_severity) < static_cast<int>(LumiGetLogLevel())) {
    return;
  }

  std::lock_guard<std::mutex> const k_log_lock(log_mutex);

  auto& logger = GetAppropriateLogger(LumiGetTestMode(), LumiGetLogEnabled(),
                                      final_severity, LumiGetErrorSeverity());
  if (!logger) {
    return;
  }

  WriteLogMessage(logger, k_data.k_timestamp_, k_data.pid_, k_data.tid_,
                  LumiSeverityString(final_severity), k_is_funny_error,
                  final_severity, k_current_fatal_severity, funny_message_str,
                  message, LumiLogString(code), code, expected, actual);

  if (final_severity >= k_current_fatal_severity && LumiGetFatalCrash()) {
    std::ostream& fatal_logger =
        LumiGetLogEnabled() ? std::cerr : GetNullStream();
    fatal_logger << "Fatal Error Occurred, Can not proceed. Exiting..." << '\n';
    fatal_logger.flush();
    std::quick_exit(static_cast<int>(code));
  }
}
}  // namespace lumi::error_handler