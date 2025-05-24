#-----------------------------------------------------------------------------
# Library Sources
#-----------------------------------------------------------------------------
set(LUMI_WINDOW_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

# Define public headers for the Window component
set(LUMI_WINDOW_PUBLIC_HEADERS
        "${CMAKE_SOURCE_DIR}/include/Lumi/window/main.h"
)

# IDE source organization
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${LUMI_WINDOW_SOURCES})
source_group(TREE "${CMAKE_SOURCE_DIR}/include/Lumi/window" FILES ${LUMI_WINDOW_PUBLIC_HEADERS})


#-----------------------------------------------------------------------------


if (LUMI_BUILD_STATIC_LIBS)
    add_library(LumiStaticWindow STATIC ${LUMI_WINDOW_SOURCES})
    set_target_properties(LumiStaticWindow PROPERTIES OUTPUT_NAME "LumiWindow" PREFIX "")
    add_library(Lumi::WindowStatic ALIAS LumiStaticWindow)

    configure_lumi_target(LumiStaticWindow FALSE
            "${LUMI_WINDOW_PUBLIC_HEADERS}")

    target_link_libraries(LumiStaticWindow PUBLIC glfw)
endif ()

if (LUMI_BUILD_SHARED_LIBS)
    add_library(LumiSharedWindow SHARED ${LUMI_WINDOW_SOURCES})
    set_target_properties(LumiSharedWindow PROPERTIES OUTPUT_NAME "LumiWindow" PREFIX "")
    add_library(Lumi::WindowShared ALIAS LumiSharedWindow)

    configure_lumi_target(LumiSharedWindow TRUE
            "${LUMI_WINDOW_PUBLIC_HEADERS}")

    target_link_libraries(LumiSharedWindow PUBLIC glfw)
endif ()