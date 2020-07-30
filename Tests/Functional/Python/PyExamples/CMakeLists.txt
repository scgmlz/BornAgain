###############################################################################
# Tests/Functional/PyExamples/CMakeLists.txt
#
# > Test functionality of all examples found in PY_EXAMPLES_DIR = <BornAgain>/Examples/python
# > Validates selected examples against reference files
#
###############################################################################

set(output_dir ${TEST_OUTPUT_DIR}/Functional/Python/PyExamples)
file(MAKE_DIRECTORY ${output_dir})

file(GLOB sim_examples "${PY_EXAMPLES_DIR}/simulation/ex*/*.py")
file(GLOB fit_examples
    "${PY_EXAMPLES_DIR}/fitting/ex03_ExtendedExamples/specular/FitSpecularBasics.py")
set(examples ${sim_examples} ${fit_examples})

set(test_script ${output_dir}/check_functionality.py)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/check_functionality.py ${test_script} @ONLY)

foreach(example ${examples})
    set(script_path ${example})

    get_filename_component(script_name ${script_path} NAME_WE)
    set(test_name PyExamples/${script_name})

    add_test(${test_name} ${Python3_EXECUTABLE} ${test_script} ${script_path})
    set_tests_properties(${test_name} PROPERTIES LABELS "Fullcheck")
endforeach()
