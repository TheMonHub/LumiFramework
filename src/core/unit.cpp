// Copyright (c) 2025.
// Distributed under the Boost Software License, Version 1.0

//
// Created by Mono on 29/6/2025.
//

module;
#include <cstdint>
module lumi.unit;

namespace lumi::unit {
uint64_t GetUnitMultiplier(const StorageUnit unit) {
  switch (unit) {
    case StorageUnit::KILOBYTE:
      return 1024;
    case StorageUnit::MEGABYTE:
      return static_cast<uint64_t>(1024) * static_cast<uint64_t>(1024);
    case StorageUnit::GIGABYTE:
      return static_cast<uint64_t>(1024) * static_cast<uint64_t>(1024) *
             static_cast<uint64_t>(1024);
    case StorageUnit::TERABYTE:
      return static_cast<uint64_t>(1024) * static_cast<uint64_t>(1024) *
             static_cast<uint64_t>(1024) * static_cast<uint64_t>(1024);
    case StorageUnit::PETABYTE:
      return static_cast<uint64_t>(1024) * static_cast<uint64_t>(1024) *
             static_cast<uint64_t>(1024) * static_cast<uint64_t>(1024) *
             static_cast<uint64_t>(1024);
    default:
      return 1;  // Default to Byte if unknown or it is BYTE
  }
}
}  // namespace lumi::unit