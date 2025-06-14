// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 8/6/2025.
//

#ifndef ERRORFUNNY_H
#define ERRORFUNNY_H

#include "Lumi/Core/ErrorHandler.h"

namespace lumi::error_handler {
const std::vector<std::string>& GetLumiFunnyErrorMessages();
void LumiRegisterDefaultFunnyMessages();
}  // namespace lumi::error_handler

#endif  // ERRORFUNNY_H
