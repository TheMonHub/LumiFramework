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

VersionTag GetVersionTag() noexcept {
  if constexpr (kVersionTag.empty()) {
    return VersionTag::NONE;
  }
  if constexpr (kVersionTag == "dev") {
    return VersionTag::DEV;
  } else if constexpr (kVersionTag == "alpha") {
    return VersionTag::ALPHA;
  } else if constexpr (kVersionTag == "beta") {
    return VersionTag::BETA;
  } else if constexpr (kVersionTag == "rc") {
    return VersionTag::RELEASE_CANDIDATE;
  } else if constexpr (kVersionTag == "release") {
    return VersionTag::RELEASE;
  }
  return VersionTag::NONE;
}
uint8_t GetVersionReleaseCandidate() noexcept {
  return kVersionReleaseCandidate;
}

BuildType GetBuildType() noexcept {
  if constexpr (kBuildType == "Debug") {
    return BuildType::DEBUG;
  } else if constexpr (kBuildType == "Release") {
    return BuildType::RELEASE;
  } else if constexpr (kBuildType == "RelWithDebInfo") {
    return BuildType::REL_WITH_DEB_INFO;
  } else if constexpr (kBuildType == "MinSizeRel") {
    return BuildType::MINSIZEREL;
  }
  return BuildType::UNKNOWN;
}

std::string_view GetCommitHash() noexcept { return kCommitHash; }
PLATFORM GetPlatform() noexcept {
  if constexpr (kPlatform == "Linux") {
    return PLATFORM::LINUX;
  } else if constexpr (kPlatform == "Windows") {
    return PLATFORM::WINDOWS;
  } else if constexpr (kPlatform == "Darwin") {
    return PLATFORM::MACOS;
  }
}

std::string_view GetGitBranch() noexcept { return kGitBranch; }

ARCHITECTURE GetArchitecture() noexcept {
  if constexpr (kArchitecture == "x86" || kArchitecture == "i386" ||
                kArchitecture == "X86") {
    return ARCHITECTURE::X86;
  } else if constexpr (kArchitecture == "x86_64" || kArchitecture == "x64" ||
                       kArchitecture == "AMD64" || kArchitecture == "EM64T") {
    return ARCHITECTURE::X86_64;
  } else if constexpr (kArchitecture == "arm") {
    return ARCHITECTURE::ARM;
  } else if constexpr (kArchitecture == "arm64" || kArchitecture == "aarch64" ||
                       kArchitecture == "ARM64") {
    return ARCHITECTURE::ARM64;
  }
  return ARCHITECTURE::UNKNOWN;
}
uint8_t GetBitness() noexcept { return kBitness; }
COMPILER GetCompiler() noexcept {
  if constexpr (kCompiler == "GCC") {
    return COMPILER::GCC;
  } else if constexpr (kCompiler == "Clang") {
    return COMPILER::CLANG;
  } else if constexpr (kCompiler == "MSVC") {
    return COMPILER::MSVC;
  }
  return COMPILER::UNKNOWN;
}
std::string_view GetCompilerName() noexcept { return kCompiler; }

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