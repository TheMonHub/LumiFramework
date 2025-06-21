// Copyright (c) 2025.
// Distributed under the Boost Software License, Version 1.0

//
// Created by Mono on 20/6/2025.
//
module;
#include <string_view>
#include <vector>

export module lumi.core:error_funny;


export namespace lumi::error_handler {
std::vector<std::string_view> GetLumiFunnyErrorMessages();
void LumiRegisterDefaultFunnyMessages();
}