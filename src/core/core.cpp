//
// Created by Mono on 1/6/2025.
//
#include "Lumi/Core/Core.h"
#include <string>
#include "Lumi/Metadata.h"

std::string Lumi::Core::GetVersion() { return LUMI_VERSION_STRING; }
std::string Lumi::Core::GetLicense() { return LUMI_LICENSE_TEXT; }
