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
macro(configure_lumi_target target_name component_public_headers component_name)
    target_include_directories(${target_name}
            PUBLIC
            "$<BUILD_INTERFACE:${LUMI_SOURCE_DIR}/include>"
            "$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${LUMI_VERSIONED_SUBDIR}>"
            PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    set_target_properties(${target_name} PROPERTIES
            PUBLIC_HEADER "${component_public_headers}"
            VERSION ${PROJECT_VERSION}
            OUTPUT_NAME "Lumi${component_name}"
    )

    set_target_properties(${target_name} PROPERTIES DEBUG_POSTFIX "D")

    if (LUMI_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
        # This single install(TARGETS) command handles:
        # 1. Adding the target to the export set.
        # 2. Installing the physical library files (ARCHIVE, LIBRARY, RUNTIME).
        # 3. Installing public headers associated with the target property.
        if ("${component_name}" STREQUAL "")
            set(PUBLIC_HEADER_DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/Lumi/${LUMI_VERSIONED_SUBDIR}")
            set(INSTALL_DESTINATION "/${LUMI_VERSIONED_SUBDIR}/$<CONFIG>")
            message(STATUS "${target_name}'s headers will be installed to ${PUBLIC_HEADER_DESTINATION} under '${LUMI_VERSIONED_SUBDIR}' folder.")
            message(STATUS "${target_name} will be installed to ${INSTALL_DESTINATION} under '${LUMI_VERSIONED_SUBDIR}'")
        else ()
            set(PUBLIC_HEADER_DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LUMI_VERSIONED_SUBDIR}/Lumi/${component_name}")
            set(INSTALL_DESTINATION "/${LUMI_VERSIONED_SUBDIR}/${component_name}$<CONFIG>")
            message(STATUS "${target_name}'s headers will be installed to ${PUBLIC_HEADER_DESTINATION} under '${component_name}' folder.")
            message(STATUS "${target_name} will be installed to ${INSTALL_DESTINATION} under '${component_name}' folder.")
        endif ()
        install(TARGETS ${target_name}
                EXPORT "${LUMI_COMMON_EXPORT_SET}"
                COMPONENT Lumi-dev

                ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}${INSTALL_DESTINATION}" COMPONENT Lumi-dev

                # Install public headers from the PUBLIC_HEADER target property
                # This ensures headers associated directly with the target are installed.
                PUBLIC_HEADER DESTINATION "${PUBLIC_HEADER_DESTINATION}" COMPONENT Lumi-dev
        )
    endif ()
endmacro()