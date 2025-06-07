// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 7/6/2025.
//

#include <iostream>
#include <string>

#include "Lumi/Core/ErrorHandler.h"

namespace Lumi::ErrorHandler {
	std::string_view LUMI_ERROR_STRING(const ErrorCode code) {
		switch (code) {
			case ErrorCode::InternalError:
				return "Internal error occurred";
			case ErrorCode::AssertionFailed:
				return "Expected value did not match actual value";
			case ErrorCode::InvalidArgument:
				return "Invalid argument";
			case ErrorCode::InaccessibleReference:
				return "Inaccessible reference";
			default:
				return "Unknown error occurred";
		}
	}

	void LUMI_ERROR(std::string_view messageString, const ErrorCode code, const std::string_view info,
					const bool fatal) {
		if (code != ErrorCode::UnknownError) {
			const std::string_view errorString = LUMI_ERROR_STRING(code);
			std::string message = std::string(messageString);
			if (message.empty()) {
				message = "";
			} else {
				message = ", " + message;
			}

			std::cerr << "Error: " << errorString << message << " (Code: " << static_cast<int>(code);

			if (code == ErrorCode::AssertionFailed) {
				std::cerr << ", Expected value: ";
				if (!info.empty()) {
					std::cerr << info;
				} else {
					std::cerr << "N/A";
				}
			}
		} else {
			std::cerr << "Error: Unknown error occurred";
		}
		std::cerr << ")";
		if (fatal) {
			std::cerr << std::endl << "Fatal error occurred. Exiting..." << std::endl;
			exit(static_cast<int>(code));
		}
	}
} // namespace Lumi::ErrorHandler
