// Copyright (c) 2025.
// Distributed under the Boost Software License, Version 1.0

//
// Created by Mono on 18/6/2025.
//
module;
#include <cstdint>
#include <string_view>

export module lumi.core:info;

export namespace lumi::info {
enum class VERSION_TAG : uint8_t {
  K_NONE,
  K_DEV,
  K_ALPHA,
  K_BETA,
  K_RELEASE_CANDIDATE,
  K_RELEASE
};
enum class BUILD_TYPE : uint8_t {
  K_DEBUG,
  K_RELEASE,
  K_REL_WITH_DEB_INFO,
  K_MINSIZEREL,
  K_UNKNOWN
};
std::string_view GetVersion(bool include_tag = false) noexcept;
uint8_t GetVersionMajor() noexcept;
uint8_t GetVersionMinor() noexcept;
uint8_t GetVersionPatch() noexcept;
VERSION_TAG GetVersionTag() noexcept;
uint8_t GetVersionReleaseCandidate() noexcept;
BUILD_TYPE GetBuildType() noexcept;
bool IsDebugMode() noexcept;
std::string_view GetFrameworkName() noexcept;
std::string_view GetFrameworkDescription() noexcept;
std::string_view GetFrameworkHomepage() noexcept;
std::string_view GetFrameworkCopyrightHolder() noexcept;
std::string_view GetFrameworkLicense() noexcept;
std::string_view GetFrameworkLicenseText() noexcept;

}  // namespace lumi::info
