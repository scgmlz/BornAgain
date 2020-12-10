############################################################################
# Tests/Functional/PyCore/scripts/CMakeLists.txt
############################################################################

set(OUTPUT_DIR ${TEST_OUTPUT_DIR_PY_CORE})
file(MAKE_DIRECTORY ${OUTPUT_DIR})

file(GLOB tests RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.py")
list(REMOVE_ITEM tests utils.py)
if(NOT BORNAGAIN_TIFF_SUPPORT)
    list(REMOVE_ITEM tests "intensitydata_io_tiff.py")
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/utils.py ${OUTPUT_DIR}/utils.py @ONLY)

foreach(_test ${tests})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${_test} ${OUTPUT_DIR}/${_test} COPYONLY)
    add_test(PyCore.${_test}
        env PYTHONPATH=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        ${Python3_EXECUTABLE} ${OUTPUT_DIR}/${_test})
endforeach()
