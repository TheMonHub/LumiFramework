// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 31/5/2025.
//

#include "main.h"

#include <Lumi/Core/ErrorFunny.h>
#include <Lumi/Core/ErrorHandler.h>
#include <Lumi/Core/Info.h>
#include <iostream>

int main() {
	Lumi::ErrorHandler::LUMI_SET_FUNNY_ERROR_BOOL(true);
	Lumi::ErrorHandler::LUMI_SET_FATAL_SEVERITY(Lumi::ErrorHandler::LogSeverity::Warning);
	Lumi::ErrorHandler::LUMI_REGISTER_DEFAULT_FUNNY_MESSAGES();
	std::cout << "\n"
			  << "Lumi Version: " << Lumi::Info::Version::GetVersionString(true) << "\n"
			  << std::endl;
	std::cout << Lumi::Info::License::GetLicenseString() << "\n" << std::endl;
}
