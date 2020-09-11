# configure Doxyfiles; define targets doxy and doxy${flavor}
set(AUTO_DOX_DIR ${CMAKE_BINARY_DIR}/doxygen)
file(MAKE_DIRECTORY ${AUTO_DOX_DIR})
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/html)
add_custom_target(doxy) # this target builds _all_ documentation flavors
foreach(flavor user long dirgraphs)
    configure_file(Doxyfile.${flavor}.in
        ${AUTO_DOX_DIR}/Doxyfile.${flavor} @ONLY)
    add_custom_target(doxy${flavor}
        COMMAND doxygen ${AUTO_DOX_DIR}/Doxyfile.${flavor} )
    add_dependencies(doxy doxy${flavor})
endforeach()
