# Find libcerf or libcerfcpp
#
# Usage:
#   find_package(Cerf [REQUIRED] [QUIET])
#
# Sets the following variables:
#   - Cerf_FOUND        .. true if library is found
#   - Cerf_LIBRARIES    .. full path to library
#   - Cerf_INCLUDE_DIR  .. full path to include directory
#   - Cerf_IS_CPP       .. true if C++ version of library is used
#
# Copyright 2018 Joachim Wuttke, Forschungszentrum Jülich.
# Redistribution permitted.

set(Cerf_ULTIMATELY_REQUIRED ${Cerf_FIND_REQUIRED})
set(Cerf_FIND_REQUIRED FALSE)
# set(Cerf_FIND_VERSION 1.13) incompatible with Debian package

find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(PC_Cerf QUIET libcerf)
    if(PC_Cerf_FOUND)
        set(Cerf_VERSION ${PC_Cerf_VERSION})
    endif()
endif()

find_path(Cerf_INCLUDE_DIR cerf.h)
find_library(Cerf_LIBRARIES NAMES cerf)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Cerf
    REQUIRED_VARS Cerf_LIBRARIES Cerf_INCLUDE_DIR
    VERSION_VAR Cerf_VERSION)

# If CERF was found, then either it has been found because the C version is present and was freshly 
# found, or because the variables have been found in the cache (which then can be because of
# a formerly found C or C++ version)
# If not found at this point, the C version has not been found and no cache variables exist
# => Search for the C++ version

if(Cerf_FOUND)
	# Either we freshly found the C version, which also means Cerf_IS_CPP is not present in the 
	# cache and we set it. Or we found any formerly found version (C or C++) from the cache, then 
	# Cerf_IS_CPP is also already in the cache and will not be changed by the following command
	set(Cerf_IS_CPP OFF CACHE BOOL "Define whether CERF shall be used as C++")
else()
    # C version not found and cache is empty => search for C++ version
    unset(Cerf_FOUND)
    unset(Cerf_LIBRARIES)
    find_library(Cerf_LIBRARIES NAMES cerfcpp)
    find_package_handle_standard_args(Cerf
        REQUIRED_VARS Cerf_LIBRARIES Cerf_INCLUDE_DIR
        VERSION_VAR Cerf_VERSION)
    if(Cerf_FOUND)
		set(Cerf_IS_CPP ON CACHE BOOL "Define whether CERF shall be used as C++")
	endif()
endif()

# If still not found, then check whether it is ultimately required or not.
if(NOT Cerf_FOUND)
	message(STATUS "libcerf: FOUND=${Cerf_FOUND}, VERSION=${Cerf_VERSION}, "
		"LIB=${Cerf_LIBRARIES}, IS_CPP=${Cerf_IS_CPP}")
	if(${Cerf_ULTIMATELY_REQUIRED})
		message(FATAL_ERROR "Found neither C nor C++ version of cerf")
	endif()
	message(STATUS "Found neither C nor C++ version of cerf")
	return()
endif()

if(Cerf_IS_CPP)
	message(STATUS "Found libcerf, language=CPP, version=${Cerf_VERSION}, lib=${Cerf_LIBRARIES},"
        " include_dir=${Cerf_INCLUDE_DIR}.")
else()
    message(STATUS "Found libcerf, language=C, version=${Cerf_VERSION}, lib=${Cerf_LIBRARIES},"
        " include_dir=${Cerf_INCLUDE_DIR}.")
endif()
		
mark_as_advanced(Cerf_INCLUDE_DIR Cerf_LIBRARIES Cerf_IS_CPP)

include(AssertLibraryFunction)
assert_library_function(Cerf cerf "")
assert_library_function(Cerf dawson "")
assert_library_function(Cerf voigt "")
