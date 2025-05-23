# A helper function to set a variable only if it hasn't been set yet.
# This prevents hardcoding values if the user wants to define them externally.
function(set_if_undefined VAR_NAME)
    if (NOT DEFINED ${VAR_NAME})
        set(${VAR_NAME} ${ARGN} PARENT_SCOPE)
    endif ()
endfunction()