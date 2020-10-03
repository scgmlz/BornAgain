# Configure and install swig runtime and Python code, in particular examples and plot_utils

if(NOT BORNAGAIN_PYTHON)
    return()
endif()

if(CONFIGURE_BINDINGS)
    add_custom_command(
        OUTPUT ${AUTO_DIR}/swig_runtime.h
        COMMAND ${SWIG_EXECUTABLE} -c++;-python;-external-runtime;${AUTO_DIR}/swig_runtime.h
        DEPENDS ${swig_dependencies} ${include_files}
        )
endif()
add_custom_target(swig_runtime DEPENDS ${AUTO_DIR}/swig_runtime.h)
add_dependencies(BornAgainCore swig_runtime)

configure_file(${WRAP_DIR}/python/plot_utils.py
               ${CMAKE_BINARY_DIR}/lib/bornagain/plot_utils.py COPYONLY)

if(WIN32)
    set(BA_MODULES_IMPORT_PATH "../../bin")
else()
    set(BA_MODULES_IMPORT_PATH "..")
endif()
if(BORNAGAIN_APPLE_BUNDLE)
    set(BA_MODULES_IMPORT_PATH
        lib/BornAgain-${BornAgain_VERSION_MAJOR}.${BornAgain_VERSION_MINOR})
endif()
configure_file("${WRAP_DIR}/python/__init__.py.in"
               "${CMAKE_BINARY_DIR}/lib/bornagain/__init__.py" @ONLY)


install(DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/
    DESTINATION ${destination_examples} COMPONENT Examples FILES_MATCHING PATTERN "*.py" )
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/
    DESTINATION ${destination_examples} COMPONENT Examples FILES_MATCHING PATTERN "README")
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/
    DESTINATION ${destination_examples} COMPONENT Examples FILES_MATCHING PATTERN "*.gz")
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/
    DESTINATION ${destination_examples} COMPONENT Examples FILES_MATCHING PATTERN "*.png")
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/cpp
    DESTINATION ${destination_examples} COMPONENT Examples)
install(FILES "${AUTO_DIR}/swig_runtime.h"
    DESTINATION ${destination_include}/Wrap COMPONENT Headers)
install(FILES ${CMAKE_SOURCE_DIR}/Wrap/WinDllMacros.h
    DESTINATION ${destination_include}/Wrap COMPONENT Headers)

# Install bornagain/__init__.py and utilites
install(DIRECTORY "${CMAKE_BINARY_DIR}/lib/bornagain/"
        DESTINATION "${destination_libexec}/bornagain"
        COMPONENT Libraries
        FILES_MATCHING PATTERN "*.py"
        PATTERN "__pycache__" EXCLUDE)

if(WIN32)
    set(win_python_lib
        "${Python3_LIBRARY_DIRS}/python${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR}.lib")
    get_filename_component(UTF_BASE_NAME ${win_python_lib} NAME_WE)
    get_filename_component(UTF_PATH ${Python3_EXECUTABLE} PATH)
    message(STATUS "Python dll: ${UTF_PATH}/${UTF_BASE_NAME}.dll")
    install(FILES ${UTF_PATH}/${UTF_BASE_NAME}.dll
        DESTINATION ${destination_lib} COMPONENT Libraries)
endif()
