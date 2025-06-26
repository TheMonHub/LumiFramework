#-----------------------------------------------------------------------------
# Library Sources
#-----------------------------------------------------------------------------
message(STATUS "Configuring Lumi Core...")

#-----------------------------------------------------------------------------
if (NOT EXISTS "${CMAKE_BINARY_DIR}/include/lumi/metadata.cppm")
    message(FATAL_ERROR "Metadata interface file not found.")
endif ()
#-----------------------------------------------------------------------------
set(LUMI_INFO_IMPLEMENTATION_SOURCES
        "${LUMI_SOURCE_DIR}/src/core/buildinfo.cpp"
        "${LUMI_SOURCE_DIR}/src/core/systeminfo.cpp"
)

set(LUMI_INFO_PUBLIC_HEADERS

)

set(LUMI_INFO_PUBLIC_INTERFACES
        "${LUMI_SOURCE_DIR}/include/lumi/core/info.cppm"
        "${LUMI_SOURCE_DIR}/include/lumi/core/buildinfo.cppm"
        "${LUMI_SOURCE_DIR}/include/lumi/core/systeminfo.cppm"
)

set(LUMI_INFO_DEPENDENCIES

)
# IDE source organization
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${LUMI_INFO_IMPLEMENTATION_SOURCES})
source_group(TREE "${LUMI_SOURCE_DIR}/include/lumi" FILES ${LUMI_INFO_PUBLIC_INTERFACES})

#-----------------------------------------------------------------------------
# Build Configuration
#-----------------------------------------------------------------------------
if (LUMI_BUILD_STATIC_LIBS)
    # info
    add_library(LumiInfo STATIC)

    target_sources(LumiInfo
            PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
                "${LUMI_SOURCE_DIR}/include/lumi"
            FILES
                ${LUMI_INFO_PUBLIC_HEADERS}
            FILE_SET CXX_MODULES
            BASE_DIRS
                "${LUMI_SOURCE_DIR}/include/lumi"
                "${CMAKE_BINARY_DIR}/include/lumi"
            FILES
                ${LUMI_INFO_PUBLIC_INTERFACES}
                ${LUMI_GENERATED_METADATA_OUTPUT}
            PRIVATE
                ${LUMI_INFO_IMPLEMENTATION_SOURCES}
    )
    add_library(Lumi::Info ALIAS LumiInfo)

    target_link_libraries(
            LumiInfo
            PUBLIC
            ${LUMI_INFO_DEPENDENCIES}
    )
    configure_lumi_target(LumiInfo "Info")

    list(APPEND LUMI_ALL_SOURCES ${LUMI_INFO_IMPLEMENTATION_SOURCES})
    list(APPEND LUMI_ALL_PUBLIC_HEADERS ${LUMI_INFO_PUBLIC_HEADERS})
    list(APPEND LUMI_ALL_PUBLIC_INTERFACES ${LUMI_INFO_PUBLIC_INTERFACES} ${LUMI_GENERATED_METADATA_OUTPUT})

    configure_lumi_interface_target(LumiCore "LumiInfo")
endif ()

push_data_to_global()