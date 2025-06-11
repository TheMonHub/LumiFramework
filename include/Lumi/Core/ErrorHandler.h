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

namespace Lumi::ErrorHandler {
	enum class LogCode {
		/** General */
		Success = 0,
		UnknownError = 1,

		/** Internal Errors */
		InternalError = 200,
		AssertionFailed = 201,

		/** Application Errors */
		InvalidArgument = 300,
		InaccessibleReference = 301,
	};

	enum class LogSeverity { Info = 0, Unknown = 1, Warning = 2, Error = 3, Fatal = 4, None = 5 };

	enum class AssertType { EQUAL, GREATER, LOWER, GREATER_EQUAL, LOWER_EQUAL, NONE };

	struct LogData {
		std::string message;
		LogCode code;
		LogSeverity severity;
		std::string expected;
		std::string actual;
		unsigned long pid;
		unsigned long long tid;
		const std::string timestamp;
		std::string funnyMessage;
		AssertType assertType;
	};

	using LogCallback = std::function<void(LogData Data)>;

	std::string_view LUMI_LOG_STRING(LogCode code = LogCode::UnknownError) noexcept;
	std::string_view LUMI_SEVERITY_STRING(LogSeverity severity = LogSeverity::Unknown) noexcept;

	void LUMI_SET_FATAL_SEVERITY(LogSeverity severity = LogSeverity::Fatal, bool allowSetInfo = false) noexcept;
	LogSeverity LUMI_GET_FATAL_SEVERITY() noexcept;

	void LUMI_SET_LOG_LEVEL(LogSeverity severity = LogSeverity::Unknown) noexcept;
	LogSeverity LUMI_GET_LOG_LEVEL() noexcept;

	void LUMI_SET_LOG_ENABLED(bool enabled) noexcept;

	void LUMI_SET_ERROR_SEVERITY(LogSeverity severity = LogSeverity::Error) noexcept;
	LogSeverity LUMI_GET_ERROR_SEVERITY() noexcept;

	void LUMI_SET_FUNNY_ERROR_BOOL(bool funny = false) noexcept;
	bool LUMI_GET_FUNNY_ERROR_BOOL() noexcept;

	bool LUMI_GET_LOG_ENABLED() noexcept;

	LogSeverity LUMI_MAP_LOG_SEVERITY(LogCode code) noexcept;

	void LUMI_LOG_SET_RANDOM_SEED(unsigned int seed) noexcept;

	void LUMI_REGISTER_LOG_MESSAGES(const std::vector<std::string> &messages);
	void LUMI_CLEAR_LOG_MESSAGES() noexcept;

	void LUMI_REGISTER_LOG_CALLBACK(LogCallback callback);
	void LUMI_CLEAR_LOG_CALLBACKS() noexcept;

	void LUMI_LOG(std::string_view message = "", LogCode code = LogCode::UnknownError,
				  LogSeverity severity = LogSeverity::Unknown, std::string_view expected = "",
				  std::string_view actual = "", AssertType assertType = AssertType::NONE);

	std::string LUMI_ASSERT_STRING(AssertType type) noexcept;

	bool LUMI_ASSERT(bool actualValue, bool expectedValue, AssertType type = AssertType::EQUAL);
	bool LUMI_ASSERT(int actualValue, int expectedValue, AssertType type = AssertType::EQUAL);
} // namespace Lumi::ErrorHandler


#endif // ERRORHANDLER_H
