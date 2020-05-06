###############################################################################
# BornAgain project configuration
###############################################################################

# -----------------------------------------------------------------------------
# Common policies
# -----------------------------------------------------------------------------

# --- from GUI section

#if(POLICY CMP0020)
#    cmake_policy(SET CMP0020 NEW)
#endif()

#if(POLICY CMP0043)
#    cmake_policy(SET CMP0043 NEW)
#endif()

#if(POLICY CMP0028)
#    cmake_policy(SET CMP0028 NEW)
#endif()

# -----------------------------------------------------------------------------
# Common definitions
# -----------------------------------------------------------------------------

# suppress qDebug() output for release build
if(CMAKE_BUILD_TYPE STREQUAL Release)
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

# -----------------------------------------------------------------------------
# source directory paths
# -----------------------------------------------------------------------------

set(TEST_OUTPUT_DIR ${CMAKE_BINARY_DIR}/test_output)
file(MAKE_DIRECTORY ${TEST_OUTPUT_DIR})
set(TEST_REFERENCE_DIR ${CMAKE_SOURCE_DIR}/Tests/ReferenceData)

set(PY_EXAMPLES_DIR ${CMAKE_SOURCE_DIR}/Examples/python)

# -----------------------------------------------------------------------------
# cmake runtime output configuration
# -----------------------------------------------------------------------------

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(BUILD_VAR_DIR ${CMAKE_BINARY_DIR}/var)
set(BUILD_INC_DIR ${CMAKE_BINARY_DIR}/inc)
set(BUILD_SRC_DIR ${CMAKE_BINARY_DIR}/src)
configure_file("${TEMPLATE_DIR}/auto_README.in" "${CMAKE_SOURCE_DIR}/auto/README" @ONLY)

file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/bornagain)
file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/exec)
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${BUILD_VAR_DIR})
file(MAKE_DIRECTORY ${BUILD_INC_DIR})
file(MAKE_DIRECTORY ${BUILD_SRC_DIR})

# -----------------------------------------------------------------------------
# file extensions
# -----------------------------------------------------------------------------

if(WIN32)
    set(libprefix _lib)
    set(libsuffix .dll)
elseif(APPLE)
    set(libprefix _lib)
    set(libsuffix .so)
else()
    set(libprefix _lib)
    set(libsuffix .so)
endif()

# -----------------------------------------------------------------------------
# destinations
# -----------------------------------------------------------------------------

if(WIN32)
    set(destination_bin bin)
    set(destination_lib ${destination_bin})
    set(destination_gui bin)
    set(destination_include include)
    set(destination_examples Examples)
    set(destination_images Images)
    set(destination_libexec python)
else()
    set(destination_suffix BornAgain-${BornAgain_VERSION_MAJOR}.${BornAgain_VERSION_MINOR})
    if(APPLE AND BORNAGAIN_APPLE_BUNDLE)
        set(destination_bundle BornAgain.app)
        set(destination_prefix ${destination_bundle}/Contents/)
        set(destination_libexec ${destination_prefix}libexec/${destination_suffix})
    else()
        if(APPLE)
            set(QTDIR $ENV{QTDIR})
            message(STATUS "QTDIR is ${QTDIR}")
            set(CMAKE_INSTALL_RPATH ${QTDIR}/lib)
        endif()
        set(destination_prefix "")
        set(destination_libexec ${destination_prefix}lib/${destination_suffix})
    endif()
    set(destination_bin ${destination_prefix}bin)
    set(destination_gui ${destination_libexec})
    set(destination_lib ${destination_prefix}lib/${destination_suffix})
    set(destination_include ${destination_prefix}include/${destination_suffix})
    set(destination_share ${destination_prefix}share/${destination_suffix}/)
    set(destination_examples ${destination_share}Examples)
    set(destination_images ${destination_share}Images)
endif()

message(STATUS "Destination directories:
    bin->${destination_bin},
    lib->${destination_lib},
    gui->${destination_gui},
    include->${destination_include},
    share->${destination_share},
    examples->${destination_examples},
    images->${destination_images},
    libexec->${destination_libexec}")

# -----------------------------------------------------------------------------
# configure files
# -----------------------------------------------------------------------------

if(BORNAGAIN_RELEASE)
    # configure Doxyfile
    configure_file(${CMAKE_SOURCE_DIR}/Doc/Doxygen/Doxyfile.in
        ${CMAKE_SOURCE_DIR}/Doc/Doxygen/Doxyfile @ONLY)
endif()

if(NOT BORNAGAIN_BUILDBOT_SERVER)
configure_file(${TEMPLATE_DIR}/CTestCustom.cmake.in ${CMAKE_BINARY_DIR}/CTestCustom.cmake)
endif()

if (WIN32)
    # Necessary to provide correct slashes in BABuild.h
    file(TO_CMAKE_PATH ${Python_EXECUTABLE} Python_EXECUTABLE)
    file(TO_CMAKE_PATH ${Python_STDLIB} Python_STDLIB)
    file(TO_CMAKE_PATH ${Python_LIBRARIES} Python_LIBRARIES)
    file(TO_CMAKE_PATH ${Python_STDLIB} Python_STDLIB)
    file(TO_CMAKE_PATH ${Python_INCLUDE_DIRS} Python_INCLUDE_DIRS)
    file(TO_CMAKE_PATH ${Python_NumPy_INCLUDE_DIRS} Python_NumPy_INCLUDE_DIRS)
    file(TO_CMAKE_PATH ${Python_SITELIB} Python_SITELIB)
endif()

configure_file(${TEMPLATE_DIR}/BAVersion.h.in  ${BUILD_INC_DIR}/BAVersion.h @ONLY)
configure_file(${TEMPLATE_DIR}/BABuild.h.in  ${BUILD_INC_DIR}/BABuild.h @ONLY)
configure_file(${TEMPLATE_DIR}/BATesting.h.in  ${BUILD_INC_DIR}/BATesting.h @ONLY)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${BUILD_INC_DIR}")

configure_file(${CMAKE_SOURCE_DIR}/Examples/python/utils/plot_intensity_data.py
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plot_intensity_data.py COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/Examples/python/utils/plot_intensity_data_diff.py
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plot_intensity_data_diff.py COPYONLY)

# -----------------------------------------------------------------------------
# configure BornAgain launch scripts
# -----------------------------------------------------------------------------

set(this_bindir $BORNAGAINSYS/bin)
set(this_libdir $BORNAGAINSYS/lib/${destination_suffix})
configure_file(${TEMPLATE_DIR}/thisbornagain.sh.in
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/thisbornagain.sh @ONLY)
configure_file(${TEMPLATE_DIR}/thisbornagain.csh.in
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/thisbornagain.csh @ONLY)

# -----------------------------------------------------------------------------
# configure postinst and prerm for the debian package
# -----------------------------------------------------------------------------

if(BUILD_DEBIAN)
    set(CMAKE_INSTALL_PREFIX "/usr")
    configure_file(${TEMPLATE_DIR}/postinst.in ${BUILD_VAR_DIR}/postinst @ONLY)
    configure_file(${TEMPLATE_DIR}/prerm.in ${BUILD_VAR_DIR}/prerm @ONLY)
    set(CMAKE_INSTALL_RPATH \$ORIGIN/../;\$ORIGIN/../../lib/${destination_suffix})
endif(BUILD_DEBIAN)
