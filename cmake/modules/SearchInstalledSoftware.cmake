# Search for installed software required by BornAgain

find_package(Threads REQUIRED)
find_package(FFTW3 REQUIRED)
find_package(GSL REQUIRED)

find_package(Cerf REQUIRED)

# --- Eigen3 is a git submodule; throw an error if submodule is not initialized ---
set(EIGEN3_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/ThirdParty/Core/eigen3" CACHE INTERNAL "")
if( NOT EXISTS "${EIGEN3_INCLUDE_DIR}/.git" )
    message( FATAL_ERROR "Eigen3 submodule was not initialized. Please run
                          git submodule update --init")
endif()

# --- Boost ---
set(Boost_NO_BOOST_CMAKE ON) # prevent shortcut
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
add_definitions(-DBOOST_ALL_DYN_LINK) # line is needed for MSVC

# Boost component libraries (do not list headers here)
set(boost_libraries_required filesystem iostreams program_options)
if(WIN32)
    # system seems to be indirectly required
    list(APPEND boost_libraries_required bzip2 system zlib)
endif()
find_package(Boost 1.65.1 COMPONENTS ${boost_libraries_required} REQUIRED)
# In spite of the "REQUIRED" flag, FindBoost will not terminate if some components are missing
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Not all required Boost component libraries were found")
endif()
message(STATUS "Found Boost includes at ${Boost_INCLUDE_DIRS}, libraries at ${Boost_LIBRARY_DIRS}")

# === optional packages ===

# --- MPI support ---
if(BORNAGAIN_MPI)
    message(STATUS "Configuring with MPI support")
    find_package(MPI REQUIRED)
    message(STATUS "MPI_CXX_INCLUDE_PATH: ${MPI_CXX_INCLUDE_PATH}")
    message(STATUS "MPI_CXX_LIBRARIES: ${MPI_CXX_LIBRARIES}")
endif()

# --- Tiff ---
if(BORNAGAIN_TIFF_SUPPORT)
    message(STATUS "Looking for libtiff (use -DBORNAGAIN_TIFF_SUPPORT=OFF to disable)")
    find_package(TIFF 4.0.2 REQUIRED COMPONENTS CXX)
endif()

# --- Python ---
if (BORNAGAIN_GENERATE_BINDINGS AND BORNAGAIN_GENERATE_PYTHON_DOCS)
    find_package(Doxygen REQUIRED)
endif()

if(BORNAGAIN_PYTHON OR BORNAGAIN_GUI)

    find_package (Python COMPONENTS Interpreter Development NumPy)

    message(STATUS "  Python_VERSION              : ${Python_VERSION}")
    message(STATUS "  Python_INTERPRETER_ID       : ${Python_INTERPRETER_ID}")
    message(STATUS "  Python_EXECUTABLE           : ${Python_EXECUTABLE}")
    message(STATUS "  Python_STDLIB               : ${Python_STDLIB} Python_STDARCH: ${Python_STDARCH}")
    message(STATUS "  Python_SITELIB              : ${Python_SITELIB} Python_SITEARCH: ${Python_SITEARCH}")
    message(STATUS "  Python_INCLUDE_DIRS         : ${Python_INCLUDE_DIRS}")
    message(STATUS "  Python_LIBRARIES            : ${Python_LIBRARIES}")
    message(STATUS "  Python_LIBRARY_DIRS         : ${Python_LIBRARY_DIRS}")
    message(STATUS "  Python_NumPy_VERSION        : ${Python_NumPy_VERSION}")
    message(STATUS "  Python_NumPy_INCLUDE_DIRS   : ${Python_NumPy_INCLUDE_DIRS}")

    if (NOT Python_FOUND)
        message(FATAL_ERROR "No Python requested components.")
    endif ()

    if (NOT Python_Development_FOUND)
        message(FATAL_ERROR "No Python.h has been found.")
    endif ()

    if (NOT Python_NumPy_FOUND)
        message(FATAL_ERROR "Numpy was not found.")
    endif ()

endif()

# --- Swig ---
if(BORNAGAIN_PYTHON AND BORNAGAIN_GENERATE_BINDINGS)
    find_package(SWIG 4.0 REQUIRED)
    include(${SWIG_USE_FILE})
    message(STATUS "Found SWIG version ${SWIG_VERSION} at ${SWIG_EXECUTABLE} with flags '${SWIG_FLAGS}'; CMake definitions in ${SWIG_USE_FILE}")
endif()

# --- man page generation ---
if(BORNAGAIN_MANPAGE)
    find_program(POD2MAN pod2man)
    if(NOT POD2MAN)
        message(FATAL_ERROR "FATAL: cannot satisfy BORNAGAIN_MANPAGE: pod2man not found")
    endif()
    message(STATUS "Found pod2man: ${POD2MAN}")
endif()
