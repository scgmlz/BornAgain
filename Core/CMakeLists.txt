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
    string(APPEND CMAKE_CXX_FLAGS " -DCERF_AS_CPP=ON")
endif()

# --- make the library ---

MakeLib(${name} ${lib} ${CMAKE_CURRENT_BINARY_DIR}/Wrap)

set(${lib}_LIBRARY ${lib} PARENT_SCOPE)

# --- external dependencies ---

target_link_libraries(${lib}
    ${BornAgainParam_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT})

if(BORNAGAIN_TIFF_SUPPORT)
    target_compile_definitions(${lib} PUBLIC -DBORNAGAIN_TIFF_SUPPORT)
    target_include_directories(${lib} PUBLIC ${TIFF_INCLUDE_DIR})
    target_link_libraries(${lib} ${TIFF_LIBRARIES})
endif()

target_include_directories(${lib}
    PUBLIC ${CMAKE_SOURCE_DIR}
    ${tspectrum_INCLUDE_DIR}
    ${Cerf_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/ThirdParty/Core/cerf_wrapper # TEMPORARY
    )
target_link_libraries(${lib}
    ${tspectrum_LIBRARY} ${Cerf_LIBRARIES})

if(BORNAGAIN_MPI)
    add_definitions(-DBORNAGAIN_MPI)
    include_directories(${MPI_INCLUDE_PATH})
    target_link_libraries(${lib} ${MPI_LIBRARIES})
endif()
