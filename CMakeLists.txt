# Lumi Framework - A modular C++ framework for cross-platform desktop applications
# Copyright (c) 2025 TheMonHub
# Licensed under MIT License

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
# - DLUMI_BUILD_SHARED_LIBS=OFF  (Default: ON if Lumi is the top-level project)
#   Builds Lumi as a shared library (DLL on Windows, .so on Linux, .dylib on macOS).
# - DLUMI_BUILD_STATIC_LIBS=OFF   (Default: ON if Lumi is the top-level project)
#   Builds Lumi as a static library (.lib on Windows, .a on Linux/macOS).
#
# Feature Building:
# - DLUMI_BUILD_DOCS=OFF         (Default: ON)
#   Builds API documentation using Doxygen.
# - DLUMI_BUILD_EXAMPLES=ON    (Default: OFF)
#   Builds example applications demonstrating Lumi usage.
# - DLUMI_BUILD_TESTS=ON       (Default: OFF)
#   Builds unit tests for Lumi.
#
# Installation:
# - DLUMI_INSTALL=OFF            (Default: ON if Lumi is the top-level project)
#   Enables the 'install' target, allowing you to install Lumi to your system.
# - DLUMI_INSTALL_DOCS=OFF       (Default: ON)
#   Installs the generated Lumi documentation.
# - DLUMI_INSTALL_EXAMPLES=OFF   (Default: ON)
#   Installs the built Lumi examples.

cmake_minimum_required(VERSION 3.16)
project(Lumi
        VERSION 0.1.0
        DESCRIPTION "A modular C++ framework library that streamlines cross-platform desktop application development, cutting boilerplate and empowering developers with deep control."
        HOMEPAGE_URL "https://github.com/TheMonHub/LumiFramework"
        LANGUAGES CXX)

# Core configuration
set(CMAKE_CXX_STANDARD 17)

# Determine if Lumi is being built as a standalone project
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" IS_TOP_LEVEL_PROJECT)
# Set the base directory for FetchContent downloads
set(FETCHCONTENT_BASE_DIR "${CMAKE_BINARY_DIR}/extern")

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
set(LUMI_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
        CACHE STRING "Install path for Lumi package-related CMake files")
set(LUMI_VERSIONED_SUBDIR "${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

# Configure symbol visibility
set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

#-----------------------------------------------------------------------------
# Dependencies
#-----------------------------------------------------------------------------
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

#-----------------------------------------------------------------------------
# Library Sources
#-----------------------------------------------------------------------------
set(public_headers
        include/Lumi/export.h
        include/Lumi/lumi.h)

set(sources
        src/lumi.cpp)

# IDE source organization
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#-----------------------------------------------------------------------------
# Library Targets
#-----------------------------------------------------------------------------
if (LUMI_BUILD_STATIC_LIBS)
    add_library(LumiStatic STATIC ${sources})
    set_target_properties(LumiStatic PROPERTIES OUTPUT_NAME "Lumi" PREFIX "")
    add_library(Lumi::LumiStatic ALIAS LumiStatic)
endif ()

if (LUMI_BUILD_SHARED_LIBS)
    add_library(LumiShared SHARED ${sources})
    set_target_properties(LumiShared PROPERTIES OUTPUT_NAME "Lumi" PREFIX "")
    add_library(Lumi::LumiShared ALIAS LumiShared)
endif ()

# Generate export headers for proper symbol visibility
if (LUMI_BUILD_STATIC_LIBS)
    generate_export_header(LumiStatic
            EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/include/Lumi/Lumi_static_export.h"
            STATIC_DEFINE LUMI_STATIC_DEFINE
            EXPORT_MACRO_NAME LUMI_EXPORT
            DEPRECATED_MACRO_NAME LUMI_DEPRECATED_EXPORT
            NO_EXPORT_MACRO_NAME LUMI_NO_EXPORT)
    target_sources(LumiStatic PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include/Lumi/Lumi_static_export.h")
endif ()

if (LUMI_BUILD_SHARED_LIBS)
    generate_export_header(LumiShared
            EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/include/Lumi/Lumi_shared_export.h"
            EXPORT_MACRO_NAME LUMI_EXPORT
            DEPRECATED_MACRO_NAME LUMI_DEPRECATED_EXPORT
            NO_EXPORT_MACRO_NAME LUMI_NO_EXPORT)
    target_sources(LumiShared PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include/Lumi/Lumi_shared_export.h")
endif ()

# Configure common properties for both static and shared targets
macro(configure_lumi_target target_name is_shared_lib)
    target_include_directories(${target_name}
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
            PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/src")

    set_target_properties(${target_name} PROPERTIES
            PUBLIC_HEADER "${public_headers}"
            VERSION ${PROJECT_VERSION})

    target_link_libraries(${target_name} PRIVATE glfw)

    if (${is_shared_lib})
        set_target_properties(${target_name} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
    else ()
        target_compile_definitions(${target_name} PUBLIC LUMI_STATIC_DEFINE)
    endif ()
endmacro()

# Apply configuration to targets
if (LUMI_BUILD_STATIC_LIBS)
    configure_lumi_target(LumiStatic FALSE)
endif ()

if (LUMI_BUILD_SHARED_LIBS)
    configure_lumi_target(LumiShared TRUE)
endif ()

# Set up default target alias
if (TARGET LumiShared)
    add_library(Lumi::Lumi ALIAS LumiShared)
elseif (TARGET LumiStatic)
    add_library(Lumi::Lumi ALIAS LumiStatic)
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
                    DESTINATION "${CMAKE_INSTALL_DOCDIR}/${PROJECT_NAME}"
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
    configure_package_config_file(cmake/Lumi-config.cmake.in
            Lumi-config.cmake
            INSTALL_DESTINATION "${LUMI_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(Lumi-config-version.cmake
            COMPATIBILITY SameMajorVersion)

    # Install static library and its components        
    if (LUMI_BUILD_STATIC_LIBS)
        install(TARGETS LumiStatic EXPORT Lumi_static_export
                ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}/${LUMI_VERSIONED_SUBDIR}" COMPONENT Lumi-dev
                PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LUMI_VERSIONED_SUBDIR}" COMPONENT Lumi-dev)

        install(EXPORT Lumi_static_export
                COMPONENT Lumi-dev
                FILE "Lumi-static-targets.cmake"
                DESTINATION "${LUMI_INSTALL_CMAKEDIR}"
                NAMESPACE Lumi::)
    endif ()

    # Install shared library and its components
    if (LUMI_BUILD_SHARED_LIBS)
        install(TARGETS LumiShared EXPORT Lumi_shared_export
                RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}/${LUMI_VERSIONED_SUBDIR}" COMPONENT Lumi
                LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/${LUMI_VERSIONED_SUBDIR}" COMPONENT Lumi NAMELINK_COMPONENT Lumi-dev
                PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LUMI_VERSIONED_SUBDIR}" COMPONENT Lumi-dev)

        install(EXPORT Lumi_shared_export
                COMPONENT Lumi-dev
                FILE "Lumi-shared-targets.cmake"
                DESTINATION "${LUMI_INSTALL_CMAKEDIR}"
                NAMESPACE Lumi::)
    endif ()

    # Install CMake configuration files
    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/Lumi-config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/Lumi-config-version.cmake"
            COMPONENT Lumi-dev
            DESTINATION "${LUMI_INSTALL_CMAKEDIR}")

    # Install examples if enabled
    if (LUMI_INSTALL_EXAMPLES)
        install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/examples/"
                DESTINATION "${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/examples"
                COMPONENT Lumi-dev)
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

set(CPACK_COMPONENTS_ALL "Lumi" "Lumi-dev") # Explicitly list all components

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
    set(CPACK_WIX_PROPERTY_ARPURLINFOABOUT "https://your_lumi_homepage.com")
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