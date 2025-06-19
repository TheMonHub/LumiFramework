// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 18/6/2025.
//

module lumi.core:info;

import <string_view>;
import <sys/types.h>;
import :metadata;

namespace lumi::info {
static std::string_view GetVersion(const bool include_tag = false) {
  return include_tag ? kVersionFull : kVersion;
}
static uint GetVersionMajor() { return kVersionNumbers.major_; }
static uint GetVersionMinor() { return kVersionNumbers.minor_; }
static uint GetVersionPatch() { return kVersionNumbers.patch_; }

static std::string_view GetFrameworkName() { return kProjectName; }
static std::string_view GetFrameworkDescription() {
  return kProjectDescription;
}
static std::string_view GetFrameworkHomepage() { return kProjectHomepage; }
static std::string_view GetFrameworkCopyrightHolder() {
  return kCopyrightHolder;
}
static std::string_view GetFrameworkLicenseText() { return kLicenseText; }
}  // namespace lumi::info