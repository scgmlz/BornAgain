set(library_name BornAgainFitTestMachinery)

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBA_CORE_BUILD_DLL")
endif()

# making library
add_library(
    ${library_name}
    SHARED
    ${source_files} ${include_files}
    )

set_target_properties(${library_name} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(${library_name}_LIBRARY_TYPE SHARED)

target_include_directories(${library_name} PUBLIC ${BornAgainFit_INCLUDE_DIRS})
target_link_libraries(${library_name} PUBLIC ${BornAgainFit_LIBRARY})

# exposing library name and include directories
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)


if(APPLE AND BORNAGAIN_APPLE_BUNDLE)
    set(link_flags "-Wl,-rpath,@loader_path/../../Frameworks")
    set_target_properties(${library_name} PROPERTIES LINK_FLAGS ${link_flags})
endif()
