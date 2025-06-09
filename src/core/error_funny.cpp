// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 10/6/2025.
//

#include "Lumi/Core/ErrorFunny.h"

#include "Lumi/Core/ErrorHandler.h"

using namespace Lumi;

namespace Lumi::ErrorHandler {
	void LUMI_REGISTER_DEFAULT_FUNNY_MESSAGES() {
		LUMI_REGISTER_LOG_MESSAGES(LUMI_FUNNY_ERROR_MESSAGES);
		LUMI_LOG("Default funny error messages registered.", LogCode::Success, LogSeverity::Info);
	}
} // namespace Lumi::ErrorHandler
