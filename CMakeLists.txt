###########################################################################
# top-level CMakeLists.txt for building BornAgain
############################################################################

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)


set(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake/generic/modules
    ${CMAKE_SOURCE_DIR}/cmake/bornagain/modules)
set(TEMPLATE_DIR ${CMAKE_SOURCE_DIR}/cmake/bornagain/scripts)

include(PreventInSourceBuilds)

project(BornAgain)

include(CTest) # equivalent to "enable_testing() ???
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -LE Fullcheck) # => 'make check' is an alias for 'ctest'
add_custom_target(fullcheck COMMAND ${CMAKE_CTEST_COMMAND}) # => 'make check' is an alias for 'ctest'

include(VERSION.cmake)

## declare project-wide user flags, and set default values

# options that can be switched off to simplify the build and reduce its scope
option(BORNAGAIN_PYTHON "Build with python support" ON)
option(BORNAGAIN_GUI "Build a graphical user interface" ON)
option(BORNAGAIN_TIFF_SUPPORT "Tiff files read/write support" ON)
option(BORNAGAIN_OPENGL "Build additional modules for 3D in GUI" ON)
option(UNITTESTS "Don't skip unit tests" ON)

option(BORNAGAIN_USE_PYTHON2 "Build against python 2.7" OFF)
option(BORNAGAIN_MPI "Build with MPI support" OFF)

option(BORNAGAIN_GENERATE_BINDINGS "Generate python bindings during build (requires swig)" OFF)
option(BORNAGAIN_GENERATE_PYTHON_DOCS "Generate python documentation from the doxygen comments" OFF)
option(BORNAGAIN_MANPAGE "Build Unix man page" OFF)
option(BORNAGAIN_CONFIGURE_DOXY "Configure Doxygen files" OFF)
option(AUTOGENERATE "Regenerate Py docs, Py wrappers, man page, Doxyfiles" OFF)
option(BORNAGAIN_USERMANUAL "Build the User Manual" OFF)

option(BUILD_DEBIAN "Build a debian package" OFF)
option(BORNAGAIN_APPLE_BUNDLE "Create a Mac OS X bundle" OFF)

option(ZERO_TOLERANCE "Terminate compilation on warnings" OFF)
option(BORNAGAIN_COVERAGE "Build with test coverage information" OFF)
option(BORNAGAIN_DEBUG_OPTIMIZATION "Build with debug optimization (gcc only)" OFF)
option(BORNAGAIN_BUILDBOT_SERVER "Special option for the buildbot server" OFF)
option(BORNAGAIN_TIDY "Invokes clang-tidy" OFF)

if(AUTOGENERATE)
    set(BORNAGAIN_MANPAGE ON)
    set(BORNAGAIN_GENERATE_PYTHON_DOCS ON)
    set(BORNAGAIN_GENERATE_BINDINGS ON)
    set(BORNAGAIN_CONFIGURE_DOXY ON)
endif()

# include CMake macros and functions
include(GetFilenameComponent) # overwrite CMake command
include(SearchInstalledSoftware)
include(CheckCompiler)
if(ZERO_TOLERANCE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wfatal-errors")
endif()
include(BornAgainConfiguration)
include(BornAgainPolicy)
include(GeneratePythonDocs)
include(PyExamplesLineLength)
include(CheckCode)

# debug optimization
if(BORNAGAIN_DEBUG_OPTIMIZATION)
  include(DebugOptimization)
endif()

# code coverage analysis
if(BORNAGAIN_COVERAGE)
  include(CheckCoverage)
  include(SetupCoverage)
endif()

# recurse into the given subdirectories
if(BORNAGAIN_USERMANUAL)
    add_subdirectory(Doc/UserManual)
endif()
if(BORNAGAIN_MANPAGE)
    add_subdirectory(Doc/man)
endif()
if(BORNAGAIN_CONFIGURE_DOXY)
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

if(BORNAGAIN_GUI)
    include(SearchQt)
    add_subdirectory(ThirdParty/GUI)
    add_subdirectory(GUI)
    add_subdirectory(Tests/UnitTests/GUI)
endif()

# functional tests (ctest)
add_subdirectory(Tests/Functional)

# after-install message
add_subdirectory(cmake/bornagain)

# make package targets
include(BornAgainCPack)
