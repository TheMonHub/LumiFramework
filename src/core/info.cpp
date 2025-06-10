// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 7/6/2025.
//

#include <chrono>
#include <iomanip>


#include <string_view>
#include <thread>

#include "Lumi/Core/ErrorHandler.h"
#include "Lumi/Core/Info.h"
#include "Lumi/Metadata.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

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
					{"release", VersionTag::Release}};

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
	namespace Application {
		unsigned long get_process_id() noexcept {
#ifdef _WIN32
			return GetCurrentProcessId();
#else
			return static_cast<unsigned long>(getpid());
#endif
		}

		unsigned long long get_thread_id() noexcept {
			std::ostringstream oss;
			oss << std::this_thread::get_id();
			try {
				return std::stoull(oss.str());
			} catch ([[maybe_unused]] const std::exception &e) {
				return 0;
			}
		}

		std::string get_current_timestamp() {
			const auto now = std::chrono::system_clock::now();
			const auto in_time_t = std::chrono::system_clock::to_time_t(now);

			std::stringstream ss;
			ss << std::put_time(std::localtime(&in_time_t), "%H:%M:%S");

			const auto duration = now.time_since_epoch();
			const auto microseconds =
					(std::chrono::duration_cast<std::chrono::microseconds>(duration) % 1000000).count();
			ss << '.' << std::setfill('0') << std::setw(2) << (microseconds / 10000);
			return ss.str();
		}
	} // namespace Application
} // namespace Lumi::Info
