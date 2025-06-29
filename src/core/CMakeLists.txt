#-----------------------------------------------------------------------------
# Library Sources
#-----------------------------------------------------------------------------
message(STATUS "Configuring Lumi Core...")

#-----------------------------------------------------------------------------
if (NOT EXISTS "${CMAKE_BINARY_DIR}/include/lumi/metadata.cppm")
    message(FATAL_ERROR "Metadata interface file not found.")
endif ()
#-----------------------------------------------------------------------------
if (${CMAKE_HOST_LINUX})
    set(LUMI_INFO_IMPLEMENTATION_SOURCES
            "${LUMI_SOURCE_DIR}/src/core/systeminfo_linux.cpp"
    )
elseif (${CMAKE_HOST_WIN32})
else ()
endif ()

set(LUMI_INFO_PUBLIC_HEADERS

)

set(LUMI_INFO_PUBLIC_INTERFACES
        "${LUMI_SOURCE_DIR}/include/lumi/core/info.cppm"
        "${LUMI_SOURCE_DIR}/include/lumi/core/buildinfo.cppm"
        "${LUMI_SOURCE_DIR}/include/lumi/core/systeminfo.cppm"
)

set(LUMI_INFO_DEPENDENCIES

)
#-----------------------------------------------------------------------------
set(LUMI_UNIT_IMPLEMENTATION_SOURCES
        "${LUMI_SOURCE_DIR}/src/core/unit.cpp"
)

set(LUMI_UNIT_PUBLIC_HEADERS

)

set(LUMI_UNIT_PUBLIC_INTERFACES
        "${LUMI_SOURCE_DIR}/include/lumi/core/unit.cppm"
)

set(LUMI_UNIT_DEPENDENCIES

)

# IDE source organization
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${LUMI_INFO_IMPLEMENTATION_SOURCES} ${LUMI_UNIT_IMPLEMENTATION_SOURCES})
source_group(TREE "${LUMI_SOURCE_DIR}/include/lumi" FILES ${LUMI_INFO_PUBLIC_INTERFACES} ${LUMI_UNIT_PUBLIC_INTERFACES})

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
                "${LUMI_SOURCE_DIR}/src/core/buildinfo.cpp"
                ${LUMI_INFO_IMPLEMENTATION_SOURCES}
    )
    add_library(Lumi::Info ALIAS LumiInfo)

    target_link_libraries(
            LumiInfo
            PUBLIC
            ${LUMI_INFO_DEPENDENCIES}
    )
    configure_lumi_target(LumiInfo "info")

    # unit
    add_library(LumiUnit STATIC)

    target_sources(LumiUnit
            PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
            "${LUMI_SOURCE_DIR}/include/lumi"
            FILES
            ${LUMI_UNIT_PUBLIC_HEADERS}
            FILE_SET CXX_MODULES
            BASE_DIRS
            "${LUMI_SOURCE_DIR}/include/lumi"
            FILES
            ${LUMI_UNIT_PUBLIC_INTERFACES}
            PRIVATE
            ${LUMI_UNIT_IMPLEMENTATION_SOURCES}
    )
    add_library(Lumi::Unit ALIAS LumiUnit)

    target_link_libraries(
            LumiUnit
            PUBLIC
            ${LUMI_UNIT_DEPENDENCIES}
    )
    configure_lumi_target(LumiUnit "unit")

    list(APPEND LUMI_ALL_SOURCES "${LUMI_INFO_IMPLEMENTATION_SOURCES} ${LUMI_UNIT_IMPLEMENTATION_SOURCES}")
    list(APPEND LUMI_ALL_PUBLIC_HEADERS "${LUMI_INFO_PUBLIC_HEADERS} ${LUMI_UNIT_PUBLIC_HEADERS}")
    list(APPEND LUMI_ALL_PUBLIC_INTERFACES "${LUMI_INFO_PUBLIC_INTERFACES} ${LUMI_GENERATED_METADATA_OUTPUT} ${LUMI_UNIT_PUBLIC_INTERFACES}")
endif ()

push_data_to_global()