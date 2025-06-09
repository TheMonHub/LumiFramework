// Copyright (c) 2025 TheMonHub
// Licensed under zlib License

//
// Created by Mono on 10/6/2025.
//

#ifndef CORE_H
#define CORE_H

namespace Lumi {
	void Initialize();
	void RegisterInitFunction(std::function<void()> &init);
	namespace Core {
		void Initialize();
		void RegisterInitFunction(std::function<void()> &init);
	} // namespace Core
} // namespace Lumi

#endif // CORE_H
