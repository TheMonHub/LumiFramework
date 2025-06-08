// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <random>
#include <sstream>
#include <string_view>
#include <thread>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "Lumi/Core/ErrorFunny.h"
#include "Lumi/Core/ErrorHandler.h"

namespace Lumi::ErrorHandler {
	static std::mutex rng_mutex;
	static std::mutex log_mutex;
	static std::mutex config_mutex;
	static std::mutex callback_mutex;

	static std::mt19937 rng{std::random_device{}()};
	static auto LUMI_FATAL_SEVERITY = LogSeverity::Fatal;
	static auto LUMI_LOG_LEVEL = LogSeverity::Info;
	static auto LUMI_ERROR_SEVERITY = LogSeverity::Warning;
	static auto LUMI_FUNNY_ERROR = false;

	static std::vector<LogCallback> s_callbacks;

	std::string_view LUMI_LOG_STRING(const LogCode code) noexcept {
		switch (code) {
			case LogCode::InternalError:
				return "Internal error occurred";
			case LogCode::AssertionFailed:
				return "Assertion failed";
			case LogCode::InvalidArgument:
				return "Invalid argument";
			case LogCode::InaccessibleReference:
				return "Inaccessible reference";
			case LogCode::Success:
				return "Success";
			default:
				return "Unknown error occurred";
		}
	}

	std::string_view LUMI_SEVERITY_STRING(const LogSeverity severity) noexcept {
		switch (severity) {
			case LogSeverity::Info:
				return "Info";
			case LogSeverity::Warning:
				return "Warning";
			case LogSeverity::Error:
				return "Error";
			case LogSeverity::Fatal:
				return "Fatal";
			default:
				return "Unknown severity";
		}
	}

	LogSeverity LUMI_MAP_LOG_SEVERITY(const LogCode code) noexcept {
		switch (code) {
			case LogCode::InternalError:
				return LogSeverity::Error;
			case LogCode::AssertionFailed:
				return LogSeverity::Error;
			case LogCode::InvalidArgument:
				return LogSeverity::Error;
			case LogCode::InaccessibleReference:
				return LogSeverity::Error;
			case LogCode::Success:
				return LogSeverity::Info;
			default:
				return LogSeverity::Unknown;
		}
	}

	void LUMI_LOG_SET_RANDOM_SEED(const unsigned int seed) noexcept {
		std::lock_guard<std::mutex> lock(rng_mutex);
		rng.seed(seed);
	}

	void LUMI_SET_FATAL_SEVERITY(const LogSeverity severity, const bool allowSetInfo) noexcept {
		std::lock_guard<std::mutex> lock(config_mutex);
		switch (severity) {
			case LogSeverity::Info:
				if (!allowSetInfo) {
					return;
				}
				break;
			default:
				break;
		}
		LUMI_FATAL_SEVERITY = severity;
	}

	LogSeverity LUMI_GET_FATAL_SEVERITY() noexcept {
		std::lock_guard<std::mutex> lock(config_mutex);
		return LUMI_FATAL_SEVERITY;
	}

	void LUMI_SET_LOG_LEVEL(const LogSeverity severity) noexcept {
		std::lock_guard<std::mutex> lock(config_mutex);
		LUMI_LOG_LEVEL = severity;
	}

	void LUMI_SET_ERROR_SEVERITY(const LogSeverity severity) noexcept {
		std::lock_guard<std::mutex> lock(config_mutex);
		LUMI_ERROR_SEVERITY = severity;
	}

	LogSeverity LUMI_GET_ERROR_SEVERITY() noexcept {
		std::lock_guard<std::mutex> lock(config_mutex);
		return LUMI_ERROR_SEVERITY;
	}

	LogSeverity LUMI_GET_LOG_LEVEL() noexcept {
		std::lock_guard<std::mutex> lock(config_mutex);
		return LUMI_LOG_LEVEL;
	}

	void LUMI_SET_FUNNY_ERROR_BOOL(const bool funny) noexcept {
		std::lock_guard<std::mutex> lock(config_mutex);
		LUMI_FUNNY_ERROR = funny;
	}

	bool LUMI_GET_FUNNY_ERROR_BOOL() noexcept {
		std::lock_guard<std::mutex> lock(config_mutex);
		return LUMI_FUNNY_ERROR;
	}

	unsigned long get_process_id() noexcept {
#ifdef _WIN32
		return GetCurrentProcessId();
#else
		return static_cast<unsigned long>(getpid());
#endif
	}

	unsigned long long get_thread_id() noexcept {
		std::ostringstream oss;
		oss << std::this_thread::get_id();
		try {
			return std::stoull(oss.str());
		} catch ([[maybe_unused]] const std::exception &e) {
			return 0;
		}
	}

	std::string get_current_timestamp() {
		const auto now = std::chrono::system_clock::now();
		const auto in_time_t = std::chrono::system_clock::to_time_t(now);

		std::stringstream ss;
		ss << std::put_time(std::localtime(&in_time_t), "%H:%M:%S");

		const auto duration = now.time_since_epoch();
		const auto microseconds = (std::chrono::duration_cast<std::chrono::microseconds>(duration) % 1000000).count();
		ss << '.' << std::setfill('0') << std::setw(2) << (microseconds / 10000);
		return ss.str();
	}

	void LUMI_REGISTER_LOG_CALLBACK(LogCallback callback) {
		std::lock_guard<std::mutex> lock(callback_mutex);
		s_callbacks.push_back(std::move(callback));
	}

	void LUMI_CLEAR_LOG_CALLBACKS() noexcept {
		std::lock_guard<std::mutex> lock(callback_mutex);
		s_callbacks.clear();
	}

	void LUMI_LOG(std::string_view message, LogCode code, LogSeverity severity, std::string_view expected,
				  std::string_view actual, AssertType assertType) {
		LogSeverity current_log_level;
		LogSeverity current_error_severity;
		LogSeverity current_fatal_severity;
		bool is_funny_error;
		{
			std::lock_guard<std::mutex> config_lock(config_mutex);
			current_log_level = LUMI_LOG_LEVEL;
			current_error_severity = LUMI_ERROR_SEVERITY;
			current_fatal_severity = LUMI_FATAL_SEVERITY;
			is_funny_error = LUMI_FUNNY_ERROR;
		}

		LogSeverity final_severity = severity;
		if (final_severity == LogSeverity::Unknown) {
			final_severity = LUMI_MAP_LOG_SEVERITY(code);
		}

		if (static_cast<int>(final_severity) < static_cast<int>(current_log_level)) {
			return;
		}

		const auto logMessageCodeString = LUMI_LOG_STRING(code);
		const auto logSeverityString = LUMI_SEVERITY_STRING(final_severity);

		const unsigned long pid = get_process_id();
		const unsigned long long tid = get_thread_id();
		const std::string timestamp = get_current_timestamp();

		std::lock_guard<std::mutex> log_lock(log_mutex);

		std::ostream &logger = (final_severity <= current_error_severity) ? std::cout : std::cerr;
		if (!logger) {
			return;
		}

		logger << "[" << timestamp << " PID:" << pid << " TID:" << tid << " | " << logSeverityString << "] ";

		std::string funny_message_str;

		if (is_funny_error && final_severity >= current_fatal_severity) {
			{
				std::lock_guard<std::mutex> rng_lock(rng_mutex);
				if (!LUMI_FUNNY_ERROR_MESSAGES.empty()) {
					std::uniform_int_distribution<> dist(0, static_cast<int>(LUMI_FUNNY_ERROR_MESSAGES.size() - 1));
					funny_message_str = LUMI_FUNNY_ERROR_MESSAGES[dist(rng)];
				} else {
					funny_message_str = "Error: No funny messages available";
				}
			}
			logger << funny_message_str << " But seriously, ";
		}

		logger << message << " : " << logMessageCodeString << " (Code: " << static_cast<int>(code);
		if (code == LogCode::AssertionFailed) {
			logger << " | Expected: " << expected << " | Value: " << actual;
		}

		logger << ")" << '\n';
		logger.flush();

		{
			const LogData Data = {message, code, final_severity, std::string(expected), std::string(actual),
								  pid,	   tid,	 timestamp,		 funny_message_str,		assertType};

			std::lock_guard<std::mutex> callback_lock(callback_mutex);
			for (const auto &cb: s_callbacks) {
				if (cb) {
					cb(Data);
				}
			}
		}

		if (final_severity >= current_fatal_severity) {
			logger << "Fatal Error Occurred, Can not proceed. Exiting..." << '\n';
			logger.flush();
			exit(static_cast<int>(code));
		}
	}

	std::string LUMI_ASSERT_STRING(const AssertType type) noexcept {
		switch (type) {
			case AssertType::GREATER:
				return "Value greater than ";
			case AssertType::LOWER:
				return "Value lower than ";
			case AssertType::GREATER_EQUAL:
				return "Value greater equal than ";
			case AssertType::LOWER_EQUAL:
				return "Value lower equal than ";
			case AssertType::EQUAL:
			case AssertType::NONE:
			default:
				return "Value equal to ";
		}
	}

	bool LUMI_ASSERT(bool actualValue, bool expectedValue, const AssertType type) {
		if (actualValue == expectedValue) {
			return false;
		}
		LUMI_LOG("Assertion failed", LogCode::AssertionFailed, LogSeverity::Error, std::to_string(expectedValue),
				 std::to_string(actualValue), type);
		return true;
	}

	bool LUMI_ASSERT(int actualValue, int expectedValue, const AssertType type) {
		bool assertion_met = false;
		switch (type) {
			case AssertType::GREATER:
				assertion_met = (actualValue > expectedValue);
				break;
			case AssertType::LOWER:
				assertion_met = (actualValue < expectedValue);
				break;
			case AssertType::GREATER_EQUAL:
				assertion_met = (actualValue >= expectedValue);
				break;
			case AssertType::LOWER_EQUAL:
				assertion_met = (actualValue <= expectedValue);
				break;
			case AssertType::EQUAL:
			case AssertType::NONE:
			default:
				assertion_met = (actualValue == expectedValue);
				break;
		}

		if (assertion_met) {
			return false;
		}

		const std::string expected_str = LUMI_ASSERT_STRING(type) + std::to_string(expectedValue);
		const std::string actual_str = std::to_string(actualValue);

		LUMI_LOG("Assertion failed", LogCode::AssertionFailed, LogSeverity::Error, expected_str, actual_str, type);
		return true;
	}
} // namespace Lumi::ErrorHandler
