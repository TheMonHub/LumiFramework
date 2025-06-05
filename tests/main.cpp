//
// Created by Mono on 24/5/2025.
//
#include "gtest/gtest.h"

#include "Lumi/Core/CoreMeta.h"

using namespace Lumi;

TEST(LumiCoreTest, LicenseCheck) { EXPECT_TRUE(Metadata::License::LicenseAvailable()); }
