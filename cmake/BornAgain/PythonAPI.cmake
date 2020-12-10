# Configure and install the Swig runtime, the BornAgain Python module, and more

if(NOT BORNAGAIN_PYTHON)
    message(FATAL_ERROR PythonAPI included though BORNAGAIN_PYTHON=false)
endif()

if(WIN32)
    set(BA_MODULES_IMPORT_PATH ../../bin)
else()
    set(BA_MODULES_IMPORT_PATH ..)
endif()
if(BORNAGAIN_APPLE_BUNDLE)
    set(BA_MODULES_IMPORT_PATH
        lib/BornAgain-${BornAgain_VERSION_MAJOR}.${BornAgain_VERSION_MINOR})
endif()

configure_file(${WRAP_DIR}/Python/__init__.py.in
    ${CMAKE_BINARY_DIR}/lib/bornagain/__init__.py @ONLY)
foreach(mod plot_utils.py fit_monitor.py)
    configure_file(${WRAP_DIR}/Python/${mod} ${CMAKE_BINARY_DIR}/lib/bornagain/${mod} COPYONLY)
endforeach()

if(CONFIGURE_BINDINGS)
    add_custom_command(
        OUTPUT ${AUTO_DIR}/swig_runtime.h
        COMMAND ${SWIG_EXECUTABLE} -c++;-python;-external-runtime;${AUTO_DIR}/swig_runtime.h
        DEPENDS ${swig_dependencies} ${include_files}
        )
endif()

add_custom_target(swig_runtime DEPENDS ${AUTO_DIR}/swig_runtime.h)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/
    DESTINATION ${destination_examples} COMPONENT Examples FILES_MATCHING PATTERN *.py )
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/
    DESTINATION ${destination_examples} COMPONENT Examples FILES_MATCHING PATTERN README)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/
    DESTINATION ${destination_examples} COMPONENT Examples FILES_MATCHING PATTERN *.gz)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/
    DESTINATION ${destination_examples} COMPONENT Examples FILES_MATCHING PATTERN *.png)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/cpp
    DESTINATION ${destination_examples} COMPONENT Examples)
install(FILES ${AUTO_DIR}/swig_runtime.h
    DESTINATION ${destination_include}/Wrap COMPONENT Headers)

# Install bornagain/__init__.py and utilites
install(DIRECTORY ${CMAKE_BINARY_DIR}/lib/bornagain/
        DESTINATION ${destination_libexec}/bornagain
        COMPONENT Libraries
        FILES_MATCHING PATTERN *.py
        PATTERN __pycache__ EXCLUDE)
