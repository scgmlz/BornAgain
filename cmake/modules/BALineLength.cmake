set(SRC_LEN_LIM 100) # maximum line length of code written by MLZ-SCG
set(WEB_LEN_LIM 85) # maximum line length of code for display in web docs

if(NOT MSVC)

    foreach(dir "Core" "Fit" "GUI")
        file(GLOB_RECURSE src1 ${dir}/*.cpp)
        file(GLOB_RECURSE src2 ${dir}/*.h)
        add_test(NAME "LineLength_Cpp_${dir}"
            COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_SOURCE_DIR}/devtools/analyze/check-line-length.py ${SRC_LEN_LIM}
            ${src1} ${src2})
    endforeach()

    foreach(dir "Core" "Fit" "GUI")
        file(GLOB_RECURSE src1 ${dir}/*CMakeLists.txt)
        add_test(NAME "LineLength_CMake_${dir}"
            COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_SOURCE_DIR}/devtools/analyze/check-line-length.py ${SRC_LEN_LIM}
            ${src1})
    endforeach()

    file(GLOB sources "${PY_EXAMPLES_DIR}/*/ex*/*.py")
    add_test(NAME "LineLength_PyExamples" COMMAND ${Python3_EXECUTABLE}
        ${CMAKE_SOURCE_DIR}/devtools/analyze/check-line-length.py ${WEB_LEN_LIM} ${sources})

endif()
