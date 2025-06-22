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
macro(configure_lumi_target target_name)
    set_target_properties(${target_name} PROPERTIES
            VERSION ${PROJECT_VERSION}
            OUTPUT_NAME "${target_name}"
    )

    # Add debug postfix for debug builds
    set_target_properties(${target_name} PROPERTIES DEBUG_POSTFIX "_d")

    if (LUMI_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
        set(INSTALL_DESTINATION "/${LUMI_VERSIONED_SUBDIR}/lumi")

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