############################################################################
# Fit unit tests
############################################################################

include(GoogleTest)

set(test FitUnitTest)

file(GLOB source_files "*.cpp" "run_gtests.cpp")

add_executable(${test} ${source_files})
target_include_directories(${test} PUBLIC ${gtest_SOURCE_DIR}/include)
target_link_libraries(${test} PRIVATE ${BornAgainFit_LIBRARY} gtest)

gtest_discover_tests(${test} TEST_PREFIX Fit:Unit:)
