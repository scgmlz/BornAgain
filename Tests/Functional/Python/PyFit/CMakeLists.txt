############################################################################
# Tests/Functional/PyFit/CMakeLists.txt
############################################################################

set(output_dir ${TEST_OUTPUT_DIR}/Functional/Python/PyFit)
file(MAKE_DIRECTORY ${output_dir})

file(GLOB sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.py")
foreach(_src ${sources})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${_src}
         ${output_dir}/${_src} @ONLY)
endforeach()

set(tests
    "minimizer_api.py"
    "standalone_fits.py"
    "fitobjective_api.py"
)

foreach(_test ${tests})
    add_test(PyFit/${_test} ${Python3_EXECUTABLE}  ${output_dir}/${_test})
endforeach()
