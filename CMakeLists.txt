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
#   Builds Lumi as a shared library (DLL on Windows, .so on Linux, .dylib on macOS).
# -DLUMI_BUILD_STATIC_LIBS=OFF   (Default: ON if Lumi is the top-level project)
#   Builds Lumi as a static library (.lib on Windows, .a on Linux/macOS).
#
# Feature Building:
# - DLUMI_BUILD_DOCS=OFF         (Default: ON)
#   Builds API documentation using Doxygen.
# - DLUMI_BUILD_EXAMPLES=ON    (Default: OFF)
#   Builds example applications demonstrating Lumi usage.
# -DLUMI_BUILD_TESTS=ON       (Default: OFF)
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
option(LUMI_INSTALL "Generate target for installing Lumi" ${IS_TOP_LEVEL_PROJECT})
option(LUMI_INSTALL_DOCS "Install Lumi documentation" ON)
option(LUMI_INSTALL_EXAMPLES "Install Lumi examples" ON)
option(LUMI_BUILD_DOCS "Build project documentation with Doxygen" ON)
option(LUMI_BUILD_EXAMPLES "Build Lumi examples" OFF)
option(LUMI_BUILD_TESTS "Build Lumi tests" OFF)

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
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG v1.17.0
)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG 3.4
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # To ensure Googletest links against shared C runtime
FetchContent_MakeAvailable(googletest glfw)

#-----------------------------------------------------------------------------
# Library Targets
#-----------------------------------------------------------------------------

set(LUMI_COMMON_EXPORT_SET "LumiFrameworkTargets")
set(LUMI_FRAMEWORK_PUBLIC_HEADERS
        "${CMAKE_SOURCE_DIR}/include/Lumi/export.h"
        "${CMAKE_SOURCE_DIR}/include/Lumi/lumi.h"
)

if (LUMI_FRAMEWORK_PUBLIC_HEADERS)
    install(FILES ${LUMI_FRAMEWORK_PUBLIC_HEADERS}
            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LUMI_VERSIONED_SUBDIR}"
            COMPONENT Lumi-dev)
endif ()

if (LUMI_BUILD_STATIC_LIBS OR LUMI_BUILD_SHARED_LIBS)
    add_subdirectory(src/window)
endif ()

if (LUMI_BUILD_STATIC_LIBS)
    # Concrete static umbrella library that includes a common source file
    add_library(LumiStatic STATIC
            src/lumi.cpp # This file makes it a concrete target
    )
    target_link_libraries(LumiStatic PRIVATE
            LumiStaticWindow
    )
    target_compile_definitions(LumiStatic PUBLIC LUMI_STATIC_DEFINE)
    configure_lumi_target(LumiStatic FALSE
            "${LUMI_FRAMEWORK_PUBLIC_HEADERS}")

    # Generate the export header for this concrete static library
    generate_export_header(LumiStatic
            EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/include/Lumi/Lumi_static_export.h"
            STATIC_DEFINE LUMI_STATIC_DEFINE
            EXPORT_MACRO_NAME LUMI_EXPORT
            DEPRECATED_MACRO_NAME LUMI_DEPRECATED_EXPORT
            NO_EXPORT_MACRO_NAME LUMI_NO_EXPORT)
endif ()

if (LUMI_BUILD_SHARED_LIBS)
    # Concrete shared umbrella library that includes a common source file
    add_library(LumiShared SHARED
            src/lumi.cpp
    )
    target_link_libraries(LumiShared PRIVATE
            LumiSharedWindow
    )
    configure_lumi_target(LumiShared TRUE
            "${LUMI_FRAMEWORK_PUBLIC_HEADERS}")

    # Generate the export header for this concrete shared library
    generate_export_header(LumiShared
            EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/include/Lumi/Lumi_shared_export.h"
            EXPORT_MACRO_NAME LUMI_EXPORT
            DEPRECATED_MACRO_NAME LUMI_DEPRECATED_EXPORT
            NO_EXPORT_MACRO_NAME LUMI_NO_EXPORT)
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
    find_package(Doxygen REQUIRED)
    if (DOXYGEN_FOUND)
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

    # IMPORTANT: Install the generated global export headers
    if (LUMI_BUILD_STATIC_LIBS)
        install(FILES "${CMAKE_BINARY_DIR}/include/Lumi/Lumi_static_export.h"
                DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LUMI_VERSIONED_SUBDIR}/Lumi"
                COMPONENT Lumi-dev)
    endif ()
    if (LUMI_BUILD_SHARED_LIBS)
        install(FILES "${CMAKE_BINARY_DIR}/include/Lumi/Lumi_shared_export.h"
                DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LUMI_VERSIONED_SUBDIR}/Lumi"
                COMPONENT Lumi-dev)
    endif ()

    # Install CMake configuration files
    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/lumi-config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/lumi-config-version.cmake"
            COMPONENT Lumi-dev
            DESTINATION "${LUMI_INSTALL_CMAKEDIR}")

    # Install examples if enabled
    if (LUMI_INSTALL_EXAMPLES)
        install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/examples/"
                DESTINATION "${CMAKE_INSTALL_DATADIR}/${LUMI_VERSIONED_SUBDIR}/examples"
                COMPONENT Lumi-addon)
    endif ()
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
# CPack General Configuration & Generator Selection
#-----------------------------------------------------------------------------
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_VENDOR "${PROJECT_COPYRIGHT_HOLDER}")
set(CPACK_PACKAGE_HOMEPAGE_URL "${PROJECT_HOMEPAGE_URL}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME} ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/res/DESCRIPTION")
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}")
set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/res/icon.png")
set(CPACK_SET_DESTDIR ON)

# --- Platform-specific CPack Generators ---
if (WIN32)
    set(CPACK_GENERATOR "WIX")

    # --- WiX-specific variables ---
    # These are crucial for proper MSI behavior, especially for upgrades.

    # Generate unique GUIDs once and keep them constant for your project.
    # You can generate GUIDs online (search for "GUID generator")
    # This should be done only once and kept consistent across major versions.
    set(CPACK_WIX_UPGRADE_GUID "PLACEHOLDER_GUID")
    set(CPACK_WIX_CULTURES "en-US")
    set(CPACK_WIX_PRODUCT_ICON "${CMAKE_CURRENT_SOURCE_DIR}/res/icon.ico")
    set(CPACK_WIX_UI_REF "WixUI_FeatureTree")
    set(CPACK_WIX_LICENSE_RTF "${CMAKE_CURRENT_SOURCE_DIR}/res/LICENSE.rtf")
    set(CPACK_WIX_PROPERTY_ARPURLINFOABOUT "${PROJECT_HOMEPAGE_URL}")
    set(CPACK_WIX_PROPERTY_ARPCONTACT "mono15.parnthakote@gmail.com")
    set(CPACK_WIX_ALLUSERS "perMachine")
elseif (UNIX)
    set(CPACK_GENERATOR "DEB;RPM;TGZ")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "TheMonHub")
    set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "${PROJECT_HOMEPAGE_URL}")
    set(CPACK_PACKAGE_CONTACT "mono15.parnthakote@gmail.com")
    set(CPACK_DEBIAN_PACKAGE_SECTION "libs")
    set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
elseif (APPLE)
    set(CPACK_GENERATOR "DragNDrop")
    set(CPACK_DMG_VOLUME_NAME "${PROJECT_NAME} ${PROJECT_VERSION}")
endif ()

if (LUMI_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    include(CPack)
endif ()