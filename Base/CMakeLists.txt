############################################################################
# CMakeLists.txt file for building libBornAgainCore
############################################################################

set(name Base)
set(lib BornAgain${name})

# --- source and include files ---

file(GLOB source_files */*.cpp)
file(GLOB include_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */*.h)

# --- make the library ---

MakeLib(${name} ${lib} ${CMAKE_CURRENT_BINARY_DIR}/Wrap)

set(${lib}_LIBRARY ${lib} PARENT_SCOPE)

# --- external dependencies ---

# target_link_libraries(${lib} ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(${lib}
    PUBLIC ${CMAKE_SOURCE_DIR} ${GSL_INCLUDE_DIR} ${FFTW3_INCLUDE_DIR} ${Boost_INCLUDE_DIRS}
    SYSTEM PUBLIC ${EIGEN3_INCLUDE_DIRS}
    )
target_link_libraries(${lib} ${GSL_LIBRARIES} ${FFTW3_LIBRARIES} ${Boost_LIBRARIES})

if(BORNAGAIN_GUI)
    target_include_directories(${lib} PUBLIC ${Qt5Core_INCLUDE_DIRS})
    target_link_libraries(${lib} ${Qt5Core_LIBRARIES})
endif()

if(BORNAGAIN_MPI)
    add_definitions(-DBORNAGAIN_MPI)
    include_directories(${MPI_INCLUDE_PATH})
    target_link_libraries(${lib} ${MPI_LIBRARIES})
endif()
