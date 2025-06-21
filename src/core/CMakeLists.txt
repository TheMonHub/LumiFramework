#-----------------------------------------------------------------------------
# Library Sources
#-----------------------------------------------------------------------------
message(STATUS "Configuring Lumi Core...")

#-----------------------------------------------------------------------------
if (NOT EXISTS "${CMAKE_BINARY_DIR}/include/lumi/metadata.cppm")
    message(FATAL_ERROR "Metadata interface file not found.")
endif ()
#-----------------------------------------------------------------------------
set(LUMI_CORE_IMPLEMENTATION_SOURCES
        "${LUMI_SOURCE_DIR}/src/core/info.cpp"
        "${LUMI_SOURCE_DIR}/src/core/error_funny.cpp"
        "${LUMI_SOURCE_DIR}/src/core/stacktrace.cpp"
)

set(LUMI_CORE_PUBLIC_INTERFACES
        "${LUMI_SOURCE_DIR}/include/lumi/core/core.cppm"
        "${LUMI_SOURCE_DIR}/include/lumi/core/info.cppm"
        "${LUMI_SOURCE_DIR}/include/lumi/core/error_funny.cppm"
        "${LUMI_SOURCE_DIR}/include/lumi/core/stacktrace.cppm"
)

set(LUMI_CORE_DEPENDENCIES

)
# IDE source organization
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${LUMI_CORE_SOURCES})
source_group(TREE "${LUMI_SOURCE_DIR}/include/lumi" FILES ${LUMI_CORE_PUBLIC_INTERFACES})

#-----------------------------------------------------------------------------
# Build Configuration
#-----------------------------------------------------------------------------
if (LUMI_BUILD_STATIC_LIBS)
    # core
    add_library(LumiCore)

    target_sources(LumiCore
            PUBLIC
            FILE_SET CXX_MODULES
            BASE_DIRS
                "${LUMI_SOURCE_DIR}/include/lumi/core"
                "${CMAKE_BINARY_DIR}/include/lumi"
            FILES
                ${LUMI_GENERATED_METADATA_OUTPUT}
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
            core)

    set_property(GLOBAL APPEND PROPERTY LUMI_STATIC_LIB_TARGETS LumiCore)

    list(APPEND LUMI_ALL_SOURCES ${LUMI_CORE_IMPLEMENTATION_SOURCES})
    list(APPEND LUMI_ALL_PUBLIC_INTERFACES ${LUMI_CORE_PUBLIC_INTERFACES})
endif ()

# Push the data to the global scope
set(LUMI_ALL_SOURCES ${LUMI_ALL_SOURCES} PARENT_SCOPE)
set(LUMI_ALL_PUBLIC_INTERFACES ${LUMI_ALL_PUBLIC_INTERFACES} PARENT_SCOPE)