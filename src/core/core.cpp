//
// Created by Mono on 1/6/2025.
//
#include "Lumi/Core/Core.h"

#include <string_view>
#include "Lumi/Metadata.h"

using namespace Lumi;
using namespace Lumi::Metadata;


namespace Lumi::Core {
	std::string_view GetVersionString() { return LUMI_VERSION_STRING; }
	unsigned int GetVersionMajor() { return LUMI_VERSION_MAJOR; }
	unsigned int GetVersionMinor() { return LUMI_VERSION_MINOR; }
	unsigned int GetVersionPatch() { return LUMI_VERSION_PATCH; }
	std::string_view GetLicense() { return LUMI_LICENSE_TEXT; }
	bool LicenseAvailable() { return !LUMI_LICENSE_TEXT.empty(); }
} // namespace Lumi::Core
