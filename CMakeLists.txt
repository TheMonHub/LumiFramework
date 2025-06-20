# lumi Framework - A modular C++ framework for cross-platform desktop applications
# Copyright (c) 2025.
# Distributed under the Boost Software License, Version 1.0

#-----------------------------------------------------------------------------
# Build & Installation Guide
#-----------------------------------------------------------------------------
# Basic Usage:
# 1. Configure:  cmake -S . -B build
# 2. Build:      cmake --build build
# 3. Install:    cmake --install build
# 4. Package:    cd build && cpack -G <GENERATOR>
# 5. Test:       ctest --test-dir build

# Currently supported packaging generators:
# - ZIP
# - TGZ

# Currently supported workflows:
# - Build and install
# - Add as subdirectory
# - Manual linking for non-CMake project

# Build Options:
# -DLUMI_BUILD_ALL=ON/OFF           Force build all components of lumi (Default: OFF)

# core Options:
# -DLUMI_BUILD_STATIC_LIBS=ON/OFF   Build static libraries (Default: ON)

# Components:
# -DLUMI_BUILD_WINDOW=ON/OFF        Build Window component (Default: ON)

# Features:
# -DLUMI_BUILD_DOCS=ON/OFF          Build documentation (Default: ON)
# -DLUMI_BUILD_EXAMPLES=ON/OFF      Build examples (Default: ON if top-level)
# -DLUMI_BUILD_TESTS=ON/OFF         Build tests (Default: ON if top-level)

# Installation:
# -DLUMI_INSTALL=ON/OFF             Install library (Default: ON if top-level)
# -DLUMI_INSTALL_DOCS=ON/OFF        Install documentation (Default: ON)
# -DLUMI_INSTALL_EXAMPLES=ON/OFF    Install examples (Default: ON)

# TODO: Add Window component

cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
project(Lumi
        VERSION 0.1.0
        DESCRIPTION "A modular C++ framework library that streamlines cross-platform desktop application development, cutting boilerplate and empowering developers with deep control."
        HOMEPAGE_URL "https://github.com/TheMonHub/LumiFramework"
        LANGUAGES CXX)

# License and copyright information
set(PROJECT_COPYRIGHT_HOLDER "TheMonHub")

# Determine if lumi is being built as a standalone project
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" IS_TOP_LEVEL_PROJECT)

# Set lumi source directory
set(LUMI_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
message(NOTICE "Lumi source directory: ${LUMI_SOURCE_DIR}")

# Set lumi version tag
# alpha, beta, rc, or dev
set(VERSION_TAG "dev")

if ("${VERSION_TAG}" STREQUAL "alpha")
    set(LUMI_VERSION_TAG "-alpha")
elseif ("${VERSION_TAG}" STREQUAL "beta")
    set(LUMI_VERSION_TAG "-beta")
elseif ("${VERSION_TAG}" STREQUAL "rc")
    set(LUMI_VERSION_TAG "-rc.")
elseif ("${VERSION_TAG}" STREQUAL "dev")
    set(LUMI_VERSION_TAG "-dev")
elseif ("${VERSION_TAG}" STREQUAL "")
    message(WARNING "VERSION_TAG is empty. Please set it to 'alpha', 'beta', 'rc', 'dev', or 'release'. Defaulting to empty tag.")
    set(LUMI_VERSION_TAG "")
else ()
    message(WARNING "Unknown VERSION_TAG '${VERSION_TAG}'. Expected 'alpha', 'beta', 'rc', 'dev', or 'release'.")
    set(LUMI_VERSION_TAG "")
endif ()

# If this is a release candidate, set this to the appropriate version.
# For example, if this is the first release candidate, set it to "1".
set(LUMI_RELEASE_CANDIDATE_VERSION "")
if ("${VERSION_TAG}" STREQUAL "rc")
    if ("${LUMI_RELEASE_CANDIDATE_VERSION}" STREQUAL "")
        message(FATAL_ERROR "LUMI_RELEASE_CANDIDATE_VERSION must be set when VERSION_TAG is 'rc'.")
    endif ()
else ()
    set(LUMI_RELEASE_CANDIDATE_VERSION "")
endif ()

# Set lumi version based on the project version and tag
set(PROJECT_VERSION "${PROJECT_VERSION}${LUMI_VERSION_TAG}${LUMI_RELEASE_CANDIDATE_VERSION}")

# Required CMake modules
include(FetchContent)
include(GNUInstallDirs)
include(cmake/utils.cmake)

#-----------------------------------------------------------------------------
# Build Options
#-----------------------------------------------------------------------------
option(LUMI_BUILD_ALL "Force build all components of Lumi" OFF)
option(LUMI_BUILD_STATIC_LIBS "Build Lumi as static libraries" ON)

option(LUMI_INSTALL "Install Lumi" ${IS_TOP_LEVEL_PROJECT})
option(LUMI_INSTALL_DOCS "Install Lumi documentation" ON)
option(LUMI_INSTALL_EXAMPLES "Install Lumi examples" ${IS_TOP_LEVEL_PROJECT})

option(LUMI_BUILD_DOCS "Build project documentation with Doxygen" ON)
option(LUMI_BUILD_EXAMPLES "Build Lumi examples" OFF)
option(LUMI_BUILD_TESTS "Build Lumi tests" ${IS_TOP_LEVEL_PROJECT})

option(LUMI_BUILD_WINDOW "Build Lumi Window component" ON)

# Define installation paths
set(LUMI_INSTALL_CMAKEDIR "${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
        CACHE STRING "Install path for Lumi package-related CMake files")
set(LUMI_VERSIONED_SUBDIR "${PROJECT_NAME}/${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

# core configuration
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Configure symbol visibility
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

# scan for C++20 modules
set(CXX_SCAN_FOR_MODULES ON)
cmake_policy(SET CMP0155 NEW)

#-----------------------------------------------------------------------------
# Developer Build Output Configuration
# Consolidate binaries into predictable subdirectories within the build tree.
#-----------------------------------------------------------------------------
# For static libraries (.a, .lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# For multi-configuration generators, specify config-specific subdirectories
# This ensures that Debug and Release binaries don't clobber each other.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib/Debug")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib/Release")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/lib/RelWithDebInfo")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/lib/MinSizeRel")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib/Debug")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib/Release")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/lib/RelWithDebInfo")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/lib/MinSizeRel")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/Debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin/RelWithDebInfo")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/bin/MinSizeRel")

#-----------------------------------------------------------------------------
# Post-Configuration Setup
#-----------------------------------------------------------------------------
if (LUMI_BUILD_ALL)
    set(LUMI_BUILD_STATIC_LIBS  ON CACHE BOOL "Build Lumi as static libraries" FORCE)
endif ()

if (LUMI_BUILD_ALL OR LUMI_BUILD_TESTS OR LUMI_BUILD_EXAMPLES)
    set(LUMI_BUILD_STATIC_LIBS  ON CACHE BOOL "Build Lumi as static libraries" FORCE)
    set(LUMI_BUILD_WINDOW ON CACHE BOOL "Build Lumi Window component" FORCE)
    message(STATUS "All build components options are ON.")
endif ()

#-----------------------------------------------------------------------------
# Dependencies
#-----------------------------------------------------------------------------
if (LUMI_BUILD_TESTS)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest
            GIT_TAG v1.17.0
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # To ensure Googletest links against shared C runtime
    FetchContent_MakeAvailable(googletest)
endif ()

if (LUMI_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    message(STATUS "Doxygen found: ${DOXYGEN_EXECUTABLE}, version ${DOXYGEN_VERSION}")
    if (${DOXYGEN_VERSION} VERSION_LESS "1.10.0")
        message(WARNING "Doxygen version 1.10.0 or higher is required for Lumi documentation. Skipping documentation generation.")
        set(LUMI_BUILD_DOCS OFF CACHE BOOL "Disable Lumi documentation build" FORCE)
    endif ()
endif ()

#-----------------------------------------------------------------------------
# Generate lumi Header
#-----------------------------------------------------------------------------
set(LUMI_LICENSE_FILE "${LUMI_SOURCE_DIR}/LICENSE")
if (EXISTS "${LUMI_LICENSE_FILE}")
    file(READ "${LUMI_LICENSE_FILE}" LUMI_LICENSE_TEXT_CONTENT_RAW)
    # Replace newlines with "\\n" for C++ string literal
    string(REPLACE "\n" "\\n\\\n" LUMI_LICENSE_TEXT_CONTENT_ESCAPED "${LUMI_LICENSE_TEXT_CONTENT_RAW}")
    # Replace double quotes with escaped double quotes
    string(REPLACE "\"" "\\\"" LUMI_LICENSE_TEXT_CONTENT_ESCAPED "${LUMI_LICENSE_TEXT_CONTENT_ESCAPED}")
    set(LUMI_LICENSE_TEXT_CONTENT "${LUMI_LICENSE_TEXT_CONTENT_ESCAPED}")
else ()
    message(WARNING "License file not found at ${LUMI_LICENSE_FILE}. Embedding a empty string.")
    set(LUMI_LICENSE_TEXT_CONTENT "")
endif ()

# Make sure the variable is available for configure_file.
set(LUMI_LICENSE_TEXT "${LUMI_LICENSE_TEXT_CONTENT}")

# --- GLOBAL METADATA HEADER GENERATION ---
# metadata.ixx.in template should be at lumi/src/core/metadata.ixx.in
set(LUMI_METADATA_TEMPLATE "${LUMI_SOURCE_DIR}/src/core/metadata.ixx.in")
set(LUMI_GENERATED_METADATA_OUTPUT "${LUMI_SOURCE_DIR}/src/core/metadata.ixx") # Output to include/lumi/metadata.h
configure_file(
        "${LUMI_METADATA_TEMPLATE}"
        "${LUMI_GENERATED_METADATA_OUTPUT}"
        @ONLY
)

#-----------------------------------------------------------------------------
# Library Targets
#-----------------------------------------------------------------------------
set(LUMI_COMMON_EXPORT_SET "LumiFrameworkTargets")

# Collect all source files and public interfaces
set(LUMI_ALL_SOURCES "")
set(LUMI_ALL_PUBLIC_INTERFACES "")

# Global property to accumulate static library targets
set_property(GLOBAL PROPERTY LUMI_STATIC_LIB_TARGETS "")

# Build individual components
if (LUMI_BUILD_STATIC_LIBS)
    add_subdirectory(src/core)
else ()
    message(STATUS "Skipping library build: LUMI_BUILD_STATIC_LIBS is OFF.")
endif ()

if (LUMI_BUILD_WINDOW)
    # add_subdirectory(src/window)
else ()
    message(STATUS "Skipping Window component build: LUMI_BUILD_WINDOW is OFF.")
endif ()

# Retrieve the accumulated lists of targets from global properties
get_property(LUMI_STATIC_LIB_TARGETS_LIST GLOBAL PROPERTY LUMI_STATIC_LIB_TARGETS)

# Print accumulated sources, interfaces, and dependencies
message(STATUS "Lumi sources: ${LUMI_ALL_SOURCES}")
message(STATUS "Lumi interfaces: ${LUMI_ALL_PUBLIC_INTERFACES}")
message(STATUS "Lumi static library targets: ${LUMI_STATIC_LIB_TARGETS_LIST}")

# An INTERFACE library to group all static components
# This allows linking all static components using one target.
if (LUMI_STATIC_LIB_TARGETS_LIST)
    add_library(Lumi INTERFACE)
    target_link_libraries(Lumi INTERFACE ${LUMI_STATIC_LIB_TARGETS_LIST})
    add_library(Lumi::Lumi ALIAS Lumi)
    install(TARGETS Lumi EXPORT "${LUMI_COMMON_EXPORT_SET}")

    message(STATUS "Created Lumi::Lumi interface library to group all static components.")
endif ()

#-----------------------------------------------------------------------------
# Testing and Examples
#-----------------------------------------------------------------------------
if (LUMI_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()
if (LUMI_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

#-----------------------------------------------------------------------------
# Documentation
#-----------------------------------------------------------------------------
if (LUMI_BUILD_DOCS)
    set(DOXYFILE_IN "${LUMI_SOURCE_DIR}/docs/Doxyfile.in")
    set(DOXYFILE_OUT "${CMAKE_BINARY_DIR}/docs/Doxyfile")
    set(DOXY_OUTPUT_DIR "${CMAKE_BINARY_DIR}/docs")

    configure_file("${DOXYFILE_IN}" "${DOXYFILE_OUT}" @ONLY)

    add_custom_target(doc ALL
            COMMAND ${DOXYGEN_EXECUTABLE} "${DOXYFILE_OUT}"
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/docs"
            COMMENT "Generating Doxygen documentation"
            VERBATIM)
    if (LUMI_INSTALL_DOCS)
        install(DIRECTORY "${DOXY_OUTPUT_DIR}/"
                DESTINATION "${CMAKE_INSTALL_DOCDIR}/${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
        install(FILES "${LUMI_SOURCE_DIR}/docs/doxygen-awesome-css-LICENSE.txt"
                DESTINATION "${CMAKE_INSTALL_DOCDIR}/${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
    endif ()
endif ()

#-----------------------------------------------------------------------------
# Installation Configuration
#-----------------------------------------------------------------------------
if (LUMI_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    include(CMakePackageConfigHelpers)

    # Generate CMake config files
    configure_package_config_file(cmake/lumi-config.cmake.in
            lumi-config.cmake
            INSTALL_DESTINATION "${LUMI_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(lumi-config-version.cmake
            COMPATIBILITY SameMajorVersion)

    if (LUMI_BUILD_STATIC_LIBS)
        install(EXPORT "${LUMI_COMMON_EXPORT_SET}"
                FILE "lumi-targets.cmake"
                DESTINATION "${LUMI_INSTALL_CMAKEDIR}"
                NAMESPACE Lumi::)
    endif ()

    install(FILES "${LUMI_SOURCE_DIR}/LICENSE"
            DESTINATION "${CMAKE_INSTALL_DOCDIR}"
            COMPONENT Lumi)

    # Install CMake configuration files
    install(FILES
            "${CMAKE_BINARY_DIR}/lumi-config.cmake"
            "${CMAKE_BINARY_DIR}/lumi-config-version.cmake"
            DESTINATION "${LUMI_INSTALL_CMAKEDIR}")
endif ()

#-----------------------------------------------------------------------------
# CPack Component Configuration
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# CPack General Configuration
#-----------------------------------------------------------------------------
# TODO: Add res/icon.png
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_VENDOR "${PROJECT_COPYRIGHT_HOLDER}")
set(CPACK_PACKAGE_HOMEPAGE_URL "${PROJECT_HOMEPAGE_URL}")
set(CPACK_RESOURCE_FILE_LICENSE "${LUMI_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${LUMI_SOURCE_DIR}/res/DESCRIPTION")
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}")
set(CPACK_PACKAGE_ICON "${LUMI_SOURCE_DIR}/res/icon.png")
set(CPACK_SET_DESTDIR ON)

set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")

if (LUMI_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    include(CPack)
endif ()