###############################################################################
# Tests/Functional/PyExamples/CMakeLists.txt
#
# Runs check_functionality.py over example scripts found in PY_EXAMPLES_DIR
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

foreach(example_path ${examples})
    get_filename_component(example_name ${example_path} NAME_WE)
    set(test_name PyExamples.${example_name})

    add_test(${test_name} ${Python3_EXECUTABLE} ${test_script} ${example_path})
    set_tests_properties(${test_name} PROPERTIES LABELS "Fullcheck")
endforeach()
