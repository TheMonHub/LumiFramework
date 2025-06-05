#-----------------------------------------------------------------------------
# Library Sources
#-----------------------------------------------------------------------------
message(STATUS "Configuring Lumi Core...")
# Define sources
set(LUMI_CORE_SOURCES
        "${LUMI_SOURCE_DIR}/src/core/core.cpp"
        "${LUMI_SOURCE_DIR}/src/core/coremeta.cpp"
)

# Define public headers
set(LUMI_CORE_PUBLIC_HEADERS
        "${LUMI_SOURCE_DIR}/include/Lumi/Core/Core.h"
)

# Define dependencies
set(LUMI_CORE_DEPENDENCIES
        # Empty for now
)

# IDE source organization
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${LUMI_CORE_SOURCES})
source_group(TREE "${LUMI_SOURCE_DIR}/include/Lumi/Core" FILES ${LUMI_CORE_PUBLIC_HEADERS})

#-----------------------------------------------------------------------------
# Build Configuration
#-----------------------------------------------------------------------------
if (LUMI_BUILD_STATIC_LIBS)
    add_library(LumiStaticCore STATIC ${LUMI_CORE_SOURCES})
    set_target_properties(LumiStaticCore PROPERTIES OUTPUT_NAME "LumiCore")
    add_library(Lumi::CoreStatic ALIAS LumiStaticCore)

    target_link_libraries(
            LumiStaticCore
            PUBLIC
            ${LUMI_CORE_DEPENDENCIES}
    )

    configure_lumi_target(LumiStaticCore
            "${LUMI_CORE_PUBLIC_HEADERS}"
            Core)

    set_property(GLOBAL APPEND PROPERTY LUMI_STATIC_LIB_TARGETS LumiStaticCore)
endif ()

# Push the data to the global scope
list(APPEND LUMI_ALL_SOURCES ${LUMI_CORE_SOURCES})
set(LUMI_ALL_SOURCES ${LUMI_ALL_SOURCES} PARENT_SCOPE)
list(APPEND LUMI_ALL_PUBLIC_HEADERS ${LUMI_CORE_PUBLIC_HEADERS})
set(LUMI_ALL_PUBLIC_HEADERS ${LUMI_ALL_PUBLIC_HEADERS} PARENT_SCOPE)
list(APPEND LUMI_ALL_DEPENDENCIES ${LUMI_CORE_DEPENDENCIES})
set(LUMI_ALL_DEPENDENCIES ${LUMI_ALL_DEPENDENCIES} PARENT_SCOPE)