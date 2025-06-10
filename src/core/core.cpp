// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 10/6/2025.
//

#include <functional>
#include <mutex>
#include <shared_mutex>
#include <vector>
namespace Lumi {
	static std::shared_mutex config_mutex;
	static bool LUMI_TEST_MODE = false;

	void LUMI_SET_TEST_MODE(const bool enabled) noexcept {
		std::unique_lock<std::shared_mutex> lock(config_mutex);
		LUMI_TEST_MODE = enabled;
	}

	bool LUMI_GET_TEST_MODE() noexcept {
		std::shared_lock<std::shared_mutex> lock(config_mutex);
		return LUMI_TEST_MODE;
	}


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
