// Copyright (c) 2025.
// Distributed under the Boost Software License, Version 1.0

//
// Created by Mono on 18/6/2025.
//

module;

#include <sys/types.h>

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
std::string_view GetVersion(bool include_tag = false);
uint GetVersionMajor();
uint GetVersionMinor();
uint GetVersionPatch();
VERSION_TAG GetVersionTag();
std::string_view GetFrameworkName();
std::string_view GetFrameworkDescription();
std::string_view GetFrameworkHomepage();
std::string_view GetFrameworkCopyrightHolder();
std::string_view GetFrameworkLicense();
std::string_view GetFrameworkLicenseText();

}  // namespace lumi::info
