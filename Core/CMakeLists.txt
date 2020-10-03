############################################################################
# CMakeLists.txt file for building libBornAgainCore
############################################################################

set(name Core)
set(lib BornAgain${name})

# --- source and include files ---

file(GLOB source_files */*.cpp)
file(GLOB include_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */*.h)

if((NOT Cerf_IS_CPP) AND (NOT WIN32)) # TEMPORARY
    list(APPEND source_files ${CMAKE_SOURCE_DIR}/ThirdParty/Core/cerf_wrapper/cerf_ptr.c)
endif()
if(${Cerf_IS_CPP})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCERF_AS_CPP=ON")
endif()


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


if(BORNAGAIN_PYTHON)
    if(CONFIGURE_BINDINGS)
        add_custom_command(
            OUTPUT ${AUTO_DIR}/swig_runtime.h
            COMMAND ${SWIG_EXECUTABLE} -c++;-python;-external-runtime;${AUTO_DIR}/swig_runtime.h
            DEPENDS ${swig_dependencies} ${include_files}
            )
    endif()
    add_custom_target(${lib}_runtime DEPENDS ${AUTO_DIR}/swig_runtime.h)
    add_dependencies(${lib} ${lib}_runtime)

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



# --- external dependencies ---

target_link_libraries(${lib} ${BornAgainFit_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})

if(BORNAGAIN_TIFF_SUPPORT)
    target_compile_definitions(${lib} PUBLIC -DBORNAGAIN_TIFF_SUPPORT)
    target_include_directories(${lib} PUBLIC ${TIFF_INCLUDE_DIR})
    target_link_libraries(${lib} ${TIFF_LIBRARIES})
endif()

target_include_directories(${lib}
    PUBLIC ${CMAKE_SOURCE_DIR} ${Boost_INCLUDE_DIRS} ${FFTW3_INCLUDE_DIR} ${GSL_INCLUDE_DIR}
    ${tspectrum_INCLUDE_DIR}
    ${Cerf_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/ThirdParty/Core/cerf_wrapper # TEMPORARY
    SYSTEM PUBLIC ${EIGEN3_INCLUDE_DIRS}
    )
if(BORNAGAIN_GUI)
    target_include_directories(${lib} PUBLIC ${Qt5Core_INCLUDE_DIRS})
    target_link_libraries(${lib} ${Qt5Core_LIBRARIES})
endif()

target_link_libraries(${lib} ${Boost_LIBRARIES} ${FFTW3_LIBRARIES} ${GSL_LIBRARIES}
    ${tspectrum_LIBRARY} ${Cerf_LIBRARIES})

if(BORNAGAIN_MPI)
    add_definitions(-DBORNAGAIN_MPI)
    include_directories(${MPI_INCLUDE_PATH})
    target_link_libraries(${lib} ${MPI_LIBRARIES})
endif()

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

    # system libraries
    foreach(Boost_lib ${Boost_LIBRARIES})
        get_filename_component(UTF_BASE_NAME ${Boost_lib} NAME_WE)
        get_filename_component(UTF_PATH ${Boost_lib} PATH)
        message(STATUS "Boost dll: ${UTF_PATH}/${UTF_BASE_NAME}.dll")
        install(FILES ${UTF_PATH}/${UTF_BASE_NAME}.dll
            DESTINATION ${destination_lib} COMPONENT Libraries)
    endforeach()

    set(win_python_lib
        "${Python3_LIBRARY_DIRS}/python${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR}.lib")
    get_filename_component(UTF_BASE_NAME ${win_python_lib} NAME_WE)
    get_filename_component(UTF_PATH ${Python3_EXECUTABLE} PATH)
    message(STATUS "Python dll: ${UTF_PATH}/${UTF_BASE_NAME}.dll")
    install(FILES ${UTF_PATH}/${UTF_BASE_NAME}.dll
        DESTINATION ${destination_lib} COMPONENT Libraries)

    set(Cerf_LIB ${Cerf_LIBRARIES}) # we take for granted that there is only one cerf.lib
    get_filename_component(DIR ${Cerf_LIB} DIRECTORY)
    get_filename_component(cerf ${Cerf_LIB} NAME_WE)

    set(DLL_MSG "")
    foreach(LIB IN ITEMS ${cerf} libgcc_s_seh-1 libstdc++-6 libwinpthread-1)
        set(DLL "${DIR}/${LIB}.dll")
        if (NOT EXISTS ${DLL})
            message(FATAL_ERROR "Dynamic load library ${DLL} (needed for cerf) does not exist")
        endif()
        install(FILES ${DLL} DESTINATION ${destination_lib} COMPONENT Libraries)
        string(APPEND DLL_MSG " ${DLL}")
    endforeach()
    message(STATUS "Cerf dlls: ${DLL_MSG}")

    set(DLL_MSG "")
    foreach(LIB IN LISTS FFTW3_LIBRARIES TIFF_LIBRARIES)
        string(REPLACE ".lib" ".dll" DLL "${LIB}")
        if (NOT EXISTS ${DLL})
            message(FATAL_ERROR "Dynamic load library ${DLL} (derived from ${LIB}) does not exist")
        endif()
        install(FILES ${DLL} DESTINATION ${destination_lib} COMPONENT Libraries)
        string(APPEND DLL_MSG " ${DLL}")
    endforeach()
    message(STATUS "Other dlls: ${DLL_MSG}")

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
