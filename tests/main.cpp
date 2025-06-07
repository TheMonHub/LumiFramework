// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 24/5/2025.
//
#include "gtest/gtest.h"

#include "Lumi/Core/Meta.h"

using namespace Lumi;

TEST(LumiCoreTest, LicenseCheck) { EXPECT_TRUE(Information::License::LicenseAvailable()); }
