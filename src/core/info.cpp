// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 7/6/2025.
//

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
			static const std::unordered_map<std::string_view, VersionTag> tagMap = {
				{"dev", VersionTag::Dev},
				{"alpha", VersionTag::Alpha},
				{"beta", VersionTag::Beta},
				{"rc", VersionTag::ReleaseCandidate},
				{"release", VersionTag::Release}
			};

			if (const auto it = tagMap.find(LUMI_VERSION_TAG); it != tagMap.end()) {
				return it->second;
			}

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
			if (LUMI_ASSERT(IsLicenseAvailable(), true)) {
				return "";
			}
			return LUMI_LICENSE_TEXT;
		}
		bool IsLicenseAvailable() { return !LUMI_LICENSE_TEXT.empty(); }

	} // namespace License
} // namespace Lumi::Info
