// Copyright (c) 2025.
// Distributed under the Boost Software License, Version 1.0

//
// Created by Mono on 29/6/2025.
//

module;
#include <pthread.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/utsname.h>

#include <array>
#include <fstream>
#include <mutex>
#include <optional>
#include <string_view>
#include <vector>

module lumi.info;

namespace {
std::optional<struct sysinfo> LoadSystemInfo() {
  struct sysinfo s_sysinfo{};
  if (sysinfo(&s_sysinfo) == 0) {
    return s_sysinfo;
  }
  return std::nullopt;
}

std::string Trim(const std::string &str) {
  const size_t first = str.find_first_not_of(" \t\n\r");
  if (std::string::npos == first) {
    return str;
  }
  const size_t last = str.find_last_not_of(" \t\n\r");
  return str.substr(first, (last - first + 1));
}

std::vector<lumi::systeminfo::Cpuinfo> ParseCpuInfo() {
  std::vector<lumi::systeminfo::Cpuinfo> cpu_data_list;
  std::ifstream cpuinfo_file("/proc/cpuinfo");

  if (!cpuinfo_file.is_open()) {
    return {};
  }

  std::string line;
  lumi::systeminfo::Cpuinfo current_proc_info;

  while (std::getline(cpuinfo_file, line)) {
    if (line.empty()) {
      if (current_proc_info.logical_id_ > 0 ||
          !current_proc_info.vendor_id_.empty()) {
        cpu_data_list.push_back(std::move(current_proc_info));
        current_proc_info = lumi::systeminfo::Cpuinfo{};
      }
      continue;
    }

    const size_t colon_pos = line.find(':');
    if (colon_pos == std::string::npos) {
      continue;
    }

    const std::string key = Trim(line.substr(0, colon_pos));
    const std::string value = Trim(line.substr(colon_pos + 1));

    if (key == "processor") {
      current_proc_info.logical_id_ = std::stoul(value);
    } else if (key == "vendor_id") {
      current_proc_info.vendor_id_ = value;
    } else if (key == "model name") {
      current_proc_info.model_name_ = value;
    } else if (key == "cpu family") {
      current_proc_info.cpu_family_ = std::stoul(value);
    } else if (key == "model") {
      current_proc_info.model_ = std::stoul(value);
    } else if (key == "stepping") {
      current_proc_info.stepping_ = std::stoul(value);
    } else if (key == "microcode") {
      current_proc_info.microcode_ = value;
    } else if (key == "cpu MHz") {
      current_proc_info.cpu_mhz_ = std::stod(value);
    } else if (key == "cache size") {
      current_proc_info.cache_size_str_ = value;
    } else if (key == "physical id") {
      current_proc_info.physical_id_ = std::stoul(value);
    } else if (key == "siblings") {
      current_proc_info.siblings_ = std::stoul(value);
    } else if (key == "core id") {
      current_proc_info.core_id_ = std::stoul(value);
    } else if (key == "cpu cores") {
      current_proc_info.physical_cores_ = std::stoul(value);
    } else if (key == "apicid") {
      current_proc_info.apicid_ = std::stoul(value);
    } else if (key == "initial apicid") {
      current_proc_info.initial_apicid_ = std::stoul(value);
    } else if (key == "bogomips") {
      current_proc_info.bogomips_ = std::stod(value);
    } else if (key == "clflush size") {
      current_proc_info.clflush_size_ = std::stoul(value);
    } else if (key == "cache_alignment") {
      current_proc_info.cache_alignment_ = std::stoul(value);
    } else if (key == "address sizes") {
      current_proc_info.address_sizes_ = value;
    } else if (key == "power management") {
      current_proc_info.power_management_ = value;
    } else if (key == "flags") {
      current_proc_info.flags_ = value;
      if (current_proc_info.flags_.find("fpu") != std::string::npos) {
        current_proc_info.has_fpu_ = true;
      }
    } else if (key == "vmx flags") {
      current_proc_info.vmx_flags_ = value;
    } else if (key == "bugs") {
      current_proc_info.bugs_ = value;
    }
  }
  if (current_proc_info.logical_id_ > 0 ||
      !current_proc_info.vendor_id_.empty()) {
    cpu_data_list.push_back(std::move(current_proc_info));
  }
  return cpu_data_list;
}

struct CachedCpuInfo {
  std::string model_name_;
  lumi::systeminfo::CpuVendor vendor_{lumi::systeminfo::CpuVendor::OTHER};
  std::string vendor_name_;
  uint32_t logical_cores_{0};
  uint32_t physical_cores_{0};
  bool is_cached_{false};
};

std::optional<CachedCpuInfo> g_cpu_info_cache;
std::once_flag g_cpu_info_once_flag;

void InitializeCpuInfoCache() {
  const auto all_cores_info = ParseCpuInfo();
  if (all_cores_info.empty()) {
    return;
  }

  CachedCpuInfo cache;
  cache.is_cached_ = true;
  cache.logical_cores_ = all_cores_info.size();

  const auto &first_proc = all_cores_info.front();
  cache.model_name_ = first_proc.model_name_;
  cache.physical_cores_ = first_proc.physical_cores_;
  cache.vendor_name_ = first_proc.vendor_id_;

  if (cache.vendor_name_ == "GenuineIntel") {
    cache.vendor_ = lumi::systeminfo::CpuVendor::INTEL;
  } else if (cache.vendor_name_ == "AuthenticAMD") {
    cache.vendor_ = lumi::systeminfo::CpuVendor::AMD;
  } else if (cache.vendor_name_.find("Apple") != std::string::npos) {
    cache.vendor_ = lumi::systeminfo::CpuVendor::APPLE;
  } else {
    cache.vendor_ = lumi::systeminfo::CpuVendor::OTHER;
  }

  g_cpu_info_cache = cache;
}

const CachedCpuInfo *GetCachedCpuInfo() {
  std::call_once(g_cpu_info_once_flag, InitializeCpuInfoCache);

  if (g_cpu_info_cache) {
    return &g_cpu_info_cache.value();
  }
  return nullptr;
}

std::optional<lumi::systeminfo::Cpuinfo> LoadCpuInfo() {
  static auto s_cpu_list = ParseCpuInfo();
  if (!s_cpu_list.empty()) {
    return s_cpu_list.front();
  }
  return std::nullopt;
}
}  // namespace

namespace lumi::systeminfo {
Cpuinfo LinuxGetCpuInfo() {
  if (const auto cpu_info = LoadCpuInfo()) {
    return *cpu_info;
  }
  return {};
}
std::string_view GetCpuModelName() {
  if (const auto *const cache = GetCachedCpuInfo()) {
    return cache->model_name_;
  }
  return {};
}

uint16_t GetCpuLogicalCores() {
  if (const auto *const cache = GetCachedCpuInfo()) {
    return static_cast<uint16_t>(cache->logical_cores_);
  }
  return 0;
}

uint16_t GetCpuPhysicalCores() {
  if (const auto *const cache = GetCachedCpuInfo()) {
    return static_cast<uint16_t>(cache->physical_cores_);
  }
  return 0;
}

CpuVendor GetCpuVendor() {
  if (const auto *const cache = GetCachedCpuInfo()) {
    return cache->vendor_;
  }
  return CpuVendor::OTHER;
}

std::string_view GetCpuVendorName() {
  if (const auto *const cache = GetCachedCpuInfo()) {
    return cache->vendor_name_;
  }
  return {};
}

uint64_t GetTotalSystemMemoryBytes() {
  if (const auto sysinfo = LoadSystemInfo()) {
    return sysinfo->totalram * sysinfo->mem_unit;
  }
  return 0;
}
uint64_t GetAvailableSystemMemoryBytes() {
  if (const auto sysinfo = LoadSystemInfo()) {
    return sysinfo->freeram * sysinfo->mem_unit;
  }
  return 0;
}
uint64_t GetTotalSystemMemorySwapSizeBytes() {
  if (const auto sysinfo = LoadSystemInfo()) {
    return sysinfo->totalswap * sysinfo->mem_unit;
  }
  return 0;
}
uint64_t GetAvailableSystemMemorySwapSizeBytes() {
  if (const auto sysinfo = LoadSystemInfo()) {
    return sysinfo->freeswap * sysinfo->mem_unit;
  }
  return 0;
}

uint64_t GetSystemUptimeSeconds() {
  if (const auto sysinfo = LoadSystemInfo()) {
    return sysinfo->uptime;
  }
  return 0;
}
std::string GetHostname();
std::string GetKernelVersion() {
  utsname buffer{};
  if (uname(&buffer) == 0) {
    return std::string{static_cast<const char *>(buffer.release)};
  }
  return {};
}

uint32_t GetTotalRunningProcesses() {
  if (const auto sysinfo = LoadSystemInfo()) {
    return sysinfo->procs;
  }
  return 0;
}

std::string GetExecutablePath() {
  std::array<char, 1024> path_buffer{};

  if (const ssize_t count = readlink("/proc/self/exe", path_buffer.data(),
                                     path_buffer.size() - 1);
      count != -1) {
    return {path_buffer.data(), static_cast<size_t>(count)};
  }
  return {};
}

uint32_t GetCurrentProcessId() { return getpid(); }
uint32_t GetParentProcessId() { return getppid(); }
uint32_t GetCurrentThreadId() { return gettid(); }
}  // namespace lumi::systeminfo