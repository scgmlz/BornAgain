# Reimplementation of native CMake command,
# for correct handling of leading dot,
# https://cmake.org/pipermail/cmake-developers/2011-June/013526.html
function (get_filename_component)
    _get_filename_component (${ARGN})
    list (GET ARGN 0 VAR)
    list (GET ARGN 2 CMD)
    if (${CMD} STREQUAL "EXT")
        string (REGEX MATCHALL "\\.[^.]*" PARTS "${${VAR}}")
        list (LENGTH PARTS LEN)
        if (LEN GREATER 1)
            math (EXPR LEN "${LEN} - 1")
            list (GET PARTS ${LEN} ${VAR})
        endif ()
    endif ()
    set (${VAR} "${${VAR}}" PARENT_SCOPE)
endfunction ()
