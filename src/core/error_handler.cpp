// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

#include <Lumi/Core/Core.h>
#include <Lumi/Core/Info.h>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <random>
#include <shared_mutex>
#include <string_view>
#include <thread>
#include <vector>

#include "Lumi/Core/ErrorHandler.h"

class NullBuffer final : public std::streambuf {
protected:
	int overflow(const int c) override { return c; }
};

static NullBuffer nullBuffer;
static std::ostream nullStream(&nullBuffer);


namespace Lumi::ErrorHandler {
	static std::mutex rng_mutex;
	static std::mutex log_mutex;
	static std::shared_mutex config_mutex;
	static std::shared_mutex callback_mutex;
	static std::mutex message_mutex;

	static std::mt19937 rng{std::random_device{}()};
	static auto LUMI_FATAL_SEVERITY = LogSeverity::Fatal;
	static auto LUMI_LOG_LEVEL = LogSeverity::Info;
	static auto LUMI_ERROR_SEVERITY = LogSeverity::Warning;
	static auto LUMI_FUNNY_ERROR = false;
	static auto LUMI_LOG_ENABLED = true;

	static std::vector<std::string> s_message_storage;
	static std::vector<std::string_view> s_message_views;


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
		std::unique_lock<std::shared_mutex> lock(config_mutex);
		if (severity == LogSeverity::Info && !allowSetInfo)
			return;
		LUMI_FATAL_SEVERITY = severity;
	}

	void LUMI_SET_LOG_ENABLED(const bool enabled) noexcept {
		std::unique_lock<std::shared_mutex> lock(config_mutex);
		LUMI_LOG_ENABLED = enabled;
	}

	LogSeverity LUMI_GET_FATAL_SEVERITY() noexcept {
		std::shared_lock<std::shared_mutex> lock(config_mutex);
		return LUMI_FATAL_SEVERITY;
	}

	void LUMI_SET_LOG_LEVEL(const LogSeverity severity) noexcept {
		std::unique_lock<std::shared_mutex> lock(config_mutex);
		LUMI_LOG_LEVEL = severity;
	}

	void LUMI_SET_ERROR_SEVERITY(const LogSeverity severity) noexcept {
		std::unique_lock<std::shared_mutex> lock(config_mutex);
		LUMI_ERROR_SEVERITY = severity;
	}

	LogSeverity LUMI_GET_ERROR_SEVERITY() noexcept {
		std::shared_lock<std::shared_mutex> lock(config_mutex);
		return LUMI_ERROR_SEVERITY;
	}

	LogSeverity LUMI_GET_LOG_LEVEL() noexcept {
		std::shared_lock<std::shared_mutex> lock(config_mutex);
		return LUMI_LOG_LEVEL;
	}

	void LUMI_SET_FUNNY_ERROR_BOOL(const bool funny) noexcept {
		std::unique_lock<std::shared_mutex> lock(config_mutex);
		LUMI_FUNNY_ERROR = funny;
	}

	bool LUMI_GET_FUNNY_ERROR_BOOL() noexcept {
		std::shared_lock<std::shared_mutex> lock(config_mutex);
		return LUMI_FUNNY_ERROR;
	}

	bool LUMI_GET_LOG_ENABLED() noexcept {
		std::shared_lock<std::shared_mutex> lock(config_mutex);
		return LUMI_LOG_ENABLED;
	}

	void LUMI_REGISTER_LOG_MESSAGES(const std::vector<std::string_view> &messages) {
		std::lock_guard<std::mutex> lock(message_mutex);
		s_message_storage.clear();
		s_message_views.clear();

		s_message_storage.reserve(messages.size());
		s_message_views.reserve(messages.size());

		for (const auto &msg: messages) {
			s_message_storage.emplace_back(msg);
			s_message_views.emplace_back(s_message_storage.back());
		}
	}

	void LUMI_CLEAR_LOG_MESSAGES() noexcept {
		s_message_storage.clear();
		s_message_views.clear();
	}

	void LUMI_REGISTER_LOG_CALLBACK(LogCallback callback) {
		std::unique_lock<std::shared_mutex> lock(callback_mutex);
		s_callbacks.push_back(std::move(callback));
	}

	void LUMI_CLEAR_LOG_CALLBACKS() noexcept {
		std::unique_lock<std::shared_mutex> lock(callback_mutex);
		s_callbacks.clear();
	}

	void LUMI_LOG(const std::string_view message, LogCode code, const LogSeverity severity,
				  const std::string_view expected, const std::string_view actual, const AssertType assertType) {
		LogSeverity current_log_level;
		LogSeverity current_error_severity;
		LogSeverity current_fatal_severity;
		bool is_funny_error;
		{
			std::shared_lock<std::shared_mutex> config_lock(config_mutex);
			current_log_level = LUMI_LOG_LEVEL;
			current_error_severity = LUMI_ERROR_SEVERITY;
			current_fatal_severity = LUMI_FATAL_SEVERITY;
			is_funny_error = LUMI_FUNNY_ERROR;
		}
		bool is_test_mode;
		{
			std::shared_lock<std::shared_mutex> config_lock(config_mutex);
			is_test_mode = LUMI_GET_TEST_MODE();
		}

		LogSeverity final_severity = severity;
		if (final_severity == LogSeverity::Unknown) {
			final_severity = LUMI_MAP_LOG_SEVERITY(code);
		}

		std::string funny_message_str;
		if (is_funny_error && final_severity >= current_fatal_severity) {
			{
				std::lock_guard<std::mutex> rng_lock(rng_mutex);
				if (!s_message_views.empty()) {
					std::uniform_int_distribution<> dist(0, static_cast<int>(s_message_views.size() - 1));
					funny_message_str = s_message_views[dist(rng)];
				} else {
					funny_message_str = "Error: No funny messages available";
				}
			}
		}

		const auto logMessageCodeString = LUMI_LOG_STRING(code);
		const auto logSeverityString = LUMI_SEVERITY_STRING(final_severity);

		const unsigned long pid = Info::Application::get_process_id();
		const unsigned long long tid = Info::Application::get_thread_id();
		const std::string timestamp = Info::Application::get_current_timestamp();
		{
			const LogData Data = {message, code, final_severity, std::string(expected), std::string(actual),
								  pid,	   tid,	 timestamp,		 funny_message_str,		assertType};

			std::shared_lock<std::shared_mutex> callback_lock(callback_mutex);
			for (const auto &callback: s_callbacks) {
				if (callback) {
					try {
						callback(Data);
					} catch (const std::exception &e) {
						std::cerr << "[Lumi::ErrorHandler] WARNING: A registered log callback threw a std::exception: "
								  << e.what() << ". (Original log code: " << static_cast<int>(Data.code) << ")\n";
					} catch (...) {
						std::cerr << "[Lumi::ErrorHandler] WARNING: A registered log callback threw an unknown "
									 "exception. "
								  << "(Original log code: " << static_cast<int>(Data.code) << ")\n";
					}
				}
			}
		}

		if (static_cast<int>(final_severity) < static_cast<int>(current_log_level) || !LUMI_LOG_ENABLED) {
			return;
		}

		std::lock_guard<std::mutex> log_lock(log_mutex);

		std::ostream &logger = (is_test_mode && final_severity < current_fatal_severity)
									   ? nullStream
									   : ((final_severity <= current_error_severity) ? std::cout : std::cerr);

		if (!logger) {
			return;
		}

		logger << "[" << timestamp << " PID:" << pid << " TID:" << tid << " | " << logSeverityString << "] ";

		if (is_funny_error && final_severity >= current_fatal_severity) {
			logger << funny_message_str << " But seriously, ";
		}

		logger << message << " : " << logMessageCodeString << " (Code: " << static_cast<int>(code);
		if (code == LogCode::AssertionFailed) {
			logger << " | Expected: " << expected << " | Value: " << actual;
		}

		logger << ")" << '\n';
		logger.flush();

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

	bool LUMI_ASSERT(const bool actualValue, const bool expectedValue, const AssertType type) {
		if (actualValue == expectedValue) {
			return false;
		}
		LUMI_LOG("Assertion failed", LogCode::AssertionFailed, LogSeverity::Error, std::to_string(expectedValue),
				 std::to_string(actualValue), type);
		return true;
	}

	bool LUMI_ASSERT(const int actualValue, const int expectedValue, const AssertType type) {
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
