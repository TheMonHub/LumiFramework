// Copyright (c) 2025.
// Distributed under the Boost Software License, Version 1.0

#include "main.h"

#include <iostream>
import lumi.core;

int main() {
  lumi::info::GetVersion(true);
  std::cout << "Lumi Framework Version: "
  << lumi::info::GetVersion(true) << "\n"
  << "Build Type: " << lumi::info::kBuildType << "\n"
  << "Description: " << lumi::info::GetFrameworkDescription() << "\n"
  << "Homepage: " << lumi::info::GetFrameworkHomepage() << "\n";
        std::cout << "\n" << "Copyright holder: " << lumi::info::GetFrameworkCopyrightHolder() << "\n"
                << "License: " << "\n" << lumi::info::GetFrameworkLicenseText() << std::endl;
}