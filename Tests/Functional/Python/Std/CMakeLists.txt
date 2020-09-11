include(GoogleTest) # provides gtest_discover_tests

set(test TestPyStd)

file(GLOB source_files "*.cpp" "../../Std/Run.cpp")

add_executable(${test} ${source_files} ${CMAKE_SOURCE_DIR}/Tests/GTestWrapper/TestAll.cpp)
target_include_directories(${test} PUBLIC
    ${BornAgainCore_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/ThirdParty/common/gtest/gtest-1.8.0/include)
target_link_libraries(${test} BornAgainCore gtest)

gtest_discover_tests(${test} DISCOVERY_TIMEOUT 300 TEST_PREFIX Py.)

file(MAKE_DIRECTORY ${TEST_OUTPUT_DIR}/Functional/Python/Std)
