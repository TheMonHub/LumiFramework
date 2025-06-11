// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 10/6/2025.
//

#ifndef CORE_H
#define CORE_H

#include <functional>

namespace Lumi {
	void LUMI_SET_TEST_MODE(bool enabled) noexcept;
	bool LUMI_GET_TEST_MODE() noexcept;

	void lumiInitialize();
	void lumiRegisterInitFunction(std::function<void()> &init);
	namespace Core {
		void coreInitialize();
		void coreRegisterInitFunction(const std::function<void()> &init);
	} // namespace Core
} // namespace Lumi

#endif // CORE_H
