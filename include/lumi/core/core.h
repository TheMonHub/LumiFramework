// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 10/6/2025.
//

#ifndef CORE_H
#define CORE_H

#include <functional>

namespace lumi {
void LumiSetTestMode(bool enabled) noexcept;
bool LumiGetTestMode() noexcept;

void LumiInitialize();
void LumiRegisterInitFunction(const std::function<void()> &init);
namespace core {
void CoreInitialize();
void CoreRegisterInitFunction(const std::function<void()> &init);
}  // namespace core
}  // namespace lumi

#endif  // CORE_H
