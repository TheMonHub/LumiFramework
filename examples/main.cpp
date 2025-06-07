// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 31/5/2025.
//

#include "main.h"
#include "Lumi/Core/Meta.h"
#include <iostream>

int main() {
	std::cout << "Lumi Version: " << Lumi::Information::Version::GetVersionString() << std::endl;
	std::cout << Lumi::Information::License::GetLicense() << std::endl;
}