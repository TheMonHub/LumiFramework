# Lumi Framework - A modular C++ framework for cross-platform desktop applications
# Copyright (c) 2025 TheMonHub
# Licensed under zlib License

#-----------------------------------------------------------------------------
# Quick Start & Build Options
#-----------------------------------------------------------------------------
# To configure, build, and install Lumi:
#
# 1. Configure CMake:
#    cmake -B build -S .
#
# 2. Build the project:
#    cmake --build build
#
# 3. Install Lumi (optional):
#    cmake --install build
#
# 4. Create an installer package (optional):
#    cmake --install build && cd build && cpack -G GENERATOR_NAME
#
# You can customize the build using the following options (set with -D<OPTION>=<VALUE> during cmake configure):
#
# Library Building:
# -DLUMI_BUILD_SHARED_LIBS=OFF  (Default: ON if Lumi is the top-level project)
#   Builds Lumi as shared libraries (DLL on Windows, .so on Linux, .dylib on macOS).
# -DLUMI_BUILD_STATIC_LIBS=OFF  (Default: ON if Lumi is the top-level project)
#   Builds Lumi as static libraries (.lib on Windows, .a on Linux/macOS).
# -DLUMI_BUILD_MONOLITHIC_SHARED_LIB=OFF (Default: ON)
#   Builds a single monolithic shared library (Lumi.dll/.so/.dylib) that includes all components.
#   If this is ON, LUMI_BUILD_SHARED_LIBS for individual components may be ignored in favor of the monolithic build.
# -DLUMI_BUILD_MONOLITHIC_STATIC_LIB=OFF (Default: ON if building static libs)
#   Builds a single monolithic static library (Lumi.lib/.a) that includes all components.
#
# Component Building:
# -DLUMI_BUILD_WINDOW=OFF       (Default: ON)
#
# Feature Building:
# - DLUMI_BUILD_DOCS=OFF        (Default: ON)
#   Builds API documentation using Doxygen.
# - DLUMI_BUILD_EXAMPLES=ON     (Default: OFF)
#   Builds example applications demonstrating Lumi usage.
# -DLUMI_BUILD_TESTS=ON         (Default: OFF)
#   Builds unit tests for Lumi.
#
# Installation:
# -DLUMI_INSTALL=OFF            (Default: ON if Lumi is the top-level project)
#   Enables the 'install' target, allowing you to install Lumi to your system.
# -DLUMI_INSTALL_DOCS=OFF       (Default: ON)
#   Installs the generated Lumi documentation.
# -DLUMI_INSTALL_EXAMPLES=OFF   (Default: ON)
#   Installs the built Lumi examples.

cmake_minimum_required(VERSION 3.16)
project(Lumi
        VERSION 0.1.0
        DESCRIPTION "A modular C++ framework library that streamlines cross-platform desktop application development, cutting boilerplate and empowering developers with deep control."
        HOMEPAGE_URL "https://github.com/TheMonHub/LumiFramework"
        LANGUAGES CXX)


# License and copyright information
set(PROJECT_COPYRIGHT_HOLDER "TheMonHub")

# Determine if Lumi is being built as a standalone project
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" IS_TOP_LEVEL_PROJECT)

# Required CMake modules
include(FetchContent)
include(GNUInstallDirs)
include(cmake/utils.cmake)
include(GenerateExportHeader)

#-----------------------------------------------------------------------------
# Build Options
#-----------------------------------------------------------------------------
option(LUMI_BUILD_STATIC_LIBS "Build Lumi as a static library" ${IS_TOP_LEVEL_PROJECT})
option(LUMI_BUILD_SHARED_LIBS "Build Lumi as a shared library" ${IS_TOP_LEVEL_PROJECT})
option(LUMI_BUILD_MONOLITHIC_SHARED_LIB "Build a single monolithic shared library (Lumi.dll/.so/.dylib) that includes all components" ON)
option(LUMI_BUILD_MONOLITHIC_STATIC_LIB "Build a single monolithic static library (Lumi.lib/.a) that includes all components (interface if not true monolithic)" ON) # Default ON
option(LUMI_INSTALL "Generate target for installing Lumi" ${IS_TOP_LEVEL_PROJECT})
option(LUMI_INSTALL_DOCS "Install Lumi documentation" ON)
option(LUMI_INSTALL_EXAMPLES "Install Lumi examples" ON)
option(LUMI_BUILD_DOCS "Build project documentation with Doxygen" ON)
option(LUMI_BUILD_EXAMPLES "Build Lumi examples" OFF)
option(LUMI_BUILD_TESTS "Build Lumi tests" OFF)

option(LUMI_BUILD_WINDOW "Build Lumi Window component" ON)

# Define installation paths
set(LUMI_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
        CACHE STRING "Install path for Lumi package-related CMake files")
set(LUMI_VERSIONED_SUBDIR "${PROJECT_NAME}/${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

# Core configuration
set_if_undefined(CMAKE_CXX_STANDARD 17)
set_if_undefined(CMAKE_CXX_STANDARD_REQUIRED ON)
set_if_undefined(CMAKE_CXX_EXTENSIONS OFF)

# Configure symbol visibility
set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

#-----------------------------------------------------------------------------
# Developer Build Output Configuration
# Consolidate binaries into predictable subdirectories within the build tree.
#-----------------------------------------------------------------------------
# For static libraries (.a, .lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# For shared libraries (.so, .dylib, and Windows import libs for DLLs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# For executables and shared libraries that are directly runnable (DLLs on Windows)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

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
        message(FATAL_ERROR "Doxygen version 1.10.0 or higher is required for Lumi documentation.")
    endif ()
endif ()

if (LUMI_BUILD_WINDOW)
    FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw
            GIT_TAG 3.4
    )
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "Disable GLFW's documentation build")
    FetchContent_MakeAvailable(glfw)
endif ()

#-----------------------------------------------------------------------------
# Generate Lumi Export Header
#-----------------------------------------------------------------------------
set(LUMI_LICENSE_FILE "${CMAKE_SOURCE_DIR}/LICENSE")
if (EXISTS "${LUMI_LICENSE_FILE}")
    file(READ "${LUMI_LICENSE_FILE}" LUMI_LICENSE_TEXT_CONTENT_RAW)
    # Replace newlines with "\\n" for C++ string literal
    string(REPLACE "\n" "\\n\\\n" LUMI_LICENSE_TEXT_CONTENT_ESCAPED "${LUMI_LICENSE_TEXT_CONTENT_RAW}")
    # Replace double quotes with escaped double quotes
    string(REPLACE "\"" "\\\"" LUMI_LICENSE_TEXT_CONTENT_ESCAPED "${LUMI_LICENSE_TEXT_CONTENT_ESCAPED}")
    set(LUMI_LICENSE_TEXT_CONTENT "${LUMI_LICENSE_TEXT_CONTENT_ESCAPED}")
else ()
    message(WARNING "License file not found at ${LUMI_LICENSE_FILE}. Embedding a default license text.")
    set(LUMI_LICENSE_TEXT_CONTENT "Copyright (c) 2025 TheMonHub\\n\\n"
            "This software is provided 'as-is', without any express or implied warranty.\\n"
            "In no event will the authors be held liable for any damages arising from the use of this software.\\n\\n"
            "Permission is granted to anyone to use this software for any purpose, including commercial applications, \\n"
            "and to alter it and redistribute it freely, subject to the following restrictions:\\n\\n"
            "1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.\\n"
            "2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.\\n"
            "3. This notice may not be removed or altered from any source distribution.")
endif ()

# Make sure the variable is available for configure_file.
set(LUMI_LICENSE_TEXT_FROM_CMAKE "${LUMI_LICENSE_TEXT_CONTENT}")

# --- GLOBAL METADATA HEADER GENERATION ---
# Metadata.h.in template should be at Lumi/include/Metadata.h.in
set(LUMI_GLOBAL_METADATA_TEMPLATE "${CMAKE_SOURCE_DIR}/include/Lumi/Metadata.h.in")
set(LUMI_GENERATED_METADATA_OUTPUT "${CMAKE_BINARY_DIR}/include/Lumi/Metadata.h") # Output to build/Lumi/Metadata.h
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/Lumi") # Ensure the output directory exists

configure_file(
        "${LUMI_GLOBAL_METADATA_TEMPLATE}"
        "${LUMI_GENERATED_METADATA_OUTPUT}"
        @ONLY # Important: Only replace @VAR@ style variables, not ${VAR}
)

#-----------------------------------------------------------------------------
# Library Targets
#-----------------------------------------------------------------------------
set(LUMI_COMMON_EXPORT_SET "LumiFrameworkTargets")

set(LUMI_ALL_PUBLIC_HEADERS "") # Collect all headers for monolithic target's interface
set_property(GLOBAL PROPERTY LUMI_STATIC_LIB_TARGETS "") # Store Lumi::LumiStaticCore, etc.
set_property(GLOBAL PROPERTY LUMI_SHARED_LIB_TARGETS "") # Store Lumi::LumiSharedCore, etc.

# Force static libs if monolithic shared is on (as per original logic)
if (LUMI_BUILD_MONOLITHIC_SHARED_LIB AND NOT LUMI_BUILD_STATIC_LIBS)
    set(LUMI_BUILD_STATIC_LIBS ON CACHE BOOL "Build Lumi as a static library" FORCE)
    message(STATUS "LUMI_BUILD_MONOLITHIC_SHARED_LIB is ON. LUMI_BUILD_STATIC_LIBS forced ON.")
endif ()

# Build individual components
if (LUMI_BUILD_STATIC_LIBS OR LUMI_BUILD_SHARED_LIBS)
    add_subdirectory(src/core)
else ()
    message(STATUS "Skipping individual component library build: LUMI_BUILD_STATIC_LIBS and LUMI_BUILD_SHARED_LIBS are both OFF.")
endif ()

if (LUMI_BUILD_WINDOW)
    # add_subdirectory(src/window)
else ()
    message(STATUS "Skipping Window component build: LUMI_BUILD_WINDOW is OFF.")
endif ()

# Retrieve the accumulated lists of targets from global properties
get_property(LUMI_STATIC_LIB_TARGETS_LIST GLOBAL PROPERTY LUMI_STATIC_LIB_TARGETS)
get_property(LUMI_SHARED_LIB_TARGETS_LIST GLOBAL PROPERTY LUMI_SHARED_LIB_TARGETS)

# Monolithic Shared Library (Lumi::LumiShared)
# This will be the primary "all-in-one" shared library
if (LUMI_BUILD_MONOLITHIC_SHARED_LIB)
    add_library(LumiShared SHARED src/lumi.cpp)
    set_target_properties(LumiShared PROPERTIES OUTPUT_NAME "Lumi")

    # Link all shared components into the monolithic shared library
    target_link_libraries(LumiShared PUBLIC ${LUMI_SHARED_LIB_TARGETS_LIST} ${LUMI_STATIC_LIB_TARGETS_LIST})
    add_library(Lumi::LumiShared ALIAS LumiShared)

    # Configure the monolithic shared library for export
    configure_lumi_target(LumiShared TRUE
            "${LUMI_ALL_PUBLIC_HEADERS}"
            "")
endif ()

# Monolithic Static Library (Lumi::LumiStatic) - As an INTERFACE library to group all static components
# This allows linking all static components using one target.
if (LUMI_BUILD_MONOLITHIC_STATIC_LIB AND LUMI_STATIC_LIB_TARGETS_LIST)
    add_library(LumiStatic INTERFACE)
    target_link_libraries(LumiStatic INTERFACE ${LUMI_STATIC_LIB_TARGETS_LIST})
    add_library(Lumi::LumiStatic ALIAS LumiStatic)
    install(TARGETS LumiStatic EXPORT "${LUMI_COMMON_EXPORT_SET}" COMPONENT Lumi-dev)
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
    set(DOXYFILE_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in")
    set(DOXYFILE_OUT "${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile")
    set(DOXY_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/docs")

    configure_file("${DOXYFILE_IN}" "${DOXYFILE_OUT}" @ONLY)

    add_custom_target(doc ALL
            COMMAND ${DOXYGEN_EXECUTABLE} "${DOXYFILE_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/docs"
            COMMENT "Generating Doxygen documentation"
            VERBATIM)
    if (LUMI_INSTALL_DOCS)
        install(DIRECTORY "${DOXY_OUTPUT_DIR}/"
                DESTINATION "${CMAKE_INSTALL_DOCDIR}/${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
                COMPONENT Lumi-dev)
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

    if (LUMI_BUILD_STATIC_LIBS OR LUMI_BUILD_SHARED_LIBS)
        install(EXPORT "${LUMI_COMMON_EXPORT_SET}"
                COMPONENT Lumi-dev
                FILE "lumi-targets.cmake"
                DESTINATION "${LUMI_INSTALL_CMAKEDIR}"
                NAMESPACE Lumi::)
    endif ()

    # Install CMake configuration files
    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/lumi-config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/lumi-config-version.cmake"
            COMPONENT Lumi-dev
            DESTINATION "${LUMI_INSTALL_CMAKEDIR}")
endif ()

#-----------------------------------------------------------------------------
# CPack Component Configuration
#-----------------------------------------------------------------------------
set(CPACK_COMPONENT_Lumi_DESCRIPTION "Lumi Framework runtime libraries for executing applications.")
set(CPACK_COMPONENT_Lumi_DISPLAY_NAME "Lumi Runtime")
set(CPACK_COMPONENT_Lumi_IS_REQUIRED ON)

set(CPACK_COMPONENT_Lumi-dev_DESCRIPTION "Lumi Framework development files, including headers, import libraries for dynamic linking, static libraries, and CMake configuration for building applications.")
set(CPACK_COMPONENT_Lumi-dev_DISPLAY_NAME "Lumi Development Files")
set(CPACK_COMPONENT_Lumi-dev_DEPENDS Lumi)

set(CPACK_COMPONENT_Lumi-addon_DESCRIPTION "Lumi Framework example applications, including source code and build scripts, to demonstrate usage.")
set(CPACK_COMPONENT_Lumi-addon_DISPLAY_NAME "Lumi Additional")
set(CPACK_COMPONENT_Lumi-addon_DEPENDS Lumi-dev)

set(CPACK_COMPONENTS_ALL "Lumi" "Lumi-dev" "Lumi-addon")

set(CPACK_COMPONENT_Lumi_GROUP "Core Components")
set(CPACK_COMPONENT_Lumi-dev_GROUP "Development Tools")

set(CPACK_COMPONENT_GROUP_Core_Components_DESCRIPTION "Essential runtime files for Lumi Framework.")

#-----------------------------------------------------------------------------
# CPack General Configuration
#-----------------------------------------------------------------------------
# TODO: Add res/icon.png
# TODO: Add res/DESCRIPTION
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_VENDOR "${PROJECT_COPYRIGHT_HOLDER}")
set(CPACK_PACKAGE_HOMEPAGE_URL "${PROJECT_HOMEPAGE_URL}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/res/DESCRIPTION")
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}")
set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/res/icon.png")
set(CPACK_SET_DESTDIR ON)

set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")

if (LUMI_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    include(CPack)
endif ()