# Copyright (c) 2025 TheMonHub
# Licensed under zlib License

cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DLUMI_BUILD_ALL=ON
cmake --build build