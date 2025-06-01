#-----------------------------------------------------------------------------
# Library Sources
#-----------------------------------------------------------------------------
message("Configuring Lumi Core...")
set(LUMI_CORE_SOURCES
        "core.cpp"
)

# Define public headers for the core Lumi
set(LUMI_CORE_PUBLIC_HEADERS
        "${CMAKE_SOURCE_DIR}/include/Lumi/Core/Core.h"
)

# IDE source organization
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${LUMI_CORE_SOURCES})
source_group(TREE "${CMAKE_SOURCE_DIR}/include/Lumi/Core" FILES ${LUMI_CORE_PUBLIC_HEADERS})

#-----------------------------------------------------------------------------
# Build Configuration
#-----------------------------------------------------------------------------
if (LUMI_BUILD_STATIC_LIBS)
    add_library(LumiStaticCore STATIC ${LUMI_CORE_SOURCES})
    set_target_properties(LumiStaticCore PROPERTIES OUTPUT_NAME "LumiCore")
    add_library(Lumi::CoreStatic ALIAS LumiStaticCore)

    configure_lumi_target(LumiStaticCore FALSE
            "${LUMI_CORE_PUBLIC_HEADERS}"
            Core)

    set_property(GLOBAL APPEND PROPERTY LUMI_STATIC_LIB_TARGETS LumiStaticCore)
endif ()

if (LUMI_BUILD_SHARED_LIBS)
    add_library(LumiSharedCore SHARED ${LUMI_CORE_SOURCES})
    set_target_properties(LumiSharedCore PROPERTIES OUTPUT_NAME "LumiCore")
    add_library(Lumi::CoreShared ALIAS LumiSharedCore)

    # Generate export macros
    generate_export_header(LumiSharedCore
            EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/include/Lumi/Core/Lumi_export.h"
            EXPORT_MACRO_NAME LUMI_API
            DEPRECATED_MACRO_NAME LUMI_DEPRECATED_API
            NO_EXPORT_MACRO_NAME LUMI_NO_API)

    # Add generated export header to public headers list
    list(APPEND LUMI_CORE_PUBLIC_HEADERS "${CMAKE_BINARY_DIR}/include/Lumi/Core/Lumi_export.h")

    configure_lumi_target(LumiSharedCore TRUE
            "${LUMI_CORE_PUBLIC_HEADERS}"
            "Core")

    set_property(GLOBAL APPEND PROPERTY LUMI_SHARED_LIB_TARGETS LumiSharedCore)
endif ()

list(APPEND LUMI_ALL_PUBLIC_HEADERS ${LUMI_CORE_PUBLIC_HEADERS} PARENT_SCOPE)