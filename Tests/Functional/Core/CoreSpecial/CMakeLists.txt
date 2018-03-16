set(test CoreSpecial)

set(test_cases
    BatchSimulation
    PolDWBAMagCylinders
    FourierTransformation
#    CoreIO
#    DetectorTest
)

# build executables for each test case
file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")
add_executable(${test} ${include_files} ${source_files})
target_link_libraries(${test} BornAgainCore BornAgainTestMachinery)

# create test cases
foreach(test_case ${test_cases})
    add_test(${test}/${test_case} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test} ${test_case})
endforeach()
