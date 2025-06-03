//
// Created by Mono on 31/5/2025.
//

#include "main.h"
#include <iostream>
#include <Core/Core.h>

int main() {
	std::cout << "Lumi Version: " << Lumi::Core::GetVersionString() << std::endl;
	std::cout << Lumi::Core::GetLicense();
}
