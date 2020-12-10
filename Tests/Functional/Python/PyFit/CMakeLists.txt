############################################################################
# Tests/Functional/PyFit/CMakeLists.txt
############################################################################

set(output_dir ${TEST_OUTPUT_DIR_PY_FIT})
file(MAKE_DIRECTORY ${output_dir})

file(GLOB tests RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.py")

foreach(_test ${tests})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${_test} ${output_dir}/${_test} COPYONLY)
    add_test(PyFit.${_test}
        env PYTHONPATH=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        ${Python3_EXECUTABLE} ${output_dir}/${_test})
endforeach()
