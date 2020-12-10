#   ************************************************************************************************
#
#   BornAgain: simulate and fit scattering at grazing incidence
#
#!  @file      Tests/Functional/Python/Std/CMakeLists.txt
#!  @brief     Builds Python standard tests.
#
#              .../Std/TestAll.cpp provides main, which essentially runs RUN_ALL_TESTS().
#              RUN_ALL_TESTS is a gtest macro that runs tests defined by TEST_F macros.
#              .../Std/Run.cpp uses such TEST_F macros to define our standard test cases.
#              Check.cpp provides a callback function that executes one Python tests:
#              Export a simulation to Python, run that Python script, and compare the
#              result with a direct simulation in the C++ core.
#
#!  @homepage  http://www.bornagainproject.org
#!  @license   GNU General Public License v3 or higher (see COPYING)
#!  @copyright Forschungszentrum Jülich GmbH 2018
#!  @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
#
#   ************************************************************************************************

include(GoogleTest) # provides gtest_discover_tests

set(test TestPyStd)

set(source_files Check.cpp ../../Std/Run.cpp ${CMAKE_SOURCE_DIR}/Tests/GTestWrapper/TestAll.cpp)

add_executable(${test} ${source_files})
target_compile_options(${test} PUBLIC -DPYTHON_STD_TEST)

target_include_directories(${test} PUBLIC
    ${BornAgainCore_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/ThirdParty/common/gtest/gtest-1.8.0/include)
target_link_libraries(${test} BornAgainCore gtest)

gtest_discover_tests(${test} DISCOVERY_TIMEOUT 300 TEST_PREFIX Py.)

file(MAKE_DIRECTORY ${TEST_OUTPUT_DIR_PY_STD})
