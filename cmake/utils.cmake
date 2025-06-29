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
macro(configure_lumi_target target_name component_name)
    target_compile_features(${target_name} INTERFACE cxx_std_20)
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
                ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}${INSTALL_DESTINATION}/${component_name}"
                LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}${INSTALL_DESTINATION}/${component_name}"
                RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}${INSTALL_DESTINATION}/${component_name}"
                FILE_SET HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}${INSTALL_DESTINATION}"
                FILE_SET CXX_MODULES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}${INSTALL_DESTINATION}"
                CXX_MODULES_BMI DESTINATION "${CMAKE_INSTALL_BINDIR}${INSTALL_DESTINATION}/${component_name}/modules"
        )
    endif ()
    set_property(GLOBAL APPEND PROPERTY LUMI_STATIC_LIB_TARGETS ${target_name})
endmacro()

macro(push_data_to_global)
    # Push the data to the global scope
    set(LUMI_ALL_SOURCES ${LUMI_ALL_SOURCES} PARENT_SCOPE)
    set(LUMI_ALL_PUBLIC_HEADERS ${LUMI_ALL_PUBLIC_HEADERS} PARENT_SCOPE)
    set(LUMI_ALL_PUBLIC_INTERFACES ${LUMI_ALL_PUBLIC_INTERFACES} PARENT_SCOPE)
endmacro()