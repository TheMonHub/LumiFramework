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

// ReSharper disable once CppDFAConstantFunctionResult
VERSION_TAG GetVersionTag() noexcept {
  // ReSharper disable once CppDFAUnreachableCode
  if constexpr (kVersionTag.empty()) {
    return VERSION_TAG::K_NONE;
  }
  // ReSharper disable once CppDFAUnreachableCode
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

// ReSharper disable once CppDFAConstantFunctionResult
BUILD_TYPE GetBuildType() noexcept {
  if constexpr (kBuildType == "Debug") {
    // ReSharper disable once CppDFAUnreachableCode
    return BUILD_TYPE::K_DEBUG;
  } else if constexpr (kBuildType == "Release") {
    // ReSharper disable once CppDFAUnreachableCode
    return BUILD_TYPE::K_RELEASE;
  } else if constexpr (kBuildType == "RelWithDebInfo") {
    return BUILD_TYPE::K_REL_WITH_DEB_INFO;
    // ReSharper disable once CppDFAUnreachableCode
  } else if constexpr (kBuildType == "MinSizeRel") {
    return BUILD_TYPE::K_MINSIZEREL;
  }
  return BUILD_TYPE::K_UNKNOWN;
}
// ReSharper disable once CppDFAConstantFunctionResult
bool IsDebugMode() noexcept {
  // ReSharper disable once CppDFAConstantConditions
  if (const auto k_build_type_enum = GetBuildType();
      k_build_type_enum == BUILD_TYPE::K_DEBUG ||
      // ReSharper disable once CppDFAConstantConditions
      k_build_type_enum == BUILD_TYPE::K_REL_WITH_DEB_INFO) {
    return true;
  }

  // ReSharper disable once CppDFAUnreachableCode
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