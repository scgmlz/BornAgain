############################################################################
# CMakeLists.txt file for building libBornAgainFit library
############################################################################

set(lib BornAgainFit)

# --- source and include files ------
file(GLOB source_files */*.cpp)
file(GLOB include_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */*.h)

if(BORNAGAIN_PYTHON)

    set(AUTO_DIR ${CMAKE_SOURCE_DIR}/auto/Wrap)
    file(MAKE_DIRECTORY ${AUTO_DIR})

    if(BORNAGAIN_GENERATE_BINDINGS)

        set(WRAP_DIR ${CMAKE_SOURCE_DIR}/Wrap)
        set(TMP_DIR ${CMAKE_CURRENT_BINARY_DIR}/Wrap)
        file(MAKE_DIRECTORY ${TMP_DIR})

        GeneratePythonDocs(${AUTO_DIR}/doxygen_fit.i ${WRAP_DIR}/swig)

        set(swig_dependencies
            ${WRAP_DIR}/swig/libBornAgainFit.i
            ${WRAP_DIR}/swig/directors.i
            ${WRAP_DIR}/swig/extendFit.i
            ${WRAP_DIR}/swig/ignores.i
            ${WRAP_DIR}/swig/shared_pointers.i
            ${WRAP_DIR}/swig/warnings.i
            )
        foreach(FNAM ${swig_dependencies})
            if(NOT EXISTS ${FNAM})
                message(FATAL_ERROR "Could NOT find SWIG input ${FNAM}")
            endif()
        endforeach()
        list(APPEND swig_dependencies ${AUTO_DIR}/doxygen_fit.i)

        set(SWIG_FLAGS "-c++;-python;-o;${AUTO_DIR}/libBornAgainFit_wrap.cpp;-outdir;${TMP_DIR}"
            ";-I${CMAKE_SOURCE_DIR}")

        add_custom_command(
            OUTPUT ${AUTO_DIR}/libBornAgainFit.py
            COMMAND ${Python3_EXECUTABLE} ${WRAP_DIR}/swig/tweaks.py
                   ${TMP_DIR}/libBornAgainFit.py
                   ${AUTO_DIR}/libBornAgainFit.py
            DEPENDS ${TMP_DIR}/libBornAgainFit.py
            )
        add_custom_command(
            OUTPUT ${TMP_DIR}/libBornAgainFit.py
                   ${AUTO_DIR}/libBornAgainFit_wrap.h
                   ${AUTO_DIR}/libBornAgainFit_wrap.cpp
            COMMAND ${SWIG_EXECUTABLE} ${SWIG_FLAGS} ${WRAP_DIR}/swig/libBornAgainFit.i
            DEPENDS ${swig_dependencies} ${include_files}
            )

    endif(BORNAGAIN_GENERATE_BINDINGS)

    add_custom_target(
        ${lib}_python
        COMMAND ${CMAKE_COMMAND} -E copy ${AUTO_DIR}/libBornAgainFit.py
             ${CMAKE_BINARY_DIR}/lib/libBornAgainFit.py
        COMMAND ${CMAKE_COMMAND} -E copy ${AUTO_DIR}/libBornAgainFit.py
             ${CMAKE_BINARY_DIR}/lib/bornagain/libBornAgainFit.py
        DEPENDS ${AUTO_DIR}/libBornAgainFit.py
        )

    if((CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            OR (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
        # suppress warnings from auto-generated code (last updated for Swig 4.0.1)
        set_source_files_properties(${AUTO_DIR}/libBornAgainFit_wrap.cpp
            PROPERTIES COMPILE_OPTIONS
            "-Wno-unused-parameter;-Wno-missing-field-initializers;-Wno-deprecated-declarations")
    endif()

    list(APPEND source_files "${AUTO_DIR}/libBornAgainFit_wrap.cpp")

endif()

# --- definitions ---------
if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBA_CORE_BUILD_DLL")
endif()

# --- making library ---------
add_library(${lib} SHARED ${source_files})
set_target_properties(${lib} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(${lib}_LIBRARY_TYPE SHARED)

if(BORNAGAIN_PYTHON)
    add_dependencies(${lib} ${lib}_python)
endif()

# exposing library name and list of include directories outside
set(${lib}_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${WRAP_DIR} PARENT_SCOPE)
set(${lib}_LIBRARY ${lib} PARENT_SCOPE)

# --- dependencies ---------
target_include_directories(${lib}
    PUBLIC ${RootMinimizers_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
target_link_libraries(${lib} ${RootMinimizers_LIBRARY} ${Boost_LIBRARIES})

if(BORNAGAIN_PYTHON)
    target_include_directories(${lib}
        PUBLIC ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})
    target_link_libraries(${lib} ${Python3_LIBRARIES})
endif()

# --- custom actions
# python in windows required .pyd extention for the library name
if(WIN32 AND BORNAGAIN_PYTHON)
    add_custom_command(
        TARGET ${lib}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/bin/${libprefix}${lib}${libsuffix}
        ${CMAKE_BINARY_DIR}/lib/${libprefix}${lib}".pyd"
        )
    # for functional tests
    add_custom_command(
        TARGET ${lib}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/bin/${libprefix}${lib}${libsuffix}
        ${CMAKE_BINARY_DIR}/lib/${libprefix}${lib}${libsuffix}
        )

endif()

if(APPLE AND BORNAGAIN_APPLE_BUNDLE)
    #    set(link_flags "-Wl,-rpath,@loader_path/../..")
    set(link_flags "-Wl,-rpath,@loader_path/../../Frameworks")
    set_target_properties(${lib} PROPERTIES LINK_FLAGS ${link_flags})
endif()

# -----------------------------------------------
# installation
# -----------------------------------------------
install(TARGETS ${lib} DESTINATION ${destination_lib} COMPONENT Libraries)
install(FILES ${CMAKE_BINARY_DIR}/lib/lib${lib}.py
    DESTINATION ${destination_lib} COMPONENT Libraries) # required by SWIG

foreach(file ${include_files})
    get_filename_component(dir ${file} DIRECTORY)
    install(FILES ${file} DESTINATION ${destination_include}/Fit/${dir})
endforeach()

if(WIN32)
    if(BORNAGAIN_PYTHON)
        add_custom_command(
            TARGET ${lib}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_BINARY_DIR}/bin/${libprefix}${lib}${libsuffix}
            ${CMAKE_BINARY_DIR}/lib/${libprefix}${lib}".pyd"
            )

        install(FILES ${CMAKE_BINARY_DIR}/lib/${libprefix}${lib}.pyd
            DESTINATION ${destination_lib} COMPONENT Libraries)
    endif()
endif()
