set(SRC_LEN_LIM 100) # maximum line length of code written by MLZ-SCG

if(NOT MSVC)

    file(GLOB_RECURSE SRC1 "Core/*.cpp")
    file(GLOB_RECURSE SRC2 "Core/*.h")
    file(GLOB_RECURSE SRC1 "Fit/*.cpp")
    file(GLOB_RECURSE SRC2 "Fit/*.h")
#   file(GLOB_RECURSE SRC1 "GUI/*.cpp")
#   file(GLOB_RECURSE SRC2 "GUI/*.h")

    add_test(NAME "CodeLineLength"
        COMMAND ${PYTHON_EXECUTABLE}
        ${CMAKE_SOURCE_DIR}/dev-tools/analyze/check-line-length.py ${SRC_LEN_LIM}
        ${SRC1} ${SRC2})
endif()
