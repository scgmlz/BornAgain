# Search for installed software required by BornAgain

if(WIN32)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .dll.a .lib)
endif()

find_package(Threads REQUIRED)
find_package(FFTW3 REQUIRED)

find_package(GSL REQUIRED)
message(STATUS "GSL found=${GSL_FOUND} libs=${GSL_LIBRARIES} inc=${GSL_INCLUDE_DIR} version=${GSL_VERSION}")

if(WIN32)
    set(EIGEN3_INCLUDE_DIR ${CMAKE_INCLUDE_PATH})
    message(STATUS "Eigen3 include_dir=${EIGEN3_INCLUDE_DIR} (hard-coded)")
else()
    find_package(Eigen3 3.3 REQUIRED)
    message(STATUS "Eigen3 include_dir=${EIGEN3_INCLUDE_DIR} version=${EIGEN3_VERSION_STRING}")
endif()

find_package(Cerf REQUIRED)
if(Cerf_IS_CPP)
    add_compile_definitions(CERF_AS_CPP=ON)
endif()

# --- Boost ---
set(Boost_NO_BOOST_CMAKE ON) # prevent shortcut
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
add_definitions(-DBOOST_ALL_DYN_LINK) # line is needed for MSVC
add_definitions(-DBOOST_UUID_FORCE_AUTO_LINK) # line is needed to link bcrypt for MSVC

# Boost component libraries (do not list headers here)
set(boost_libraries_required iostreams program_options)
if(WIN32)
    # system seems to be indirectly required
    list(APPEND boost_libraries_required system)
    find_package(BZip2 REQUIRED)
    find_package(ZLIB REQUIRED)
    find_package(LibLZMA REQUIRED)
    find_library(ZSTD_LIBRARY NAMES zstd)
endif()
find_package(Boost 1.65.1 COMPONENTS ${boost_libraries_required} REQUIRED)
# In spite of the "REQUIRED" flag, FindBoost will not terminate if some components are missing
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Not all required Boost component libraries were found")
endif()
message(STATUS "Found Boost includes at ${Boost_INCLUDE_DIRS}, libraries at ${Boost_LIBRARY_DIRS}")

# requires these libs in target_link_libraries for win only
if(WIN32)
    list(APPEND Boost_LIBRARIES ${BZIP2_LIBRARIES} ${ZLIB_LIBRARIES} ${LIBLZMA_LIBRARIES} ${ZSTD_LIBRARY})
endif()

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
if(BORNAGAIN_PYTHON)
    find_package(Python3 COMPONENTS Interpreter Development)
    if(NOT Python3_FOUND)
        message(FATAL_ERROR "Python3 not found.")
    endif()

    message(STATUS "  Python3_VERSION              : ${Python3_VERSION}")
    message(STATUS "  Python3_INTERPRETER_ID       : ${Python3_INTERPRETER_ID}")
    message(STATUS "  Python3_EXECUTABLE           : ${Python3_EXECUTABLE}")
    message(STATUS "  Python3_STDLIB               : ${Python3_STDLIB} Python3_STDARCH: ${Python3_STDARCH}")
    message(STATUS "  Python3_SITELIB              : ${Python3_SITELIB} Python3_SITEARCH: ${Python3_SITEARCH}")
    message(STATUS "  Python3_INCLUDE_DIRS         : ${Python3_INCLUDE_DIRS}")
    message(STATUS "  Python3_LIBRARIES            : ${Python3_LIBRARIES}")
    message(STATUS "  Python3_LIBRARY_DIRS         : ${Python3_LIBRARY_DIRS}")

    find_package(Python3 COMPONENTS Interpreter)
    if(NOT Python3_FOUND)
        message(FATAL_ERROR "Python3 interpreter not found.")
    endif()

    find_package(Python3 COMPONENTS Interpreter Development)
    if(NOT Python3_Development_FOUND)
        message(FATAL_ERROR
            "Python.h not found. Probably you need to install package libpython3-dev (or similar).")
    endif()

    find_package(Python3 COMPONENTS Interpreter Development NumPy)
    if(NOT Python3_NumPy_FOUND)
        message(FATAL_ERROR "Python3-NumPy not found.")
    endif()
    message(STATUS "  Python3_NumPy_VERSION        : ${Python3_NumPy_VERSION}")
    message(STATUS "  Python3_NumPy_INCLUDE_DIRS   : ${Python3_NumPy_INCLUDE_DIRS}")

    if(CONFIGURE_BINDINGS)
        find_package(SWIG 4.0 REQUIRED)
        include(${SWIG_USE_FILE})
        message(STATUS "Found SWIG version ${SWIG_VERSION} at ${SWIG_EXECUTABLE} with flags '${SWIG_FLAGS}'; CMake definitions in ${SWIG_USE_FILE}")

        if(CONFIGURE_PYTHON_DOCS)
            find_package(Doxygen REQUIRED)
        endif()
    endif()

endif()

# --- man page generation ---
if(CONFIGURE_MANPAGE)
    find_program(POD2MAN pod2man)
    if(NOT POD2MAN)
        message(FATAL_ERROR "FATAL: cannot satisfy CONFIGURE_MANPAGE: pod2man not found")
    endif()
    message(STATUS "Found pod2man: ${POD2MAN}")
endif()


# === install Windows DLLs ===

if(WIN32)
    # system libraries
    foreach(Boost_lib ${Boost_LIBRARIES})
        get_filename_component(UTF_BASE_NAME ${Boost_lib} NAME_WE)
        get_filename_component(UTF_PATH ${Boost_lib} PATH)
        message(STATUS "Boost dll: ${UTF_PATH}/${UTF_BASE_NAME}.dll")
        install(FILES ${UTF_PATH}/${UTF_BASE_NAME}.dll
            DESTINATION ${destination_lib} COMPONENT Libraries)
    endforeach()

    set(win_python_lib
        "${Python3_LIBRARY_DIRS}/python${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR}.lib")
    get_filename_component(UTF_BASE_NAME ${win_python_lib} NAME_WE)
    get_filename_component(UTF_PATH ${Python3_EXECUTABLE} PATH)
    message(STATUS "Python dll: ${UTF_PATH}/${UTF_BASE_NAME}.dll"
        " - installed in ${destination_lib}")
    install(FILES ${UTF_PATH}/${UTF_BASE_NAME}.dll
        DESTINATION ${destination_lib} COMPONENT Libraries)

    set(Cerf_LIB ${Cerf_LIBRARIES}) # we take for granted that there is only one cerf.lib
    get_filename_component(DIR ${Cerf_LIB} DIRECTORY)
    get_filename_component(cerf ${Cerf_LIB} NAME_WE)

    set(DLL "${DIR}/cerfcpp.dll")
    if (NOT EXISTS ${DLL})
        message(FATAL_ERROR "Dynamic link library ${DLL} (needed for cerf) does not exist")
    endif()
    install(FILES ${DLL} DESTINATION ${destination_lib} COMPONENT Libraries)
    message(STATUS "Cerf dll: ${DLL} - installed in ${destination_lib}")

    set(DLL_MSG "")
    foreach(LIB IN LISTS FFTW3_LIBRARIES TIFF_LIBRARIES)
        string(REPLACE ".lib" ".dll" DLL "${LIB}")
        if (NOT EXISTS ${DLL})
            message(FATAL_ERROR "Dynamic link library ${DLL} (derived from ${LIB}) does not exist")
        endif()
        install(FILES ${DLL} DESTINATION ${destination_lib} COMPONENT Libraries)
        string(APPEND DLL_MSG " ${DLL}")
    endforeach()
    message(STATUS "Other dlls: ${DLL_MSG} - installed in ${destination_lib}")

endif(WIN32)
