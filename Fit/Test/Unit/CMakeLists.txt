include(GoogleTest) # provides gtest_discover_tests

set(test UnitTestFit)

include_directories(${CMAKE_SOURCE_DIR}/Tests/UnitTests/utilities)

file(GLOB source_files "*.cpp" ${CMAKE_SOURCE_DIR}/Tests/GTestWrapper/TestAll.cpp)

add_executable(${test} ${source_files})
target_link_libraries(${test} ${BornAgainFit_LIBRARY} gtest)

gtest_discover_tests(${test} DISCOVERY_TIMEOUT 300 TEST_PREFIX Fit.Unit.)
