#.rst:
# AssertLibraryFunction
# ---------------------
#
# ASSERT_LIBRARY_FUNCTION checks whether given libraries contain
# a given function. If this is not the case, a fatal error is raised.
#
# CHECK_LIBRARY_EXISTS(LIBNAME FUNCTION LOCATION)
#
# ::
#
#   LIBNAME  - library name(case sensitive)
#   FUNCTION - name of the function to be searched in ${LIBNAME}_LIBRARIES
#   LOCATION - where the library should be found(if unsure, use "")
#
#
# The following variables may be set before calling this macro to modify
# the way the check is run:
#
# ::
#
#   CMAKE_REQUIRED_FLAGS = string of compile command line flags
#   CMAKE_REQUIRED_DEFINITIONS = list of macros to define(-DFOO=bar)
#   CMAKE_REQUIRED_LIBRARIES = list of libraries to link
#   CMAKE_REQUIRED_QUIET = execute quietly without messages
#
# This function is meant to be used in Find<Package>.cmake modules,
# which in turn should be called through
#
# ::
#
#   find_package(<Package> [QUIET] [REQUIRED])
#
# Within a Find<Package>.cmake module, find_package_handle_standard_args
# must be called before any call of ASSERT_LIBRARY_FUNCTION.
# Typically, Find<Package>.cmake looks like the following:
#
# ::
# 
#   find_path(<Package>_INCLUDE_DIR <include_file>)
#   find_library(<Package>_LIBRARIES NAMES <library_name> <Package>)
#   
#   include(FindPackageHandleStandardArgs)
#   find_package_handle_standard_args(<Package> DEFAULT_MSG <Package>_LIBRARIES <Package>_INCLUDE_DIR)
#   
#   include(AssertLibraryFunction)
#   assert_library_function(<Package> <function_name> "")
#   
#   mark_as_advanced(<Package>_INCLUDE_DIR <Package>_LIBRARIES)
#   
# The result of ASSERT_LIBRARY_FUNCTION is cached in a variable named
# ${LIBNAME}_${FUNCTION}.

#=============================================================================
# Based on CheckLibrariesExists(Copyright 2002-2009 Kitware, Inc.)
# Author: Joachim Wuttke(Copyright 2015 Forschungszentrum Jülich)
# License: BSD(see cmake License for details)
#=============================================================================


macro(alf_status_message _msg)
    if( ${LIBNAME}_FIND_QUIETLY )
    else()
        message(STATUS ${_msg})
    endif()
endmacro()

function(ASSERT_LIBRARY_FUNCTION LIBNAME FUNCTION LOCATION)
    set(LIBRARY ${${LIBNAME}_LIBRARIES})
    set(VARIABLE ${LIBNAME}_${FUNCTION})
    set(_MSG "Search ${FUNCTION} in ${LIBRARY}")
    if(DEFINED "${VARIABLE}")
        if(${${VARIABLE}})
            alf_status_message("${_MSG} -- cached")
            return()
        endif()
    endif()
    alf_status_message("Search ${FUNCTION} in ${LIBRARY}")
    set(MACRO_CHECK_LIBRARY_EXISTS_DEFINITION
        "-DCHECK_FUNCTION_EXISTS=${FUNCTION} ${CMAKE_REQUIRED_FLAGS}")
    set(CHECK_LIBRARY_EXISTS_LIBRARIES ${LIBRARY})
    if(CMAKE_REQUIRED_LIBRARIES)
        set(CHECK_LIBRARY_EXISTS_LIBRARIES
            ${CHECK_LIBRARY_EXISTS_LIBRARIES} ${CMAKE_REQUIRED_LIBRARIES})
    endif()
    try_compile(COMPILE_OK
        ${CMAKE_BINARY_DIR}
        ${CMAKE_ROOT}/Modules/CheckFunctionExists.c
        COMPILE_DEFINITIONS ${CMAKE_REQUIRED_DEFINITIONS}
        LINK_LIBRARIES ${CHECK_LIBRARY_EXISTS_LIBRARIES}
        CMAKE_FLAGS
        -DCOMPILE_DEFINITIONS:STRING=${MACRO_CHECK_LIBRARY_EXISTS_DEFINITION}
        -DLINK_DIRECTORIES:STRING=${LOCATION}
        OUTPUT_VARIABLE OUTPUT)

    if(${COMPILE_OK})
        if(NOT CMAKE_REQUIRED_QUIET)
            alf_status_message("${_MSG} -- found")
        endif()
        set(${VARIABLE} 1 CACHE INTERNAL "Library ${LIBRARY} has ${function}")
        file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeOutput.log
            "Determining if the function ${FUNCTION} exists in the ${LIBRARY} "
            "passed with the following output:\n"
            "${OUTPUT}\n\n")
    else()
        set(${VARIABLE} "" CACHE INTERNAL "Library ${LIBRARY} has no ${function}")
        file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeError.log
            "Determining if the function ${FUNCTION} exists in the ${LIBRARY} "
            "failed with the following output:\n"
            "${OUTPUT}\n\n")
        if( ${LIBNAME}_FIND_REQUIRED )
            message(FATAL_ERROR "${_MSG} -- not found")
        else()
            alf_status_message("${_MSG} -- not found")
        endif()
    endif()
endfunction()
