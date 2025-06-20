#-----------------------------------------------------------------------------
# Library Sources
#-----------------------------------------------------------------------------
message(STATUS "Configuring Lumi Core...")

#-----------------------------------------------------------------------------
if (NOT EXISTS "${LUMI_SOURCE_DIR}/src/core/metadata.ixx")
    message(FATAL_ERROR "Metadata interface file not found.")
endif ()

# Define sources
set(LUMI_CORE_IMPLEMENTATION_SOURCES
        "${LUMI_SOURCE_DIR}/src/core/info.cpp"
        "${LUMI_SOURCE_DIR}/src/core/error_funny.cpp"
)

# Define public interfaces
set(LUMI_CORE_PUBLIC_INTERFACES
        "${LUMI_SOURCE_DIR}/src/core/core.ixx"
        "${LUMI_SOURCE_DIR}/src/core/metadata.ixx"
        "${LUMI_SOURCE_DIR}/src/core/info.ixx"
        "${LUMI_SOURCE_DIR}/src/core/error_funny.ixx"
)

# IDE source organization
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${LUMI_CORE_SOURCES} ${LUMI_CORE_PUBLIC_INTERFACES})

#-----------------------------------------------------------------------------
# Build Configuration
#-----------------------------------------------------------------------------
if (LUMI_BUILD_STATIC_LIBS)
    # core library
    add_library(LumiCore)

    target_sources(LumiCore
            PUBLIC
            FILE_SET CXX_MODULES FILES
            ${LUMI_CORE_PUBLIC_INTERFACES}
            PRIVATE
            ${LUMI_CORE_IMPLEMENTATION_SOURCES}
    )

    add_library(Lumi::Core ALIAS LumiCore)

    target_link_libraries(
            LumiCore
            PUBLIC
            ${LUMI_CORE_DEPENDENCIES}
    )

    configure_lumi_target(
            LumiCore
            core
    "")

    set_property(GLOBAL APPEND PROPERTY LUMI_STATIC_LIB_TARGETS LumiCore)

    list(APPEND LUMI_ALL_SOURCES ${LUMI_CORE_SOURCES})
    list(APPEND LUMI_ALL_PUBLIC_INTERFACES ${LUMI_CORE_PUBLIC_INTERFACES})
    # Interface
    add_library(ILumiCore INTERFACE)
    target_link_libraries(ILumiCore INTERFACE
            LumiCore
    )
    add_library(Lumi::ILumiCore ALIAS ILumiCore)
    install(TARGETS ILumiCore EXPORT "${LUMI_COMMON_EXPORT_SET}")
    message(STATUS "Created Lumi::ILumiCore interface library to group CORE static components.")
endif ()

# Push the data to the global scope
set(LUMI_ALL_SOURCES ${LUMI_ALL_SOURCES} PARENT_SCOPE)
set(LUMI_ALL_PUBLIC_INTERFACES ${LUMI_ALL_PUBLIC_INTERFACES} PARENT_SCOPE)