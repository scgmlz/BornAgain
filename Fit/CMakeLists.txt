############################################################################
# CMakeLists.txt file for building libBornAgainFit
############################################################################

set(name Fit)
set(lib BornAgain${name})

file(GLOB source_files */*.cpp)
file(GLOB include_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */*.h)

if(BORNAGAIN_PYTHON)
    list(APPEND source_files ${AUTO_DIR}/lib${lib}_wrap.cpp)
endif()

add_library(${lib} SHARED ${source_files})
set_target_properties(${lib} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(${lib}_LIBRARY_TYPE SHARED)
set(${lib}_LIBRARY ${lib} PARENT_SCOPE)

SwigLib(${name} ${lib})

if(APPLE AND BORNAGAIN_APPLE_BUNDLE)
    set_target_properties(${lib} PROPERTIES LINK_FLAGS "-Wl,-rpath,@loader_path/../../Frameworks")
endif()

install(TARGETS ${lib} DESTINATION ${destination_lib} COMPONENT Libraries)

foreach(file ${include_files})
    get_filename_component(dir ${file} DIRECTORY)
    install(FILES ${file} DESTINATION ${destination_include}/${name}/${dir})
endforeach()

# --- external dependencies ---

target_include_directories(${lib}
    PUBLIC ${RootMinimizers_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
target_link_libraries(${lib} ${RootMinimizers_LIBRARY} ${Boost_LIBRARIES})
