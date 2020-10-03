function(SwigLib name lib)

    if(not BORNAGAIN_PYTHON)
        return()
    endif()

    set(WRAP_DIR ${CMAKE_SOURCE_DIR}/Wrap)
    set(AUTO_DIR ${CMAKE_SOURCE_DIR}/auto/Wrap)
    file(MAKE_DIRECTORY ${AUTO_DIR})

    if(CONFIGURE_BINDINGS)

        set(TMP_DIR ${CMAKE_CURRENT_BINARY_DIR}/Wrap)
        file(MAKE_DIRECTORY ${TMP_DIR})

        GeneratePythonDocs(${AUTO_DIR}/doxygen${name}.i ${WRAP_DIR}/swig)

        set(swig_dependencies
            ${WRAP_DIR}/swig/lib${lib}.i
            ${WRAP_DIR}/swig/directors.i
            ${WRAP_DIR}/swig/extend${name}.i
            ${WRAP_DIR}/swig/ignores.i
            ${WRAP_DIR}/swig/shared_pointers.i
            ${WRAP_DIR}/swig/warnings.i
            )
        foreach(FNAM ${swig_dependencies})
            if(NOT EXISTS ${FNAM})
                message(FATAL_ERROR "Could NOT find SWIG input ${FNAM}")
            endif()
        endforeach()
        list(APPEND swig_dependencies ${AUTO_DIR}/doxygen${name}.i)

        set(SWIG_FLAGS "-c++;-python;-o;${AUTO_DIR}/lib${lib}_wrap.cpp;-outdir;${TMP_DIR}"
                               ";-I${CMAKE_SOURCE_DIR};-I${CMAKE_BINARY_DIR}/inc")

        add_custom_command(
            OUTPUT ${AUTO_DIR}/lib${lib}.py
            COMMAND ${Python3_EXECUTABLE} ${WRAP_DIR}/swig/tweaks.py
                   ${TMP_DIR}/lib${lib}.py
                   ${AUTO_DIR}/lib${lib}.py
            DEPENDS ${TMP_DIR}/lib${lib}.py
            )
        add_custom_command(
            OUTPUT ${TMP_DIR}/lib${lib}.py
                   ${AUTO_DIR}/lib${lib}_wrap.h
                   ${AUTO_DIR}/lib${lib}_wrap.cpp
            COMMAND ${SWIG_EXECUTABLE} ${SWIG_FLAGS} ${WRAP_DIR}/swig/lib${lib}.i
            DEPENDS ${swig_dependencies} ${include_files}
            )

    endif(CONFIGURE_BINDINGS)

    add_custom_target(
        ${lib}_python
        COMMAND ${CMAKE_COMMAND}
            -E copy ${AUTO_DIR}/lib${lib}.py ${CMAKE_BINARY_DIR}/lib/lib${lib}.py
        COMMAND ${CMAKE_COMMAND}
            -E copy ${AUTO_DIR}/lib${lib}.py ${CMAKE_BINARY_DIR}/lib/bornagain/lib${lib}.py
        DEPENDS ${AUTO_DIR}/lib${lib}.py
        )

    if((CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            OR (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
        # suppress warnings from auto-generated code (last updated for Swig 4.0.1)
        set_source_files_properties(${AUTO_DIR}/lib${lib}_wrap.cpp
            PROPERTIES COMPILE_OPTIONS
            "-Wno-unused-parameter;-Wno-missing-field-initializers;-Wno-sometimes-uninitialized;\
-Wno-deprecated-declarations")
    endif()

    list(APPEND source_files "${AUTO_DIR}/lib${lib}_wrap.cpp")

endif(BORNAGAIN_PYTHON)

endfunction()
