// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 10/6/2025.
//

#include "lumi/core/core.h"

#include <functional>
#include <mutex>
#include <shared_mutex>
#include <vector>

namespace {
std::shared_mutex config_mutex;
bool lumi_test_mode = false;
std::vector<std::function<void()>> lumi_init_functions;
std::vector<std::function<void()>> core_init_functions;
}  // namespace

namespace lumi {

void LumiSetTestMode(const bool enabled) noexcept {
  std::unique_lock<std::shared_mutex> const k_lock(config_mutex);
  lumi_test_mode = enabled;
}

bool LumiGetTestMode() noexcept {
  std::shared_lock<std::shared_mutex> const k_lock(config_mutex);
  return lumi_test_mode;
}

void LumiInitialize() {
  for (const auto &init : lumi_init_functions) {
    if (init) {
      init();
    }
  }
}
void LumiRegisterInitFunction(const std::function<void()> &init) {
  lumi_init_functions.push_back(init);
}
namespace core {

void CoreInitialize() {
  for (const auto &init : core_init_functions) {
    if (init) {
      init();
    }
  }
}
void CoreRegisterInitFunction(const std::function<void()> &init) {
  core_init_functions.push_back(init);
  LumiRegisterInitFunction(init);
}
}  // namespace core
}  // namespace lumi
