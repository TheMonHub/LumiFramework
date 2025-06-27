// Copyright (c) 2025.
// Distributed under the Boost Software License, Version 1.0

//
// Created by Mono on 18/6/2025.
//

/**
 * @file
 * @brief Contains compile-time information and metadata getters for the Lumi framework
 *
 * This file provides compile-time constants and configuration information about
 * lumi framework's build environment, version numbers, and project metadata.
 * This is recommended to use instead of directly using preprocessor macros.
 * It provides a more structured and type-safe way to access metadata than accessing metadata.cppm directly.
 * @note Recommended to use this instead of directly accessing metadata constants. @see metadata.cppm
 */
module;

#include <cstdint>
#include <string_view>

export module lumi.info:buildinfo;
export import :metadata;

export namespace lumi::buildinfo {
/**
 * @namespace lumi::buildinfo
 * @brief Contains compile-time information and version metadata getters for the Lumi framework
 *
 * This namespace provides compile-time constants and configuration information about
 * the build environment, version numbers, and project metadata.
 */
enum class VersionTag : uint8_t {
  NONE,
  DEV,
  ALPHA,
  BETA,
  RELEASE_CANDIDATE,
  RELEASE
};
enum class BuildType : uint8_t {
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
/// Returns the version of the Lumi framework. @param include_tag If true, includes the version tag in the output.
/// @return Returns a string_view containing the version number in the format "major.minor.patch[-tag (if include_tag is true)][.version (if release candidate)]".
std::string_view GetVersion(bool include_tag = false) noexcept;
/** @name Individual Version Getters
 * Return versions of the Lumi framework as a separated Major, Minor, Patch, Tag and Release Candidate version.
 * @{
 */
uint8_t GetVersionMajor() noexcept;
uint8_t GetVersionMinor() noexcept;
uint8_t GetVersionPatch() noexcept;
VersionTag GetVersionTag() noexcept;
uint8_t GetVersionReleaseCandidate() noexcept;
/** @} */
/** @name Build Information Getters
 * Returns information about the build environment of the Lumi framework.
 * @{
 */
BuildType GetBuildType() noexcept;
std::string_view GetCommitHash() noexcept;
std::string_view GetGitBranch() noexcept;
PLATFORM GetPlatform() noexcept;
ARCHITECTURE GetArchitecture() noexcept;
uint8_t GetBitness() noexcept;
COMPILER GetCompiler() noexcept;
std::string_view GetCompilerName() noexcept;
std::string_view GetCompilerVersion() noexcept;
/*** @} */
/** @name Metadata Getters
 * Returns metadata about the Lumi framework itself.
 * @{
 */
std::string_view GetFrameworkName() noexcept;
std::string_view GetFrameworkDescription() noexcept;
std::string_view GetFrameworkHomepage() noexcept;
std::string_view GetFrameworkCopyrightHolder() noexcept;
std::string_view GetFrameworkLicense() noexcept;
std::string_view GetFrameworkLicenseText() noexcept;
/** @} */
}  // namespace lumi::buildinfo