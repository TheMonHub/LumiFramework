// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 7/6/2025.
//

#include "lumi/core/info.h"

#include <chrono>
#include <cstdint>
#include <functional>
#include <iomanip>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_map>

#include "lumi/core/error_handler.h"
#include "lumi/metadata.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using lumi::error_handler::LumiAssert;
using lumi::info::raw::kLumiLicenseText;
using lumi::info::raw::kLumiVersionFullString;
using lumi::info::raw::kLumiVersionMajor;
using lumi::info::raw::kLumiVersionMinor;
using lumi::info::raw::kLumiVersionPatch;
using lumi::info::raw::kLumiVersionString;
using lumi::info::raw::kLumiVersionTag;

namespace lumi::info {
namespace version {
std::string GetVersionString(const bool k_include_version_tag) {
  if (k_include_version_tag) {
    return std::string(kLumiVersionFullString);
  }
  return std::string(kLumiVersionString);
}
unsigned int GetVersionMajor() { return kLumiVersionMajor; }
unsigned int GetVersionMinor() { return kLumiVersionMinor; }
unsigned int GetVersionPatch() { return kLumiVersionPatch; }

VERSION_TAG GetVersionTag() {
  static const std::unordered_map<std::string_view, VERSION_TAG> kTagMap = {
      {"dev", VERSION_TAG::DEV},
      {"alpha", VERSION_TAG::ALPHA},
      {"beta", VERSION_TAG::BETA},
      {"rc", VERSION_TAG::RELEASE_CANDIDATE},
      {"release", VERSION_TAG::RELEASE}};

  if (const auto k_it = kTagMap.find(kLumiVersionTag); k_it != kTagMap.end()) {
    return k_it->second;
  }

  return VERSION_TAG::NONE;
}

std::string GetVersionTagString() {
  switch (GetVersionTag()) {
    case VERSION_TAG::DEV:
      return "dev";
    case VERSION_TAG::ALPHA:
      return "alpha";
    case VERSION_TAG::BETA:
      return "beta";
    case VERSION_TAG::RELEASE_CANDIDATE:
      return "rc";
    case VERSION_TAG::RELEASE:
      return "release";
    default:
      return "";
  }
}

}  // namespace version
namespace license {
std::string GetLicenseString() {
  if (LumiAssert(IsLicenseAvailable(), true)) {
    return "";
  }
  return std::string(kLumiLicenseText);
}
bool IsLicenseAvailable() { return !kLumiLicenseText.empty(); }

}  // namespace license
namespace application {
uint64_t GetProcessId() noexcept {
#ifdef _WIN32
  return GetCurrentProcessId();
#else
  return static_cast<uint64_t>(getpid());
#endif
}

uint64_t GetThreadId() noexcept {
  // Get thread id
  const auto thread_id = std::this_thread::get_id();

  // Convert thread id to size_t using hash
  constexpr std::hash<std::thread::id> kHasher;
  return kHasher(thread_id);
}

std::string GetCurrentTimestamp() {
  const auto k_now = std::chrono::system_clock::now();
  const auto k_in_time_t = std::chrono::system_clock::to_time_t(k_now);

  std::tm time_info{};
#ifdef _WIN32
  if (localtime_r(&k_in_time_t, &time_info) == nullptr) {
    return "ERROR:TIME";
  }
#else
  if (localtime_r(&k_in_time_t, &time_info) == nullptr) {
    return "ERROR:TIME";
  }
#endif

  std::stringstream ss;
  ss << std::put_time(&time_info, "%H:%M:%S");

  const auto k_duration = k_now.time_since_epoch();
  const auto k_microseconds =
      (std::chrono::duration_cast<std::chrono::microseconds>(k_duration) %
       1000000)
          .count();
  ss << '.' << std::setfill('0') << std::setw(2) << (k_microseconds / 10000);
  return ss.str();
}
}  // namespace application
}  // namespace lumi::info