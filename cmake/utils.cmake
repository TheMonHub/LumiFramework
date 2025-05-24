# A helper function to set a variable only if it hasn't been set yet.
# This prevents hardcoding values if the user wants to define them externally.
function(set_if_undefined VAR_NAME)
    if (NOT DEFINED ${VAR_NAME})
        set(${VAR_NAME} ${ARGN} PARENT_SCOPE)
    endif ()
endfunction()

# Macro to configure common properties for Lumi component targets
# target_name: The actual target name (e.g., LumiWindowStatic, LumiWindowShared, LumiFrameworkStatic)
# is_shared_lib: TRUE if shared, FALSE if static
# component_public_headers: List of public header files for this component
macro(configure_lumi_target target_name is_shared_lib component_public_headers)
    target_include_directories(${target_name}
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
            "$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${LUMI_VERSIONED_SUBDIR}>"
            PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    set_target_properties(${target_name} PROPERTIES
            PUBLIC_HEADER "${component_public_headers}"
            VERSION ${PROJECT_VERSION})

    if (${is_shared_lib})
        set_target_properties(${target_name} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
    endif ()
    set_target_properties(${target_name} PROPERTIES DEBUG_POSTFIX "d")

    if (LUMI_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
        # This single install(TARGETS) command handles:
        # 1. Adding the target to the export set.
        # 2. Installing the physical library files (ARCHIVE, LIBRARY, RUNTIME).
        # 3. Installing public headers associated with the target property.
        install(TARGETS ${target_name}
                EXPORT "${LUMI_COMMON_EXPORT_SET}"
                COMPONENT Lumi-dev
                # Common installation paths for static/shared library files
                ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}/${LUMI_VERSIONED_SUBDIR}/$<IF:$<STREQUAL:${is_shared_lib},TRUE>,shared,static>$<CONFIG>" COMPONENT Lumi-dev # For static libs and Windows import libs
                LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/${LUMI_VERSIONED_SUBDIR}/shared$<CONFIG>" COMPONENT Lumi # For shared libs (non-Windows)
                RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}/${LUMI_VERSIONED_SUBDIR}/shared$<CONFIG>" COMPONENT Lumi # For Windows DLLs

                # Install public headers from the PUBLIC_HEADER target property
                # This ensures headers associated directly with the target are installed.
                PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LUMI_VERSIONED_SUBDIR}/Lumi" COMPONENT Lumi-dev
        )

        # Separate install(FILES) for specific headers if 'component_public_headers'
        # contains additional headers not covered by PUBLIC_HEADER target property.
        # If all headers are managed by PUBLIC_HEADER property, this block can be removed.
        if (component_public_headers AND NOT "$<TARGET_PROPERTY:${target_name},PUBLIC_HEADER>" STREQUAL "${component_public_headers}")
            message(WARNING "Consider moving installation of specific headers into PUBLIC_HEADER target property for '${target_name}'.")
            install(FILES ${component_public_headers}
                    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LUMI_VERSIONED_SUBDIR}/Lumi"
                    COMPONENT Lumi-dev)
        endif ()
    endif ()
endmacro()