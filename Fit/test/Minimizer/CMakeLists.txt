set(test TestMinimizer)

set(test_cases
    MinuitTestV1
    MinuitTestV2
    MinuitTestV3
    #SteepestDescentTestV1 <-- not able to fit Rosenbrock function
    SteepestDescentTestV2
    ConjugateFRTestV1
    ConjugateFRTestV2
    ConjugatePRTestV1
    ConjugatePRTestV2
    BfgsTestV1
    BfgsTestV2
    Bfgs2TestV1
    Bfgs2TestV2
    GSLSimAnTestV1
    GSLSimAnTestV2
    GeneticTestV1
    GeneticTestV2
    FumiliTestV3
    LevenbergMarquardtV3
)

include_directories(${RootMinimizers_INCLUDE_DIRS})

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

add_executable(${test} ${include_files} ${source_files})
target_include_directories(${test} PRIVATE ../engine)
target_link_libraries(${test} BornAgainCore BornAgainFitTestMachinery)

foreach(test_case ${test_cases})
    add_test(${test}/${test_case} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test} ${test_case})
endforeach()
