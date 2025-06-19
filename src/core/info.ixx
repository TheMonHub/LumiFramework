// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 18/6/2025.
//

export module lumi.core:info;

import <string_view>;
import <sys/types.h>;

export import :metadata;

export namespace lumi::info {
static std::string_view GetVersion(bool include_tag = false);
static uint GetVersionMajor();
static uint GetVersionMinor();
static uint GetVersionPatch();
static std::string_view GetFrameworkName();
static std::string_view GetFrameworkDescription();
static std::string_view GetFrameworkHomepage();
static std::string_view GetFrameworkCopyrightHolder();
static std::string_view GetFrameworkLicenseText();
}  // namespace lumi::info
