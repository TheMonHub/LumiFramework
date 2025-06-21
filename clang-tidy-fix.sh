# Copyright (c) 2025 TheMonHub
# Licensed under zlib License

# shellcheck disable=SC2046
cmake -S . -B build -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DLUMI_BUILD_TESTS=ON -DLUMI_BUILD_EXAMPLES=ON -DLUMI_BUILD_ALL=ON -DLUMI_BUILD_DOCS=OFF -D CMAKE_C_COMPILER=$(which clang) -D CMAKE_CXX_COMPILER=$(which clang++) -G Ninja
cmake --build build
# shellcheck disable=SC2046
run-clang-tidy '^(?!.*[\\/]_deps[\\/])' -p build -fix -quiet