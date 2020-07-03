############################################################################
# CMakeLists.txt file for building libBornAgainCore library
############################################################################

set(library_name BornAgainTestMachinery)

file(GLOB source_files "*.cpp")

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBA_CORE_BUILD_DLL")
endif()

add_library(${library_name} SHARED ${source_files})

set_target_properties(${library_name} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(${library_name}_LIBRARY_TYPE SHARED)

# exposing library name and list of include directories outside
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)

target_link_libraries(${library_name}
    ${BornAgainCore_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    )

if(APPLE AND BORNAGAIN_APPLE_BUNDLE)
    set(link_flags "-Wl,-rpath,@loader_path/../../Frameworks")
    set_target_properties(${library_name} PROPERTIES LINK_FLAGS ${link_flags})
endif()
