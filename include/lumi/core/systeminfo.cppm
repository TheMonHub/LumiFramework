// Copyright (c) 2025.
// Distributed under the Boost Software License, Version 1.0

//
// Created by Mono on 26/6/2025.
//

/**
* @file
* @brief Contains runtime information getters for the Lumi framework
*
* This file provides runtime information about the execution environment, such as
* Memory, CPU, OS details, etc.
*/

module;

#include <cstdint>
#include <string>
#include <string_view>

export module lumi.info:systeminfo;

export namespace lumi::systeminfo {
struct Cpuinfo {
  uint32_t logical_id_ = 0;
  std::string vendor_id_;
  std::string model_name_;
  uint32_t cpu_family_ = 0;
  uint32_t model_ = 0;
  uint32_t stepping_ = 0;
  std::string microcode_;

  double cpu_mhz_ = 0.0;
  double bogomips_ = 0.0;
  uint32_t physical_id_ = 0;
  uint32_t siblings_ = 0;
  uint32_t core_id_ = 0;
  uint32_t physical_cores_ = 0;
  uint32_t apicid_ = 0;
  uint32_t initial_apicid_ = 0;

  std::string cache_size_str_;
  uint32_t clflush_size_ = 0;
  uint32_t cache_alignment_ = 0;
  std::string address_sizes_;

  std::string flags_;
  std::string vmx_flags_;
  std::string bugs_;

  std::string power_management_;
  bool has_fpu_ = false;
};
enum class CpuVendor : uint8_t {
  INTEL,
  AMD,
  APPLE,
  QUALCOMM,
  OTHER
};

Cpuinfo LinuxGetCpuInfo();

std::string_view GetCpuModelName();
uint16_t GetCpuLogicalCores();
uint16_t GetCpuPhysicalCores();
CpuVendor GetCpuVendor();
std::string_view GetCpuVendorName();

uint64_t GetTotalSystemMemoryBytes();
uint64_t GetAvailableSystemMemoryBytes();
uint64_t GetTotalSystemMemorySwapSizeBytes();
uint64_t GetAvailableSystemMemorySwapSizeBytes();

uint64_t GetSystemUptimeSeconds();
std::string GetHostname();
std::string GetKernelVersion();

uint32_t GetTotalRunningProcesses();

std::string GetExecutablePath();
uint32_t GetCurrentProcessId();
uint32_t GetParentProcessId();
uint32_t GetCurrentThreadId();
}  // namespace lumi::systeminfo