# -----------------------------------------------------------------------------
# source directories
# -----------------------------------------------------------------------------

set(TOOL_DIR ${CMAKE_SOURCE_DIR}/devtools)
set(WRAP_DIR ${CMAKE_SOURCE_DIR}/Wrap)
set(SWIG_DIR ${WRAP_DIR}/Swig)
set(EXAMPLES_DIR ${CMAKE_SOURCE_DIR}/Examples)

set(TEST_REFERENCE_DIR            ${CMAKE_SOURCE_DIR}/Tests/ReferenceData)
set(TEST_REFERENCE_DIR_CORE       ${TEST_REFERENCE_DIR}/Core)
set(TEST_REFERENCE_DIR_PY_CORE    ${TEST_REFERENCE_DIR}/PyCore)
set(TEST_REFERENCE_DIR_PY_PERSIST ${TEST_REFERENCE_DIR}/PyPersist)
set(TEST_REFERENCE_DIR_STD        ${TEST_REFERENCE_DIR}/Std)

# -----------------------------------------------------------------------------
# auto directories (refreshed when CONFIGURE options are set)
# -----------------------------------------------------------------------------

set(AUTO_DIR ${CMAKE_SOURCE_DIR}/auto/Wrap)

file(MAKE_DIRECTORY ${AUTO_DIR})

# -----------------------------------------------------------------------------
# output directories
# -----------------------------------------------------------------------------

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY         ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY         ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(BUILD_VAR_DIR ${CMAKE_BINARY_DIR}/var)
set(BUILD_INC_DIR ${CMAKE_BINARY_DIR}/inc)
set(BUILD_SRC_DIR ${CMAKE_BINARY_DIR}/src)

set(TEST_OUTPUT_DIR             ${CMAKE_BINARY_DIR}/test_output)
set(TEST_OUTPUT_DIR_CORE        ${TEST_OUTPUT_DIR}/Core)
set(TEST_OUTPUT_DIR_PY_EXAMPLES ${TEST_OUTPUT_DIR}/PyExamples)
set(TEST_OUTPUT_DIR_PY_CORE     ${TEST_OUTPUT_DIR}/PyCore)
set(TEST_OUTPUT_DIR_PY_FIT      ${TEST_OUTPUT_DIR}/PyFit)
set(TEST_OUTPUT_DIR_PY_PERSIST  ${TEST_OUTPUT_DIR}/PyPersist)
set(TEST_OUTPUT_DIR_PY_STD      ${TEST_OUTPUT_DIR}/PyStd)
set(TEST_OUTPUT_DIR_STD         ${TEST_OUTPUT_DIR}/Std)

configure_file("${CONFIGURABLES_DIR}/auto_README.in.md" "${CMAKE_SOURCE_DIR}/auto/README.md" @ONLY)

file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/bornagain)
file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/exec)
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${BUILD_VAR_DIR})
file(MAKE_DIRECTORY ${BUILD_INC_DIR})
file(MAKE_DIRECTORY ${BUILD_SRC_DIR})
file(MAKE_DIRECTORY ${TEST_OUTPUT_DIR})

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
