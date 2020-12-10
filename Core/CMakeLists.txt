############################################################################
# CMakeLists.txt file for building libBornAgainCore
############################################################################

set(name Core)
set(lib BornAgain${name})

# --- source and include files ---

file(GLOB source_files */*.cpp)
file(GLOB include_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */*.h)

# --- make the library ---

MakeLib(${name} ${lib} ${CMAKE_CURRENT_BINARY_DIR}/Wrap)

set(${lib}_LIBRARY ${lib} PARENT_SCOPE)

# --- external dependencies ---

target_link_libraries(${lib}
    ${BornAgainSample_LIBRARY}
    ${BornAgainDevice_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(${lib}
    PUBLIC ${CMAKE_SOURCE_DIR}
    ${tspectrum_INCLUDE_DIR}
    ${Cerf_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/ThirdParty/Core/ # TEMPORARY
    )
target_link_libraries(${lib}
    ${tspectrum_LIBRARY} ${Cerf_LIBRARIES})

if(BORNAGAIN_MPI)
    add_definitions(-DBORNAGAIN_MPI)
    include_directories(${MPI_INCLUDE_PATH})
    target_link_libraries(${lib} ${MPI_LIBRARIES})
endif()
