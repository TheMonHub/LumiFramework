// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 7/6/2025.
//

#ifndef INFO_H
#define INFO_H

#include <string_view>

namespace Lumi::Info {
	namespace Version {
		enum class VersionTag { None = 0, Dev, Alpha, Beta, ReleaseCandidate, Release };
		std::string_view GetVersionString(bool includeVersionTag = false);
		unsigned int GetVersionMajor();
		unsigned int GetVersionMinor();
		unsigned int GetVersionPatch();
		VersionTag GetVersionTag();
		std::string_view GetVersionTagString();
	} // namespace Version
	namespace License {
		std::string_view GetLicenseString();
		bool IsLicenseAvailable();
	} // namespace License
} // namespace Lumi::Info

#endif // INFO_H
