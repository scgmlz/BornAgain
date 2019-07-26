# Find the FFTW includes and library.
#
# This module defines
# FFTW_INCLUDE_DIR, where to locate fftw3.h file
# FFTW_LIBRARIES, the libraries to link against to use fftw3
# FFTW_LIBRARY, where to find the libfftw3 library.

# --- Looking for headers -----

find_path(FFTW_INCLUDE_DIR fftw3.h)
if(NOT FFTW_INCLUDE_DIR)
    message(ERROR " Missed dependency. Can't find FFTW headers, please make sure that you've installed FFTW development version.")
endif()

# --- Looking for library -----

set(FFTW_NAMES ${FFTW_NAMES} fftw3 fftw3-3 libfftw3-3)

find_library(FFTW_LIBRARY NAMES ${FFTW_NAMES} QUIET)

if (WIN31)
    string( REPLACE ".lib" ".dll" FFTW_LIBRARY_DLL "${FFTW_LIBRARY}" )
    if (NOT EXISTS ${FFTW_LIBRARY_DLL})
        message(FATAL_ERROR "File ${FFTW_LIBRARY_DLL} does not exist")
    endif(NOT EXISTS ${FFTW_LIBRARY_DLL})
endif()

# --- Processing variables -----

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FFTW REQUIRED_VARS FFTW_LIBRARY FFTW_INCLUDE_DIR)

if(FFTW_FOUND)
    set( FFTW_LIBRARIES ${FFTW_LIBRARY} )
endif()

if(FFTW_FOUND)
    message(STATUS "Found FFTW: includes at ${FFTW_INCLUDE_DIR}, libraries at ${FFTW_LIBRARIES}")
else()
    message(STATUS "Cant'f find fftw3 library: ${FFTW_INCLUDE_DIR}, ${FFTW_LIBRARIES}.")
    if (NOT WIN32 AND NOT APPLE)
        message(STATUS "Please note, that shared version of FFTW library is required (use enable-shared during configuration phase).")
    endif()
endif()

mark_as_advanced(FFTW_INCLUDE_DIR FFTW_LIBRARY FFTW_LIBRARY_DLL)
