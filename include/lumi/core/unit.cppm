// Copyright (c) 2025.
// Distributed under the Boost Software License, Version 1.0

//
// Created by Mono on 29/6/2025.
//

module;

#include <cstdint>

export module lumi.unit;

export namespace lumi::unit {
enum class StorageUnit : uint8_t {
  BYTE,
  KILOBYTE,
  MEGABYTE,
  GIGABYTE,
  TERABYTE,
  PETABYTE
};
uint64_t GetUnitMultiplier(StorageUnit unit);
}  // namespace lumi::unit