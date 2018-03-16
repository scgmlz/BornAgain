# Search for installed software required by BornAgain

find_package(Threads REQUIRED)
find_package(FFTW REQUIRED)
find_package(GSL REQUIRED)

# --- Eigen3 is a git submodule; use system eigen if this submodule was not properly cloned ---
set(EIGEN3_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/ThirdParty/Core/eigen3" CACHE INTERNAL "")

# --- Boost ---
set(Boost_NO_BOOST_CMAKE ON) # prevent shortcut
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
add_definitions(-DBOOST_ALL_DYN_LINK) # line is needed for MSVC
#add_definitions(-DBOOST_LIB_DIAGNOSTIC) # shows during compilation auto-linked libraries
set(boost_libraries_required date_time chrono program_options iostreams system filesystem regex)
if(WIN32)
    set(boost_libraries_required ${boost_libraries_required} zlib bzip2)
endif()

find_package(Boost 1.48.0 COMPONENTS ${boost_libraries_required} REQUIRED)
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
    find_package(TIFF 4.0.2 REQUIRED)
endif()

# --- Python ---
if (BORNAGAIN_GENERATE_BINDINGS AND BORNAGAIN_GENERATE_PYTHON_DOCS)
    find_package(Doxygen REQUIRED)
endif()

if (BORNAGAIN_USE_PYTHON3)
    set(Python_ADDITIONAL_VERSIONS 3.6 3.5 3.4 3.3)
else()
    set(Python_ADDITIONAL_VERSIONS 2.7)
endif()

if(BORNAGAIN_PYTHON OR BORNAGAIN_GUI)
    find_package(PythonInterp REQUIRED)
    message(STATUS "Found Python interpreter version ${PYTHON_VERSION_STRING} at ${PYTHON_EXECUTABLE}")
    find_package(PythonLibs REQUIRED)
    if(NOT PYTHONLIBS_FOUND)
        message(FATAL_ERROR "No Python library has been found")
    endif()
    message(STATUS "Found Python libraries version ${PYTHONLIBS_VERSION_STRING} at ${PYTHON_LIBRARIES}; includes at ${PYTHON_INCLUDE_DIRS}")

    if(PYTHONLIBS_VERSION_STRING MATCHES "^3.*$")
        set(BORNAGAIN_USE_PYTHON3 ON)
    endif()
    message(STATUS "BORNAGAIN_USE_PYTHON3: ${BORNAGAIN_USE_PYTHON3}.")

    if(NOT WIN32)
        include(ValidatePythonInstallation)
        ValidatePythonInstallation()
    endif()

    find_package(Numpy REQUIRED)
endif()

# --- Swig ---
if(BORNAGAIN_PYTHON AND BORNAGAIN_GENERATE_BINDINGS)
    find_package(SWIG 3.0 REQUIRED)
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
