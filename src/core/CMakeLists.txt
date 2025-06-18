#-----------------------------------------------------------------------------
# Library Sources
#-----------------------------------------------------------------------------
message(STATUS "Configuring Lumi Core...")

#-----------------------------------------------------------------------------
if (NOT EXISTS "${LUMI_SOURCE_DIR}/include/lumi/metadata.h")
    message(FATAL_ERROR "Metadata header file not found.")
endif ()

# Define sources
set(LUMI_CORE_SOURCES
        "${LUMI_SOURCE_DIR}/src/core/core.cpp"
        "${LUMI_SOURCE_DIR}/src/core/info.cpp"
)

# Define public headers
set(LUMI_CORE_PUBLIC_HEADERS
        "${LUMI_SOURCE_DIR}/include/lumi/core/core.h"
        "${LUMI_SOURCE_DIR}/include/lumi/core/info.h"
        "${LUMI_SOURCE_DIR}/include/lumi/metadata.h"
)
# IDE source organization
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${LUMI_CORE_SOURCES})
source_group(TREE "${LUMI_SOURCE_DIR}/include/lumi" FILES ${LUMI_CORE_PUBLIC_HEADERS})

#-----------------------------------------------------------------------------
# Build Configuration
#-----------------------------------------------------------------------------
if (LUMI_BUILD_STATIC_LIBS)
    # core library
    add_library(LumiCore STATIC ${LUMI_CORE_SOURCES} ${LUMI_CORE_PUBLIC_HEADERS})
    add_library(Lumi::Core ALIAS LumiCore)

    target_link_libraries(
            LumiCore
            PUBLIC
            ${LUMI_CORE_DEPENDENCIES}
    )

    configure_lumi_target(LumiCore
            "${LUMI_CORE_PUBLIC_HEADERS}"
            core)

    set_property(GLOBAL APPEND PROPERTY LUMI_STATIC_LIB_TARGETS LumiCore)

    list(APPEND LUMI_ALL_SOURCES ${LUMI_CORE_SOURCES})
    list(APPEND LUMI_ALL_PUBLIC_HEADERS ${LUMI_CORE_PUBLIC_HEADERS})

    # Interface
    add_library(ILumiCore INTERFACE)
    target_link_libraries(ILumiCore INTERFACE
            LumiCore
    )
    add_library(Lumi::ILumiCore ALIAS ILumiCore)
    install(TARGETS ILumiCore EXPORT "${LUMI_COMMON_EXPORT_SET}" COMPONENT Lumi-dev)
    message(STATUS "Created Lumi::ILumiCore interface library to group CORE static components.")

    set_property(GLOBAL APPEND PROPERTY LUMI_STATIC_LIB_TARGETS LumiError)
endif ()

# Push the data to the global scope
set(LUMI_ALL_SOURCES ${LUMI_ALL_SOURCES} PARENT_SCOPE)
set(LUMI_ALL_PUBLIC_HEADERS ${LUMI_ALL_PUBLIC_HEADERS} PARENT_SCOPE)