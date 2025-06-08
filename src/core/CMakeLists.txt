#-----------------------------------------------------------------------------
# Library Sources
#-----------------------------------------------------------------------------
message(STATUS "Configuring Lumi Core...")

#-----------------------------------------------------------------------------
if (NOT EXISTS "${LUMI_SOURCE_DIR}/include/Lumi/Metadata.h")
    message(FATAL_ERROR "Metadata header file not found.")
endif ()

# Define sources
set(LUMI_CORE_SOURCES
        "${LUMI_SOURCE_DIR}/src/core/core.cpp"
        "${LUMI_SOURCE_DIR}/src/core/info.cpp"
)
set(LUMI_CORE_SOURCES_ERROR
        "${LUMI_SOURCE_DIR}/src/core/error_handler.cpp"
)

# Define public headers
set(LUMI_CORE_PUBLIC_HEADERS
        "${LUMI_SOURCE_DIR}/include/Lumi/Core/Core.h"
        "${LUMI_SOURCE_DIR}/include/Lumi/Core/Info.h"
        "${LUMI_SOURCE_DIR}/include/Lumi/Metadata.h"
)
set(LUMI_CORE_PUBLIC_HEADERS_ERROR
        "${LUMI_SOURCE_DIR}/include/Lumi/Core/ErrorHandler.h"
        "${LUMI_SOURCE_DIR}/include/Lumi/Core/ErrorFunny.h"
)

# Define dependencies
set(LUMI_CORE_DEPENDENCIES
        # Empty for now
)

# IDE source organization
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${LUMI_CORE_SOURCES})
source_group(TREE "${LUMI_SOURCE_DIR}/include/Lumi" FILES ${LUMI_CORE_PUBLIC_HEADERS})

#-----------------------------------------------------------------------------
# Build Configuration
#-----------------------------------------------------------------------------
if (LUMI_BUILD_STATIC_LIBS)
    # Core library
    add_library(LumiCore STATIC ${LUMI_CORE_SOURCES} ${LUMI_CORE_PUBLIC_HEADERS})
    add_library(Lumi::Core ALIAS LumiCore)

    target_link_libraries(
            LumiCore
            PUBLIC
            ${LUMI_CORE_DEPENDENCIES}
    )

    configure_lumi_target(LumiCore
            "${LUMI_CORE_PUBLIC_HEADERS}"
            Core)

    set_property(GLOBAL APPEND PROPERTY LUMI_STATIC_LIB_TARGETS LumiCore)

    # Error handling
    add_library(LumiError STATIC ${LUMI_CORE_SOURCES_ERROR} ${LUMI_CORE_PUBLIC_HEADERS_ERROR})
    add_library(Lumi::Error ALIAS LumiError)

    target_link_libraries(
            LumiError
            PUBLIC
            ${LUMI_CORE_DEPENDENCIES}
    )

    configure_lumi_target(LumiError
            "${LUMI_CORE_PUBLIC_HEADERS_ERROR}"
            Core)

    set_property(GLOBAL APPEND PROPERTY LUMI_STATIC_LIB_TARGETS LumiError)
endif ()

# Push the data to the global scope
list(APPEND LUMI_ALL_SOURCES ${LUMI_CORE_SOURCES_ERROR})
list(APPEND LUMI_ALL_SOURCES ${LUMI_CORE_SOURCES})
set(LUMI_ALL_SOURCES ${LUMI_ALL_SOURCES} PARENT_SCOPE)
list(APPEND LUMI_ALL_PUBLIC_HEADERS ${LUMI_CORE_PUBLIC_HEADERS_ERROR})
list(APPEND LUMI_ALL_PUBLIC_HEADERS ${LUMI_CORE_PUBLIC_HEADERS})
set(LUMI_ALL_PUBLIC_HEADERS ${LUMI_ALL_PUBLIC_HEADERS} PARENT_SCOPE)
list(APPEND LUMI_ALL_DEPENDENCIES ${LUMI_CORE_DEPENDENCIES})
set(LUMI_ALL_DEPENDENCIES ${LUMI_ALL_DEPENDENCIES} PARENT_SCOPE)