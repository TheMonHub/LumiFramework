// Copyright (c) 2025.
// Distributed under the Boost Software License, Version 1.0

#include "main.h"

#include <iostream>

import lumi.info;

int main() {
  lumi::buildinfo::GetVersion(true);
  std::cout << "Lumi Framework Version: " << lumi::buildinfo::GetVersion(true)
            << "\n"
            << "Build Type: " << lumi::buildinfo::kBuildType << "\n"
            << "Description: " << lumi::buildinfo::GetFrameworkDescription() << "\n"
            << "Homepage: " << lumi::buildinfo::GetFrameworkHomepage() << "\n";
  std::cout << "\n"
            << "Copyright holder: " << lumi::buildinfo::GetFrameworkCopyrightHolder()
            << "\n"
            << "License: " << lumi::buildinfo::GetFrameworkLicense() << "\n"
            << lumi::buildinfo::GetFrameworkLicenseText() << "\n";
}