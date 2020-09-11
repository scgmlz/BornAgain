###########################################################################
# top-level CMakeLists.txt for building BornAgain
############################################################################

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

set(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake/modules    # CMake modules specific for BornAgain
    ${CMAKE_SOURCE_DIR}/cmake/extensions # CMake modules for use in various projects
    )
set(CONFIGURABLES_DIR ${CMAKE_SOURCE_DIR}/cmake/configurables)

include(PreventInSourceBuilds)

project(BornAgain
    VERSION 1.17.99
    DESCRIPTION "BornAgain: simulate and fit scattering at grazing incidence."
    HOMEPAGE_URL https://www.bornagainproject.org
    ) # LANGUAGES CXX)
     # TODO modernize FindCerf to get rid of AssertLibraryFunction to restore restriction to CXX

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

include(CTest) # equivalent to "enable_testing() ???
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -LE Fullcheck)
   # => 'make check' is an alias for 'ctest'
add_custom_target(fullcheck COMMAND ${CMAKE_CTEST_COMMAND})
   # => 'make check' is an alias for 'ctest'

## declare project-wide user flags, and set default values

# options that can be switched off to simplify the build and reduce its scope
option(BORNAGAIN_PYTHON "Build with python support" ON)
option(BORNAGAIN_GUI "Build a graphical user interface" ON)
option(BORNAGAIN_TIFF_SUPPORT "Tiff files read/write support" ON)

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

if(ALLCONFIG)
    set(CONFIGURE_MANPAGE ON)
    set(CONFIGURE_PYTHON_DOCS ON)
    set(CONFIGURE_BINDINGS ON)
    set(CONFIGURE_DOXY ON)
endif()

# include CMake macros and functions
include(GetFilenameComponent) # overwrite CMake command
include(SearchInstalledSoftware)
include(CheckCompiler)
if(ZERO_TOLERANCE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wfatal-errors")
endif()
if(BORNAGAIN_GUI)
    include(SearchQt)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_QT=ON")
endif()
include(BornAgainConfiguration)
include(BornAgainPolicy)
include(GeneratePythonDocs)
include(BALineLength)

# debug optimization
if(BORNAGAIN_DEBUG_OPTIMIZATION)
  include(DebugOptimization)
endif()

# code coverage analysis
if(BORNAGAIN_COVERAGE)
  include(CoverageFunction)
  include(BACoverage)
endif()

# recurse into the given subdirectories
if(BORNAGAIN_USERMANUAL)
    add_subdirectory(Doc/UserManual)
endif()
if(CONFIGURE_MANPAGE)
    add_subdirectory(Doc/man)
endif()
if(CONFIGURE_DOXY)
    add_subdirectory(Doc/Doxygen)
endif()

add_subdirectory(ThirdParty/common)
add_subdirectory(ThirdParty/Fit)
add_subdirectory(Fit)
add_subdirectory(Tests/UnitTests/Fit)

add_subdirectory(ThirdParty/Core)
add_subdirectory(Core)
add_subdirectory(Tests/UnitTests/Core)
add_subdirectory(Tests/UnitTests/Numeric)
add_subdirectory(Tests/Performance/Core)

if(BORNAGAIN_GUI)
    add_subdirectory(ThirdParty/GUI)
    add_subdirectory(GUI)
    add_subdirectory(Tests/UnitTests/GUI)
    add_subdirectory(Tests/Performance/GUI)
endif()

# functional tests (ctest)
add_subdirectory(Tests/Functional)

# after-install message
add_subdirectory(cmake)

# make package targets
include(BornAgainCPack)
