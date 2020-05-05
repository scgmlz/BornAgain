# Autogenerate a .i file from doxygen comments, provided -DBORNAGAIN_GENERATE_PYTHON_DOCS=ON.

function(GeneratePythonDocs PD_TARGET SWIG_DIR)
    if(BORNAGAIN_GENERATE_PYTHON_DOCS)

        configure_file(${SWIG_DIR}/DoxyfileSwig.in ${TMP_DIR}/Doxyfile @ONLY)

        add_custom_command(
            OUTPUT ${TMP_DIR}/xml/index.xml
            COMMAND ${DOXYGEN_EXECUTABLE} ${TMP_DIR}/Doxyfile
            DEPENDS ${include_files}
            )
        add_custom_command(
            OUTPUT ${PD_TARGET}
            COMMAND ${Python_EXECUTABLE} ${SWIG_DIR}/doxy2swig.py
            ${TMP_DIR}/xml/index.xml ${PD_TARGET}
            DEPENDS ${TMP_DIR}/xml/index.xml
            )

    endif(BORNAGAIN_GENERATE_PYTHON_DOCS)
endfunction()
