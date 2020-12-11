###############################################################################
# Tests/Functional/PyExamples/CMakeLists.txt
#
# Runs check_functionality.py over example scripts found in PY_EXAMPLES_DIR
#
###############################################################################

set(output_dir ${TEST_OUTPUT_DIR_PY_EXAMPLES})
file(MAKE_DIRECTORY ${output_dir})

file(GLOB examples
    ${EXAMPLES_DIR}/scatter2d/*.py
    ${EXAMPLES_DIR}/specular/*.py
    ${EXAMPLES_DIR}/varia/*.py
    ${EXAMPLES_DIR}/fit55_Specular/FitSpecularBasics.py)
if (WIN32)
    # Convergence problem in Gauss-Kronrod integration
    list(REMOVE_ITEM examples ${EXAMPLES_DIR}/scatter2d/Interference2DParaCrystal.py)
endif()

set(test_script ${TOOL_DIR}/code-tools/batch-plot.py)

foreach(example_path ${examples})
    get_filename_component(example_name ${example_path} NAME_WE)
    set(test_name PyExamples.${example_name})
    add_test(${test_name}
        env PYTHONPATH=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        ${Python3_EXECUTABLE} ${test_script} -s ${example_path} ${output_dir})
endforeach()
