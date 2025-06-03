//
// Created by Mono on 1/6/2025.
//
#include <string>
#include "Lumi/Metadata.h"
#include "Lumi/Core/Core.h"

std::string Lumi::Core::GetVersionString() { return LUMI_VERSION_STRING; }
unsigned int Lumi::Core::GetVersionMajor() { return LUMI_VERSION_MAJOR; }
unsigned int Lumi::Core::GetVersionMinor() { return LUMI_VERSION_MINOR; }
unsigned int Lumi::Core::GetVersionPatch() { return LUMI_VERSION_PATCH; }
std::string Lumi::Core::GetLicense() { return LUMI_LICENSE_TEXT; }
bool Lumi::Core::LicenseAvailable() { return !std::string(LUMI_LICENSE_TEXT).empty(); }