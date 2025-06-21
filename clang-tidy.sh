# Copyright (c) 2025 TheMonHub
# Licensed under zlib License

cmake -S . -B build cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DLUMI_BUILD_TESTS=ON -DLUMI_BUILD_EXAMPLES=ON -DLUMI_BUILD_ALL=ON -G Ninja
cmake --build build
run-clang-tidy '^(?!.*[\\/]_deps[\\/])' -p build