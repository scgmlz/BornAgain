############################################################################
# Fit unit tests
############################################################################

set(test UnitTestFit)

file(GLOB source_files "*.cpp" "run_gtests.cpp")

add_executable(${test} ${source_files})
target_include_directories(${test} PUBLIC ${gtest_SOURCE_DIR}/include)
target_link_libraries(${test} PRIVATE ${BornAgainFit_LIBRARY} gtest)

# add execution of TestCore just after compilation
add_custom_target(${test}_run ALL DEPENDS ${test} COMMAND ${test})
