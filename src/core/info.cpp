// Copyright (c) 2025.
// Distributed under the Boost Software License, Version 1.0

//
// Created by Mono on 18/6/2025.
//

module;

# include <string_view>
# include <sys/types.h>

module lumi.core;

import :metadata;
namespace lumi::info {
std::string_view GetVersion(const bool include_tag) {
  return include_tag ? kVersionFull : kVersion;
}
uint GetVersionMajor() { return kVersionNumbers.major_; }
uint GetVersionMinor() { return kVersionNumbers.minor_; }
uint GetVersionPatch() { return kVersionNumbers.patch_; }

VERSION_TAG GetVersionTag() {
  switch (kVersionTag) {
    case "dev":
      return VERSION_TAG::K_DEV;
    case "alpha":
      return VERSION_TAG::K_ALPHA;
    case "beta":
      return VERSION_TAG::K_BETA;
    case "release_candidate":
      return VERSION_TAG::K_RELEASE_CANDIDATE;
    case "release":
      return VERSION_TAG::K_RELEASE;
    default:
      return VERSION_TAG::K_NONE;
  }
}

std::string_view GetFrameworkName() { return kProjectName; }
std::string_view GetFrameworkDescription() {
  return kProjectDescription;
}
std::string_view GetFrameworkHomepage() { return kProjectHomepage; }
std::string_view GetFrameworkCopyrightHolder() {
  return kCopyrightHolder;
}
std::string_view GetFrameworkLicense() { return "Boost Software License - Version 1.0"; }
std::string_view GetFrameworkLicenseText() { return kLicenseText; }
}  // namespace lumi::info