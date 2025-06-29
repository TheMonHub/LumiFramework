// Copyright (c) 2025.
// Distributed under the Boost Software License, Version 1.0

#include "main.h"

#include <iostream>

import lumi.info;
import lumi.unit;

std::ostream& operator<<(std::ostream& os,
                         const lumi::systeminfo::Cpuinfo& info) {
  os << "CPU Information:\n"
     << "  Processor ID: " << info.logical_id_ << "\n"
     << "  Vendor: " << info.vendor_id_ << "\n"
     << "  Model: " << info.model_name_ << "\n"
     << "  Family: " << info.cpu_family_ << "\n"
     << "  Model Number: " << info.model_ << "\n"
     << "  Stepping: " << info.stepping_ << "\n"
     << "  Microcode: " << info.microcode_ << "\n"
     << "  Frequency: " << info.cpu_mhz_ << " MHz\n"
     << "  BogoMIPS: " << info.bogomips_ << "\n"
     << "  Physical ID: " << info.physical_id_ << "\n"
     << "  Siblings: " << info.siblings_ << "\n"
     << "  Core ID: " << info.core_id_ << "\n"
     << "  Physical Cores: " << info.physical_cores_ << "\n"
     << "  APIC ID: " << info.apicid_ << "\n"
     << "  Initial APIC ID: " << info.initial_apicid_ << "\n"
     << "  Cache Size: " << info.cache_size_str_ << "\n"
     << "  Cache Line Size: " << info.clflush_size_ << "\n"
     << "  Cache Alignment: " << info.cache_alignment_ << "\n"
     << "  Address Sizes: " << info.address_sizes_ << "\n"
     << "  FPU Present: " << (info.has_fpu_ ? "Yes" : "No") << "\n";

  if (!info.flags_.empty()) {
    os << "  CPU Flags: " << info.flags_ << "\n";
  }
  if (!info.vmx_flags_.empty()) {
    os << "  VMX Flags: " << info.vmx_flags_ << "\n";
  }
  if (!info.bugs_.empty()) {
    os << "  Known Bugs: " << info.bugs_ << "\n";
  }
  if (!info.power_management_.empty()) {
    os << "  Power Management: " << info.power_management_ << "\n";
  }

  return os;
}

int main() {
  lumi::buildinfo::GetVersion(true);
  std::cout << "Lumi Framework Version: " << lumi::buildinfo::GetVersion(true)
            << "\n"
            << "Build Type: " << lumi::buildinfo::kBuildType << "\n"
            << "Description: " << lumi::buildinfo::GetFrameworkDescription()
            << "\n"
            << "Homepage: " << lumi::buildinfo::GetFrameworkHomepage() << "\n";
  std::cout << "\n"
            << "Copyright holder: "
            << lumi::buildinfo::GetFrameworkCopyrightHolder() << "\n"
            << "License: " << lumi::buildinfo::GetFrameworkLicense() << "\n"
            << lumi::buildinfo::GetFrameworkLicenseText() << "\n\n";
  std::cout << lumi::systeminfo::LinuxGetCpuInfo();
  std::cout << "\n" << GetUnitMultiplier(lumi::unit::StorageUnit::TERABYTE);
}