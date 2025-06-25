// Copyright (c) 2025.
// Distributed under the Boost Software License, Version 1.0

//
// Created by Mono on 18/6/2025.
//

module;
#include <cstdint>
#include <string_view>

export module lumi.core:info;

export namespace lumi {
enum class VERSION_TAG : uint8_t {
  NONE,
  DEV,
  ALPHA,
  BETA,
  RELEASE_CANDIDATE,
  RELEASE
};
enum class BUILD_TYPE : uint8_t {
  DEBUG,
  RELEASE,
  REL_WITH_DEB_INFO,
  MINSIZEREL,
  UNKNOWN
};
enum class PLATFORM : uint8_t {
  WINDOWS,
  LINUX,
  MACOS,
  UNKNOWN
};
enum class ARCHITECTURE : uint8_t {
  X86,
  X86_64,
  ARM,
  ARM64,
  UNKNOWN
};
enum class COMPILER : uint8_t {
  GCC,
  CLANG,
  MSVC,
  UNKNOWN
};
}  // namespace lumi

export namespace lumi::info {
std::string_view GetVersion(bool include_tag = false) noexcept;
uint8_t GetVersionMajor() noexcept;
uint8_t GetVersionMinor() noexcept;
uint8_t GetVersionPatch() noexcept;
VERSION_TAG GetVersionTag() noexcept;
uint8_t GetVersionReleaseCandidate() noexcept;
BUILD_TYPE GetBuildType() noexcept;
std::string_view GetCommitHash() noexcept;
std::string_view GetGitBranch() noexcept;
PLATFORM GetPlatform() noexcept;
ARCHITECTURE GetArchitecture() noexcept;
uint8_t GetBitness() noexcept;
COMPILER GetCompiler() noexcept;
std::string_view GetCompilerName() noexcept;
std::string_view GetCompilerVersion() noexcept;
std::string_view GetFrameworkName() noexcept;
std::string_view GetFrameworkDescription() noexcept;
std::string_view GetFrameworkHomepage() noexcept;
std::string_view GetFrameworkCopyrightHolder() noexcept;
std::string_view GetFrameworkLicense() noexcept;
std::string_view GetFrameworkLicenseText() noexcept;
}  // namespace lumi::info