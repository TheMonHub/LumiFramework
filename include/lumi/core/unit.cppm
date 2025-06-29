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
  BYTE = 0,
  KILOBYTE = 1,
  MEGABYTE = 2,
  GIGABYTE = 3,
  TERABYTE = 4,
  PETABYTE = 5
};
struct UnitConversionParams {
  StorageUnit from_unit_;
  StorageUnit to_unit_;
};
struct UnitConversionParamsUint {
  uint8_t from_exp_;
  uint8_t to_exp_;
};
uint64_t GetUnitMultiplier(uint8_t exp);
uint64_t GetUnitMultiplier(StorageUnit unit);
uint64_t UnitConvert(uint64_t value, UnitConversionParams params);
uint64_t UnitConvert(uint64_t value, UnitConversionParamsUint params);
}  // namespace lumi::unit