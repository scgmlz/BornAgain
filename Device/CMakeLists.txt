############################################################################
# CMakeLists.txt file for building libBornAgainDevice
############################################################################

set(name Device)
set(lib BornAgain${name})

# --- source and include files ---

file(GLOB source_files */*.cpp)
file(GLOB include_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */*.h)

# --- make the library ---

MakeLib(${name} ${lib} ${CMAKE_CURRENT_BINARY_DIR}/Wrap)

set(${lib}_LIBRARY ${lib} PARENT_SCOPE)

# --- external dependencies ---

target_link_libraries(${lib}
    ${BornAgainSample_LIBRARY} # TODO get rid of this dependence
    ${BornAgainParam_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(${lib}
    PUBLIC ${CMAKE_SOURCE_DIR}
    )

target_include_directories(${lib}
    PUBLIC ${CMAKE_SOURCE_DIR}
    ${tspectrum_INCLUDE_DIR}
    )
target_link_libraries(${lib}
    ${tspectrum_LIBRARY}
    )

if(BORNAGAIN_TIFF_SUPPORT)
    target_compile_definitions(${lib} PUBLIC -DBORNAGAIN_TIFF_SUPPORT)
    target_include_directories(${lib} PUBLIC ${TIFF_INCLUDE_DIR})
    target_link_libraries(${lib} ${TIFF_LIBRARIES})
endif()
