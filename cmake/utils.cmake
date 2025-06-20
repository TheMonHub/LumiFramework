# A helper function to set a variable only if it hasn't been set yet.
cmake_policy(SET CMP0177 NEW)

# This prevents hardcoding values if the user wants to define them externally.
function(set_if_undefined VAR_NAME)
    if (NOT DEFINED ${VAR_NAME} OR "${VAR_NAME}" STREQUAL "")
        set(${VAR_NAME} ${ARGN} PARENT_SCOPE)
    endif ()
endfunction()

# Macro to configure common properties for lumi component targets
# target_name: The actual target name (e.g., LumiCore, LumiWindow)
# component_name: The name of the component (e.g., core, window)
macro(configure_lumi_target target_name component_name sub_component_name)
    set_target_properties(${target_name} PROPERTIES
            VERSION ${PROJECT_VERSION}
            OUTPUT_NAME "${target_name}"
    )

    # Add debug postfix for debug builds
    set_target_properties(${target_name} PROPERTIES DEBUG_POSTFIX "_d")

    if (LUMI_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
        if ("${component_name}" STREQUAL "")
            set(INSTALL_DESTINATION "/${LUMI_VERSIONED_SUBDIR}/")
            message(STATUS "${target_name} will be installed to ${INSTALL_DESTINATION} under '${LUMI_VERSIONED_SUBDIR}'")
        elseif ("${sub_component_name}" STREQUAL "")
            set(INSTALL_DESTINATION "/${LUMI_VERSIONED_SUBDIR}/${component_name}/")
            message(STATUS "${target_name} will be installed to ${INSTALL_DESTINATION} under '${component_name}' folder.")
        else ()
            set(INSTALL_DESTINATION "/${LUMI_VERSIONED_SUBDIR}/${component_name}/${sub_component_name}/")
            message(STATUS "${target_name} will be installed to ${INSTALL_DESTINATION} under '${component_name}/${sub_component_name}' folder.")
        endif ()

        install(TARGETS ${target_name}
                EXPORT "${LUMI_COMMON_EXPORT_SET}"
                ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}${INSTALL_DESTINATION}"
                LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}${INSTALL_DESTINATION}"
                RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}${INSTALL_DESTINATION}"
                FILE_SET HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}${INSTALL_DESTINATION}"
                FILE_SET CXX_MODULES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}${INSTALL_DESTINATION}"
                INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}${INSTALL_DESTINATION}"
        )
    endif ()
endmacro()