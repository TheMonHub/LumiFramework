# Copyright (c) 2025 TheMonHub
# Licensed under zlib License

cmake -S . -B build -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DLUMI_BUILD_TESTS=ON -DLUMI_BUILD_EXAMPLES=ON -DLUMI_BUILD_ALL=ON -G Ninja
cmake --build build
# shellcheck disable=SC2046
run-clang-tidy '^(?!.*[\\/]_deps[\\/])' -clang-tidy-binary $(which clang-tidy) -p build -fix