// Copyright (c) 2025.
// Distributed under the Boost Software License, Version 1.0

//
// Created by Mono on 29/6/2025.
//

module;
#include <cmath>
#include <cstdint>
#include <iostream>
module lumi.unit;

namespace lumi::unit {
uint64_t GetUnitMultiplier(uint8_t exp) {
  uint64_t result = 1;
  while (exp != 0) {
    result *= 1024;
    --exp;
  }
  return result;
}
uint64_t GetUnitMultiplier(const StorageUnit unit) {
  switch (unit) {
    case StorageUnit::KILOBYTE:
      return 1024;
    case StorageUnit::MEGABYTE:
      return 1048576;
    case StorageUnit::GIGABYTE:
      return 1073741824;
    case StorageUnit::TERABYTE:
      return 1099511627776;
    case StorageUnit::PETABYTE:
      return 1125899906842624;
    default:
      return 1;
  }
}
uint64_t UnitConvert(const uint64_t value,
                     const UnitConversionParams
                         params) {  // NOLINT(*-easily-swappable-parameters)
  const StorageUnit from_unit = params.from_unit_;
  const StorageUnit to_unit = params.to_unit_;

  const uint64_t from_multiplier = GetUnitMultiplier(from_unit);

  if (from_multiplier != 0 &&
      value > std::numeric_limits<uint64_t>::max() / from_multiplier) {
    std::cerr << "Error: Multiplication overflow detected. Cannot convert "
              << value << " from this unit. Returning 0." << '\n';
    return 0;
  }

  const uint64_t value_in_bytes = value * from_multiplier;

  const uint64_t to_multiplier = GetUnitMultiplier(to_unit);

  return value_in_bytes / to_multiplier;
}
uint64_t UnitConvert(const uint64_t value,
                     const UnitConversionParamsUint
                         params) {  // NOLINT(*-easily-swappable-parameters)
  const uint64_t from_multiplier = params.from_exp_;

  if (from_multiplier != 0 &&
      value > std::numeric_limits<uint64_t>::max() / from_multiplier) {
    std::cerr << "Error: Multiplication overflow detected. Cannot convert "
              << value << " from this unit. Returning 0." << '\n';
    return 0;
  }

  const uint64_t value_in_bytes = value * from_multiplier;

  const uint64_t to_multiplier = params.to_exp_;

  return value_in_bytes / to_multiplier;
}
}  // namespace lumi::unit