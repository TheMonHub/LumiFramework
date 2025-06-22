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
    return VERSION_TAG::NONE;
  }
  if constexpr (kVersionTag == "dev") {
    return VERSION_TAG::DEV;
  } else if constexpr (kVersionTag == "alpha") {
    return VERSION_TAG::ALPHA;
  } else if constexpr (kVersionTag == "beta") {
    return VERSION_TAG::BETA;
  } else if constexpr (kVersionTag == "rc") {
    return VERSION_TAG::RELEASE_CANDIDATE;
  } else if constexpr (kVersionTag == "release") {
    return VERSION_TAG::RELEASE;
  }
  return VERSION_TAG::NONE;
}
uint8_t GetVersionReleaseCandidate() noexcept {
  return kVersionReleaseCandidate;
}

BUILD_TYPE GetBuildType() noexcept {
  if constexpr (kBuildType == "Debug") {
    return BUILD_TYPE::DEBUG;
  } else if constexpr (kBuildType == "Release") {
    return BUILD_TYPE::RELEASE;
  } else if constexpr (kBuildType == "RelWithDebInfo") {
    return BUILD_TYPE::REL_WITH_DEB_INFO;
  } else if constexpr (kBuildType == "MinSizeRel") {
    return BUILD_TYPE::MINSIZEREL;
  }
  return BUILD_TYPE::UNKNOWN;
}

bool IsDebugMode() noexcept {
  if (const auto k_build_type_enum = GetBuildType();
      k_build_type_enum == BUILD_TYPE::DEBUG ||
      k_build_type_enum == BUILD_TYPE::REL_WITH_DEB_INFO) {
    return true;
  }
  return false;
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