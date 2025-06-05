//
// Created by Mono on 5/6/2025.
//

#include "Lumi/Core/CoreMeta.h"

#include <string_view>
#include "Lumi/Core/Core.h"

#include "Lumi/Metadata.h"

using namespace Lumi;
using namespace Lumi::Metadata::Information;

namespace Lumi::Metadata::Version {
	std::string_view GetVersionString() { return LUMI_VERSION_STRING; }
	unsigned int GetVersionMajor() { return LUMI_VERSION_MAJOR; }
	unsigned int GetVersionMinor() { return LUMI_VERSION_MINOR; }
	unsigned int GetVersionPatch() { return LUMI_VERSION_PATCH; }
}
namespace Lumi::Metadata::License {
	std::string_view GetLicense() { return LUMI_LICENSE_TEXT; }
	bool LicenseAvailable() { return !LUMI_LICENSE_TEXT.empty(); }
}
