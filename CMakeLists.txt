###########################################################################
# top-level CMakeLists.txt for building BornAgain
############################################################################

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

set(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake
    ${CMAKE_SOURCE_DIR}/cmake/find
    ${CMAKE_SOURCE_DIR}/cmake/pack)
set(CONFIGURABLES_DIR ${CMAKE_SOURCE_DIR}/cmake/configurables)

include(commons/PreventInSourceBuilds)

project(BornAgain
    VERSION 1.18.99
    DESCRIPTION "BornAgain: simulate and fit scattering at grazing incidence."
    HOMEPAGE_URL https://www.bornagainproject.org
    ) # LANGUAGES CXX)
     # TODO modernize FindCerf to get rid of AssertLibraryFunction to restore restriction to CXX

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include(CTest) # equivalent to "enable_testing() ???
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -LE Fullcheck)
   # => 'make check' is an alias for 'ctest'
add_custom_target(fullcheck COMMAND ${CMAKE_CTEST_COMMAND})
   # => 'make check' is an alias for 'ctest'

## Project-wide user flags

# options that are on by default (switch off for accelerated builds of limited scope)
option(BORNAGAIN_PYTHON "Build with python support" ON)
option(BORNAGAIN_GUI "Build a graphical user interface" ON)
option(BORNAGAIN_TIFF_SUPPORT "Tiff files read/write support" ON)

# options that are off by default (switch on for additional functionality)
option(BORNAGAIN_MPI "Build with MPI support" OFF)
option(SLOWTESTS "CTest also covers slow tests" OFF)

option(CONFIGURE_BINDINGS "Generate python bindings during build (requires swig)" OFF)
option(CONFIGURE_PYTHON_DOCS "Generate python documentation from the doxygen comments" OFF)
option(CONFIGURE_MANPAGE "Build Unix man page" OFF)
option(CONFIGURE_DOXY "Configure Doxygen files" OFF)
option(ALLCONFIG "Regenerate Py docs, Py wrappers, man page, Doxyfiles" OFF)

option(BUILD_DEBIAN "Build a debian package" OFF)
option(BORNAGAIN_APPLE_BUNDLE "Create a Mac OS X bundle" OFF)

option(ZERO_TOLERANCE "Terminate compilation on warnings" OFF)
option(BORNAGAIN_COVERAGE "Build with test coverage information" OFF)
option(BORNAGAIN_DEBUG_OPTIMIZATION "Build with debug optimization (gcc only)" OFF)
option(BORNAGAIN_TIDY "Invokes clang-tidy" OFF)

if(BORNAGAIN_TIDY AND BORNAGAIN_PYTHON)
    message(FATAL_ERROR "BORNAGAIN_TIDY is incompatible with BORNAGAIN_PYTHON")
endif()

if(BORNAGAIN_GUI AND NOT BORNAGAIN_PYTHON AND NOT BORNAGAIN_TIDY)
    message(FATAL_ERROR "BORNAGAIN_GUI without BORNAGAIN_PYTHON is currently unsupported"
        " (except with BORNAGAIN_TIDY)")
endif()

if(ALLCONFIG)
    set(CONFIGURE_MANPAGE ON)
    set(CONFIGURE_PYTHON_DOCS ON)
    set(CONFIGURE_BINDINGS ON)
    set(CONFIGURE_DOXY ON)
endif()

## Various CMake settings (include order is of critical importance)

# function definitions
include(commons/GetFilenameComponent) # overwrite CMake command
include(BornAgain/MakeLib)
include(BornAgain/SwigLib)

# main settings

include(BornAgain/Directories)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
    include(BornAgain/Linux)
    include(BornAgain/NixInstall)
elseif(APPLE)
    include(BornAgain/MacOS)
    include(BornAgain/NixInstall)
elseif(WIN32)
    include(BornAgain/Windows)
endif()

include(BornAgain/Compiler)
if(ZERO_TOLERANCE)
    string(APPEND CMAKE_CXX_FLAGS " -Werror -Wfatal-errors")
endif()

include(BornAgain/Dependences)
if(BORNAGAIN_GUI)
    include(BornAgain/Qt)
    string(APPEND CMAKE_CXX_FLAGS " -DHAVE_QT=ON")
endif()
include(BornAgain/Config)
if(BORNAGAIN_PYTHON)
    include(BornAgain/PythonAPI)
endif()
include(BornAgain/PythonDocs)

# debug optimization
if(BORNAGAIN_DEBUG_OPTIMIZATION)
  include(commons/DebugOptimization)
endif()

## Fit
add_subdirectory(Fit/3rdParty)
add_subdirectory(Fit)
add_subdirectory(Fit/Test/Unit)
add_subdirectory(Fit/Test/Minimizer)


## recurse into the given subdirectories

# BornAgain components are build as separate shared libraries
set(CoreComponents "Base;Param;Sample;Device;Core")
set(AllComponents "${CoreComponents};GUI")

# code analysis
include(BornAgain/LineLength)
if(BORNAGAIN_COVERAGE)
  include(commons/CoverageFunction)
  include(BornAgain/Coverage)
endif()

# third-party code
add_subdirectory(ThirdParty/common)
add_subdirectory(ThirdParty/Core)
if(BORNAGAIN_GUI)
    add_subdirectory(ThirdParty/GUI)
endif()

# from here on our own code, occasionally scrutinized by clang-tidy
if(BORNAGAIN_TIDY)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy") # has effect only if compiler is clang; uses .clang-tidy
endif()

# core components
foreach(lib ${CoreComponents})
    add_subdirectory(${lib})
endforeach()
if(BORNAGAIN_PYTHON)
    add_dependencies(BornAgainFit swig_runtime)
endif()

# core tests
add_subdirectory(Tests/UnitTests/Core)
add_subdirectory(Tests/UnitTests/Numeric)
add_subdirectory(Tests/Performance/Core)

# GUI
if(BORNAGAIN_GUI)
    add_subdirectory(GUI)
    add_subdirectory(Tests/UnitTests/GUI)
    add_subdirectory(Tests/Performance/GUI)
endif()

# TODO: split Core / GUI
add_subdirectory(Tests/Functional)

# documentation
if(BORNAGAIN_USERMANUAL)
    add_subdirectory(Doc/UserManual)
endif()
if(CONFIGURE_MANPAGE)
    add_subdirectory(Doc/man)
endif()
if(CONFIGURE_DOXY)
    add_subdirectory(Doc/Doxygen)
endif()

# after-install message
add_subdirectory(cmake)

# make package targets
include(BornAgain/Pack)

message(STATUS "CMake done")
