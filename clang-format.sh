# Copyright (c) 2025 TheMonHub
# Licensed under zlib License

# shellcheck disable=SC2035
shopt -s globstar
find . -type f \( -name "*.cpp" -o -name "*.h" \) -not -path "*/_deps/*" -not -path "*/llvm/*" -exec clang-format -i -style=file --dry-run --Werror --verbose {} +