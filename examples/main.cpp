// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

#include "main.h"

#include <iostream>

#include "Lumi/Core/error_funny.h"
#include "Lumi/Core/error_handler.h"
#include "Lumi/Core/info.h"

int main() {
  lumi::error_handler::LumiSetFunnyErrorBool(true);
  lumi::error_handler::LumiSetFatalSeverity(
      lumi::error_handler::LOG_SEVERITY::WARNING);
  lumi::error_handler::LumiRegisterDefaultFunnyMessages();

  std::cout << "\n"
            << "lumi Version: " << lumi::info::version::GetVersionString(true)
            << "\n"
            << '\n';
  std::cout << lumi::info::license::GetLicenseString() << "\n" << '\n';

  lumi::error_handler::LumiLog("Oh no!",
                               lumi::error_handler::LOG_CODE::UNKNOWN_ERROR,
                               lumi::error_handler::LOG_SEVERITY::FATAL);
  std::flush(std::cout);
}