// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 10/6/2025.
//

#include <functional>
#include <vector>
namespace Lumi {
	static std::vector<std::function<void()>> lumi_init_functions;
	void lumiInitialize() {
		for (const auto &init: lumi_init_functions) {
			if (init)
				init();
		}
	}
	void lumiRegisterInitFunction(const std::function<void()> &init) { lumi_init_functions.push_back(init); }
	namespace Core {
		static std::vector<std::function<void()>> core_init_functions;
		void coreInitialize() {
			for (const auto &init: core_init_functions) {
				if (init)
					init();
			}
		}
		void coreRegisterInitFunction(const std::function<void()> &init) {
			core_init_functions.push_back(init);
			Lumi::lumiRegisterInitFunction(init);
		}
	} // namespace Core
} // namespace Lumi
