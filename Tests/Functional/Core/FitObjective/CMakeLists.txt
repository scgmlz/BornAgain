set(test TestFitObjective)

set(test_cases
    MigradCylindersInBA
    MigradResidualCylindersInBA
    SpecularFitTest
    SpecularFitTestQ
    MultipleSpecFittingTest
    FumuliCylindersInBA
    LevenbergMarquardtCylindersInBA
    RectDetectorFit
    OffSpecFitTest
    # --- slow, but still converging ---
    # SimAnCylindersInBA
    # GeneticCylindersInBA
    # SteepestDescentCylindersInBA
    # AdjustMinimizerFit
    # BfgsCylindersInBA
)

include_directories(${RootMinimizers_INCLUDE_DIRS})

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

add_executable(${test} ${include_files} ${source_files})
target_link_libraries(${test} BornAgainCore BornAgainTestMachinery)

foreach(test_case ${test_cases})
    add_test(${test}/${test_case} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test} ${test_case})
endforeach()
