// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 7/6/2025.
//

#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

namespace Lumi::ErrorHandler {
	enum class ErrorCode {
		/** General Errors */
		UnknownError = 0,

		/** Internal Errors */
		InternalError = 100,
		AssertionFailed = 101,

		/** Application Errors */
		InvalidArgument = 200,
		InaccessibleReference = 201,
	};
	std::string_view LUMI_ERROR_STRING(ErrorCode code = ErrorCode::UnknownError);

	void LUMI_ERROR(std::string_view message = "", ErrorCode code = ErrorCode::UnknownError, std::string_view info = "",
					bool fatal = true);
} // namespace Lumi::ErrorHandler

#endif // ERRORHANDLER_H
