############################################################################
# CMakeLists.txt file for building libBornAgainFit
############################################################################

set(name Fit)
set(lib BornAgain${name})

# --- source and include files ---

file(GLOB source_files */*.cpp)
file(GLOB include_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */*.h)

if(BORNAGAIN_PYTHON)

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

# --- making library ---

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBA_CORE_BUILD_DLL")
endif()

add_library(${lib} SHARED ${source_files})
set_target_properties(${lib} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(${lib}_LIBRARY_TYPE SHARED)

if(BORNAGAIN_PYTHON)
    add_dependencies(${lib} ${lib}_python)
endif()

# exposing library name and list of include directories outside
set(${lib}_LIBRARY ${lib} PARENT_SCOPE)

# --- external dependencies ---

target_include_directories(${lib}
    PUBLIC ${RootMinimizers_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
target_link_libraries(${lib} ${RootMinimizers_LIBRARY} ${Boost_LIBRARIES})


if(BORNAGAIN_PYTHON)
    target_compile_definitions(${lib} PUBLIC -DBORNAGAIN_PYTHON)
    target_include_directories(${lib} PUBLIC ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})
    target_link_libraries(${lib} ${Python3_LIBRARIES})
endif()

if(APPLE AND BORNAGAIN_APPLE_BUNDLE)
    set(link_flags "-Wl,-rpath,@loader_path/../../Frameworks")
    set_target_properties(${lib} PROPERTIES LINK_FLAGS ${link_flags})
endif()

# --- installation ---

install(TARGETS ${lib} DESTINATION ${destination_lib} COMPONENT Libraries)
install(FILES ${CMAKE_BINARY_DIR}/lib/lib${lib}.py
    DESTINATION ${destination_lib} COMPONENT Libraries) # required by swig

foreach(file ${include_files})
    get_filename_component(dir ${file} DIRECTORY)
    install(FILES ${file} DESTINATION ${destination_include}/${name}/${dir})
endforeach()

if(WIN32)
    # python in windows required .pyd extension for the library name
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
        add_custom_command(
            TARGET ${lib}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_BINARY_DIR}/bin/${libprefix}${lib}${libsuffix}
            ${CMAKE_BINARY_DIR}/lib/${libprefix}${lib}${libsuffix}
            )
    endif()
endif()
