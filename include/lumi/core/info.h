// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 7/6/2025.
//

#ifndef INFO_H
#define INFO_H

#include <cstdint>
#include <string>

namespace lumi::info {
namespace version {
enum class VERSION_TAG {
  NONE = 0,
  DEV,
  ALPHA,
  BETA,
  RELEASE_CANDIDATE,
  RELEASE
};
std::string GetVersionString(bool include_version_tag = false);
unsigned int GetVersionMajor();
unsigned int GetVersionMinor();
unsigned int GetVersionPatch();
VERSION_TAG GetVersionTag();
std::string GetVersionTagString();
}  // namespace version
namespace license {
std::string GetLicenseString();
bool IsLicenseAvailable();
}  // namespace license
namespace application {
uint64_t GetProcessId() noexcept;
uint64_t GetThreadId() noexcept;
std::string GetCurrentTimestamp();
}  // namespace application
}  // namespace lumi::info

#endif  // INFO_H
