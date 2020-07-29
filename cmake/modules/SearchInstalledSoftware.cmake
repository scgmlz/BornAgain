# Search for installed software required by BornAgain

if(WIN32)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .dll.a .lib)
endif()

find_package(Threads REQUIRED)
find_package(FFTW3 REQUIRED)
find_package(GSL REQUIRED)
if(WIN32)
    message("Eigen3 include dirs hopefully given on the command line: ${EIGEN3_INCLUDE_DIRS}")
    message(STATUS "Eigen3 include_dir=${EIGEN3_INCLUDE_DIR}")
else()
    find_package(Eigen3 3.3 REQUIRED) # no need for FindEigen3, as Eigen provides Eigen3Config.cmake
    message(STATUS "Eigen3 include_dir=${EIGEN3_INCLUDE_DIR} version=${EIGEN3_VERSION_STRING}")
endif()

find_package(Cerf REQUIRED)
message(STATUS "Cerf found=${Cerf_FOUND} lib=${Cerf_LIBRARIES} inc=${Cerf_INCLUDE_DIR} version={Cerf_VERSION}")

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
if(BORNAGAIN_GENERATE_BINDINGS AND BORNAGAIN_GENERATE_PYTHON_DOCS)
    find_package(Doxygen REQUIRED)
endif()

if(BORNAGAIN_PYTHON OR BORNAGAIN_GUI)

    find_package(Python3 COMPONENTS Interpreter Development NumPy)

    message(STATUS "  Python3_VERSION              : ${Python3_VERSION}")
    message(STATUS "  Python3_INTERPRETER_ID       : ${Python3_INTERPRETER_ID}")
    message(STATUS "  Python3_EXECUTABLE           : ${Python3_EXECUTABLE}")
    message(STATUS "  Python3_STDLIB               : ${Python3_STDLIB} Python3_STDARCH: ${Python3_STDARCH}")
    message(STATUS "  Python3_SITELIB              : ${Python3_SITELIB} Python3_SITEARCH: ${Python3_SITEARCH}")
    message(STATUS "  Python3_INCLUDE_DIRS         : ${Python3_INCLUDE_DIRS}")
    message(STATUS "  Python3_LIBRARIES            : ${Python3_LIBRARIES}")
    message(STATUS "  Python3_LIBRARY_DIRS         : ${Python3_LIBRARY_DIRS}")
    message(STATUS "  Python3_NumPy_VERSION        : ${Python3_NumPy_VERSION}")
    message(STATUS "  Python3_NumPy_INCLUDE_DIRS   : ${Python3_NumPy_INCLUDE_DIRS}")

    if(NOT Python3_FOUND)
        message(FATAL_ERROR "No Python requested components.")
    endif()

    if(NOT Python3_Development_FOUND)
        message(FATAL_ERROR "No Python.h has been found.")
    endif()

    if(NOT Python3_NumPy_FOUND)
        message(FATAL_ERROR "Numpy was not found.")
    endif()

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
