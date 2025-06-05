//
// Created by Mono on 24/5/2025.
//
#include "gtest/gtest.h"

#include "Lumi/Core/Core.h"

#include "Lumi/Metadata.h"

using namespace Lumi;
using namespace Lumi::Metadata;

TEST(LumiCoreTest, LicenseCheck) {
	EXPECT_TRUE(Core::LicenseAvailable());
}