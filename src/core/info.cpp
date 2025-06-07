// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 7/6/2025.
//

#include <cstring>


#include <string_view>
#include "Lumi/Core/ErrorHandler.h"
#include "Lumi/Core/Info.h"
#include "Lumi/Metadata.h"

using namespace Lumi::Info::Raw;
using namespace Lumi::ErrorHandler;

namespace Lumi::Info {
	namespace Version {
		std::string_view GetVersionString(const bool includeVersionTag) {
			if (includeVersionTag) {
				return LUMI_VERSION_FULL_STRING;
			}
			return LUMI_VERSION_STRING;
		}
		unsigned int GetVersionMajor() { return LUMI_VERSION_MAJOR; }
		unsigned int GetVersionMinor() { return LUMI_VERSION_MINOR; }
		unsigned int GetVersionPatch() { return LUMI_VERSION_PATCH; }

		VersionTag GetVersionTag() {
			const std::string_view::const_pointer VersionTagString = LUMI_VERSION_TAG.data();

			if (std::strcmp(VersionTagString, "dev") == 0)
				return VersionTag::Dev;
			if (std::strcmp(VersionTagString, "alpha") == 0)
				return VersionTag::Alpha;
			if (std::strcmp(VersionTagString, "beta") == 0)
				return VersionTag::Beta;
			if (std::strcmp(VersionTagString, "rc") == 0)
				return VersionTag::ReleaseCandidate;
			if (std::strcmp(VersionTagString, "release") == 0)
				return VersionTag::Release;

			return VersionTag::None;
		}

		std::string_view GetVersionTagString() {
			switch (GetVersionTag()) {
				case VersionTag::Dev:
					return "dev";
				case VersionTag::Alpha:
					return "alpha";
				case VersionTag::Beta:
					return "beta";
				case VersionTag::ReleaseCandidate:
					return "rc";
				case VersionTag::Release:
					return "release";
				default:
					return "";
			}
		}

	} // namespace Version
	namespace License {
		std::string_view GetLicenseString() {
			if (IsLicenseAvailable() == false) {
				LUMI_ERROR("License is not available.", ErrorCode::AssertionFailed, "true", false);
				return "";
			}
			return LUMI_LICENSE_TEXT;
		}
		bool IsLicenseAvailable() { return !LUMI_LICENSE_TEXT.empty(); }

	} // namespace License
} // namespace Lumi::Info
