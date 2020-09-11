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

find_path(Cerf_INCLUDE_DIR cerf.h)
find_library(Cerf_LIBRARIES NAMES cerf libcerf)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Cerf DEFAULT_MSG Cerf_LIBRARIES Cerf_INCLUDE_DIR)

if(Cerf_FOUND)
   message(STATUS "Found libcerf, version ${Cerf_VERSION}, lib=${Cerf_LIBRARIES},\
 include_dir=${Cerf_INCLUDE_DIR}.")
   set(Cerf_IS_CPP OFF)
endif()

mark_as_advanced(Cerf_INCLUDE_DIR Cerf_LIBRARIES)

include(AssertLibraryFunction)
assert_library_function(Cerf cerf "")
assert_library_function(Cerf dawson "")
assert_library_function(Cerf voigt "")
