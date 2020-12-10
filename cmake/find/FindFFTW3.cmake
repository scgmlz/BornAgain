# Find the FFTW includes and library.
#
# This module defines
# FFTW3_INCLUDE_DIR, where to locate fftw3.h file
# FFTW3_LIBRARIES, the libraries to link against to use fftw3
# FFTW3_LIBRARY, where to find the libfftw3 library.

# --- Looking for headers -----

find_path(FFTW3_INCLUDE_DIR fftw3.h)
if(NOT FFTW3_INCLUDE_DIR)
    message(ERROR " Missed dependency. Can't find FFTW headers, please make sure that you've installed FFTW development version.")
endif()

# --- Looking for library -----

set(FFTW3_NAMES ${FFTW3_NAMES} fftw3 fftw3-3 libfftw3-3)
set(ba_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES})

if (NOT APPLE AND NOT WIN32)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .so) # require shared version of library
endif()

find_library(FFTW3_LIBRARY NAMES ${FFTW3_NAMES} QUIET)
set(CMAKE_FIND_LIBRARY_SUFFIXES ${ba_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES})

# --- Processing variables -----

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FFTW3 REQUIRED_VARS FFTW3_LIBRARY FFTW3_INCLUDE_DIR)

if(FFTW3_FOUND)
    set(FFTW3_LIBRARIES ${FFTW3_LIBRARY} )
endif()

if(FFTW3_FOUND)
    message(STATUS "Found FFTW3: includes at ${FFTW3_INCLUDE_DIR}, libraries at ${FFTW3_LIBRARIES}")
else()
    message(STATUS "Cant'f find fftw3 library: ${FFTW3_INCLUDE_DIR}, ${FFTW3_LIBRARIES}.")
    if (NOT WIN32 AND NOT APPLE)
        message(STATUS "Please note, that shared version of FFTW3 library is required (use enable-shared during configuration phase).")
    endif()
endif()

mark_as_advanced(FFTW3_INCLUDE_DIR FFTW3_LIBRARY FFTW3_LIBRARY_DLL)
