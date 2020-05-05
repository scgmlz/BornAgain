############################################################################
# CMakeLists.txt file for building libBornAgainCore library
############################################################################

set(library_name BornAgainCore)

if(BORNAGAIN_TIDY)
#    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=-*,readability-*,-readability-braces-around-statements")
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=-*,clang-analyzer-*,readability-*,-readability-braces-around-statements,modernize-*")
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*,-google-*,-misc-macro-parentheses,-readability-braces-around-statements,-readability-named-parameter,-llvm-namespace-comment")
endif()

# --- source and include files ---------
include(GlobDirectories)
GLOB_DIRECTORIES(CORE_SUBDIRS)

set(CORE_SOURCE_DIRS "")
foreach(subdir ${CORE_SUBDIRS})
    list(APPEND CORE_SOURCE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}")
endforeach()

set(include_dirs
    ${BUILD_INC_DIR}
    ${CMAKE_SOURCE_DIR}/Wrap
    ${CORE_SOURCE_DIRS}
    ${BornAgainFit_INCLUDE_DIRS}
    )

include_directories(${include_dirs})

file(GLOB source_files "*/*.cpp")
file(GLOB include_files "*/*.h")

if(BORNAGAIN_PYTHON)

    set(WRAP_DIR ${CMAKE_SOURCE_DIR}/Wrap)
    set(AUTO_DIR ${CMAKE_SOURCE_DIR}/auto/Wrap)
    file(MAKE_DIRECTORY ${AUTO_DIR})
    include_directories(${AUTO_DIR})

    if(BORNAGAIN_GENERATE_BINDINGS)

        set(TMP_DIR ${CMAKE_CURRENT_BINARY_DIR}/Wrap)
        file(MAKE_DIRECTORY ${TMP_DIR})

        GeneratePythonDocs(${AUTO_DIR}/doxygen_core.i ${WRAP_DIR}/swig)

        set(swig_dependencies
            ${WRAP_DIR}/swig/libBornAgainCore.i
            ${WRAP_DIR}/swig/directors.i
            ${WRAP_DIR}/swig/extendCore.i
            ${WRAP_DIR}/swig/ignores.i
            ${WRAP_DIR}/swig/shared_pointers.i
            ${WRAP_DIR}/swig/warnings.i
            )
        foreach(FNAM ${swig_dependencies})
            if(NOT EXISTS ${FNAM})
                message(FATAL_ERROR "Could NOT find SWIG input ${FNAM}")
            endif()
        endforeach()
        set(swig_dependencies ${swig_dependencies} ${AUTO_DIR}/doxygen_core.i)

        set(SWIG_FLAGS "-c++;-python;-o;${AUTO_DIR}/libBornAgainCore_wrap.cpp;-outdir;${TMP_DIR}")
        set(SWIG_RUNTIME_FLAGS "-c++;-python;-external-runtime;${AUTO_DIR}/swig_runtime.h")
        foreach(dir ${include_dirs})
            list(APPEND SWIG_FLAGS "-I${dir}")
        endforeach(dir)

        add_custom_command (
            OUTPUT ${AUTO_DIR}/libBornAgainCore.py
            COMMAND ${Python_EXECUTABLE} ${WRAP_DIR}/swig/tweaks.py
                   ${TMP_DIR}/libBornAgainCore.py
                   ${AUTO_DIR}/libBornAgainCore.py
            DEPENDS ${TMP_DIR}/libBornAgainCore.py
            )
        add_custom_command (
            OUTPUT ${TMP_DIR}/libBornAgainCore.py
                   ${AUTO_DIR}/libBornAgainCore_wrap.h
                   ${AUTO_DIR}/libBornAgainCore_wrap.cpp
            COMMAND ${SWIG_EXECUTABLE} ${SWIG_FLAGS} ${WRAP_DIR}/swig/libBornAgainCore.i
            DEPENDS ${swig_dependencies} ${include_files}
            )

        add_custom_command (
            OUTPUT ${AUTO_DIR}/swig_runtime.h
            COMMAND ${SWIG_EXECUTABLE} ${SWIG_RUNTIME_FLAGS}
            DEPENDS ${swig_dependencies} ${include_files}
            )

    endif(BORNAGAIN_GENERATE_BINDINGS)

    add_custom_target (
        ${library_name}_python
        COMMAND ${CMAKE_COMMAND} -E copy
            ${AUTO_DIR}/libBornAgainCore.py ${CMAKE_BINARY_DIR}/lib/libBornAgainCore.py
        COMMAND ${CMAKE_COMMAND} -E copy
            ${AUTO_DIR}/libBornAgainCore.py ${CMAKE_BINARY_DIR}/lib/bornagain/libBornAgainCore.py
        DEPENDS ${AUTO_DIR}/libBornAgainCore.py
        )

    add_custom_target(${library_name}_runtime DEPENDS ${AUTO_DIR}/swig_runtime.h)

    list(APPEND source_files "${AUTO_DIR}/libBornAgainCore_wrap.cpp")
    list(APPEND include_files "${AUTO_DIR}/swig_runtime.h")

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
endif()


if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBA_CORE_BUILD_DLL")
endif()


# --- making library ---------
add_library(${library_name} SHARED ${include_files} ${source_files})

set_target_properties(${library_name} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(${library_name}_LIBRARY_TYPE SHARED)


if(BORNAGAIN_PYTHON)
    add_dependencies(${library_name} ${library_name}_python ${library_name}_runtime)
endif()

# exposing library name and list of include directories outside
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)


# --- external dependencies ---------

target_link_libraries(${library_name} ${BornAgainFit_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})

if(BORNAGAIN_TIFF_SUPPORT)
    target_compile_definitions(${library_name} PUBLIC -DBORNAGAIN_TIFF_SUPPORT)
    target_include_directories(${library_name} PUBLIC ${TIFF_INCLUDE_DIR})
    target_link_libraries(${library_name} ${TIFF_LIBRARIES})
endif()

target_include_directories(${library_name} PUBLIC ${include_dirs})
target_include_directories(${library_name} SYSTEM PUBLIC ${EIGEN3_INCLUDE_DIR})
target_include_directories(${library_name} PUBLIC ${Boost_INCLUDE_DIRS} ${FFTW_INCLUDE_DIR}
    ${GSL_INCLUDE_DIR} ${tspectrum_INCLUDE_DIR} PRIVATE ${Faddeeva_INCLUDE_DIR})
target_link_libraries(${library_name} ${Boost_LIBRARIES} ${FFTW_LIBRARY} ${GSL_LIBRARIES}
    ${Faddeeva_LIBRARY} ${tspectrum_LIBRARY})

if(BORNAGAIN_MPI)
    add_definitions(-DBORNAGAIN_MPI)
    include_directories(${MPI_INCLUDE_PATH})
    target_link_libraries(${library_name} ${MPI_LIBRARIES})
endif()

if(BORNAGAIN_PYTHON)
    target_compile_definitions(${library_name} PUBLIC -DBORNAGAIN_PYTHON)
    include_directories(${Python_INCLUDE_DIRS} ${Python_NumPy_INCLUDE_DIRS})
    target_link_libraries(${library_name} ${Python_LIBRARIES})
endif()

if(APPLE AND BORNAGAIN_APPLE_BUNDLE)
    set(link_flags "-Wl,-rpath,@loader_path/../../Frameworks")
    set_target_properties(${library_name}
        PROPERTIES
        LINK_FLAGS ${link_flags}
        )
endif()


# --- installation ---------

install (DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/ DESTINATION ${destination_examples} COMPONENT Examples FILES_MATCHING PATTERN "*.py" )
install (DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/ DESTINATION ${destination_examples} COMPONENT Examples FILES_MATCHING PATTERN "README")
install (DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/ DESTINATION ${destination_examples} COMPONENT Examples FILES_MATCHING PATTERN "*.gz")
install (DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/ DESTINATION ${destination_examples} COMPONENT Examples FILES_MATCHING PATTERN "*.png")
install (DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/cpp DESTINATION ${destination_examples} COMPONENT Examples)
install (TARGETS ${library_name} DESTINATION ${destination_lib} COMPONENT Libraries)
install (FILES ${CMAKE_BINARY_DIR}/lib/lib${library_name}.py DESTINATION ${destination_lib} COMPONENT Libraries) # required by swig
install (FILES ${include_files} DESTINATION ${destination_include} COMPONENT Headers)
install (FILES ${CMAKE_SOURCE_DIR}/Wrap/WinDllMacros.h DESTINATION ${destination_include} COMPONENT Headers)

if(WIN32)
    # python in windows required .pyd extention for the library name
    if(BORNAGAIN_PYTHON)
        add_custom_command(
            TARGET ${library_name}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_BINARY_DIR}/bin/${libprefix}${library_name}${libsuffix}
            ${CMAKE_BINARY_DIR}/lib/${libprefix}${library_name}".pyd"
            )
        install(FILES ${CMAKE_BINARY_DIR}/lib/${libprefix}${library_name}.pyd DESTINATION ${destination_lib} COMPONENT Libraries)
        add_custom_command(
            TARGET ${library_name}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_BINARY_DIR}/bin/${libprefix}${library_name}${libsuffix}
            ${CMAKE_BINARY_DIR}/lib/${libprefix}${library_name}${libsuffix}
            )
    endif()

    # system libraries
    foreach(Boost_lib ${Boost_LIBRARIES})
        get_filename_component(UTF_BASE_NAME ${Boost_lib} NAME_WE)
        get_filename_component(UTF_PATH ${Boost_lib} PATH)
        message(STATUS "Boost dll: ${UTF_PATH}/${UTF_BASE_NAME}.dll")
        install(FILES ${UTF_PATH}/${UTF_BASE_NAME}.dll
            DESTINATION ${destination_lib} COMPONENT Libraries)
    endforeach()

    get_filename_component(UTF_BASE_NAME ${Python_LIBRARIES} NAME_WE)
    get_filename_component(UTF_PATH ${Python_EXECUTABLE} PATH)
    message(STATUS "Python dll: ${UTF_PATH}/${UTF_BASE_NAME}.dll")
    install(FILES ${UTF_PATH}/${UTF_BASE_NAME}.dll
        DESTINATION ${destination_lib} COMPONENT Libraries)

    install(FILES
        ${FFTW_LIBRARY_DLL}
        ${TIFF_LIBRARY_DLL}
        DESTINATION ${destination_lib} COMPONENT Libraries)

else()
    # Install thisbornagain.sh.
    install(FILES
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/thisbornagain.sh
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/thisbornagain.csh
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
        DESTINATION ${destination_libexec})

    if(NOT BORNAGAIN_APPLE_BUNDLE AND NOT BUILD_DEBIAN)
        # Create bin directory for links.
        install(CODE "
            FILE(MAKE_DIRECTORY \"${CMAKE_INSTALL_PREFIX}/${destination_bin}\")
            "
            COMPONENT Runtime)
        # Make links.
        install(CODE "
        execute_process(COMMAND \${CMAKE_COMMAND} -E create_symlink
        \"../${destination_libexec}/thisbornagain.sh\" \"thisbornagain.sh\"
        WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}/${destination_bin}\")
        " COMPONENT Runtime)
        install(CODE "
        execute_process(COMMAND \${CMAKE_COMMAND} -E create_symlink
        \"../${destination_libexec}/thisbornagain.csh\" \"thisbornagain.csh\"
        WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}/${destination_bin}\")
        " COMPONENT Runtime)
    else()

        install(FILES ${WRAP_DIR}/python/bornagain_python_install.py
            DESTINATION ${destination_libexec})
    endif()
endif()

# Install bornagain/__init__.py and utilites
install(DIRECTORY "${CMAKE_BINARY_DIR}/lib/bornagain/"
        DESTINATION "${destination_libexec}/bornagain"
        COMPONENT Libraries
        FILES_MATCHING PATTERN "*.py"
        PATTERN "__pycache__" EXCLUDE)
