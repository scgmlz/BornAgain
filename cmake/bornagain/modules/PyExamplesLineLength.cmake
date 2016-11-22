set(WEB_LEN_LIM 85) # maximum line length of code for display in Drupal web pages

# Check whether the line length of all python examples remains below WEB_LEN_LIM

if(NOT MSVC)

file(GLOB PY_EXAMPLES "${PY_EXAMPLES_DIR}/*/ex*/*.py")

add_test(NAME "PyExamplesLineLength"
    COMMAND ${PYTHON_EXECUTABLE}
    ${CMAKE_SOURCE_DIR}/dev-tools/analyze/check-line-length.py ${WEB_LEN_LIM}
    ${PY_EXAMPLES})

endif()
