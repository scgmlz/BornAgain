############################################################################
# Tests/Functional/PyCore/scripts/CMakeLists.txt
############################################################################

set(OUTPUT_DIR ${TEST_OUTPUT_DIR}/Functional/Python/PyCore)
file(MAKE_DIRECTORY ${OUTPUT_DIR})

set(PYCORE_REFERENCE_DIR ${TEST_REFERENCE_DIR}/Python)

file(GLOB sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.py")
if(NOT BORNAGAIN_TIFF_SUPPORT)
    list(REMOVE_ITEM sources "intensitydata_io_tiff.py")
endif()

foreach(_src ${sources})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${_src}
        ${OUTPUT_DIR}/${_src} @ONLY)
endforeach()

set(tests ${sources})
list(REMOVE_ITEM tests utils.py)

foreach(_test ${tests})
    add_test(PyCore/${_test} ${Python3_EXECUTABLE} ${OUTPUT_DIR}/${_test})
endforeach()
