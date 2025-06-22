// Copyright (c) 2025.
// Distributed under the Boost Software License, Version 1.0

//
// Created by Mono on 18/6/2025.
//
module;

#include <cstdint>
#include <string_view>

module lumi.core;
import :metadata;

namespace lumi::info {
std::string_view GetVersion(const bool include_tag) noexcept {
  return include_tag ? kVersionFull : kVersion;
}
uint8_t GetVersionMajor() noexcept { return kVersionNumbers.major_; }
uint8_t GetVersionMinor() noexcept { return kVersionNumbers.minor_; }
uint8_t GetVersionPatch() noexcept { return kVersionNumbers.patch_; }

VERSION_TAG GetVersionTag() noexcept {
  if constexpr (kVersionTag.empty()) {
    return VERSION_TAG::K_NONE;
  }
  if constexpr (kVersionTag == "dev") {
    return VERSION_TAG::K_DEV;
  } else if constexpr (kVersionTag == "alpha") {
    return VERSION_TAG::K_ALPHA;
  } else if constexpr (kVersionTag == "beta") {
    return VERSION_TAG::K_BETA;
  } else if constexpr (kVersionTag == "rc") {
    return VERSION_TAG::K_RELEASE_CANDIDATE;
  } else if constexpr (kVersionTag == "release") {
    return VERSION_TAG::K_RELEASE;
  }
  return VERSION_TAG::K_NONE;
}
uint8_t GetVersionReleaseCandidate() noexcept {
  return kVersionReleaseCandidate;
}

BUILD_TYPE GetBuildType() noexcept {
  if constexpr (kBuildType == "Debug") {
    return BUILD_TYPE::K_DEBUG;
  } else if constexpr (kBuildType == "Release") {
    return BUILD_TYPE::K_RELEASE;
  } else if constexpr (kBuildType == "RelWithDebInfo") {
    return BUILD_TYPE::K_REL_WITH_DEB_INFO;
  } else if constexpr (kBuildType == "MinSizeRel") {
    return BUILD_TYPE::K_MINSIZEREL;
  }
  return BUILD_TYPE::K_UNKNOWN;
}

bool IsDebugMode() noexcept {
  if (const auto k_build_type_enum = GetBuildType();
      k_build_type_enum == BUILD_TYPE::K_DEBUG ||
      k_build_type_enum == BUILD_TYPE::K_REL_WITH_DEB_INFO) {
    return true;
  }
  return false;
}

std::string_view GetFrameworkName() noexcept { return kProjectName; }
std::string_view GetFrameworkDescription() noexcept {
  return kProjectDescription;
}
std::string_view GetFrameworkHomepage() noexcept { return kProjectHomepage; }
std::string_view GetFrameworkCopyrightHolder() noexcept {
  return kCopyrightHolder;
}
std::string_view GetFrameworkLicense() noexcept {
  return "Boost Software License - Version 1.0";
}
std::string_view GetFrameworkLicenseText() noexcept { return kLicenseText; }
}  // namespace lumi::info