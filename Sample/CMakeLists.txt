############################################################################
# CMakeLists.txt file for building libBornAgainSample
############################################################################

set(name Sample)
set(lib BornAgain${name})

# --- source and include files ---

file(GLOB source_files */*.cpp)
file(GLOB include_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */*.h)

# --- make the library ---

MakeLib(${name} ${lib} ${CMAKE_CURRENT_BINARY_DIR}/Wrap)

set(${lib}_LIBRARY ${lib} PARENT_SCOPE)

# --- external dependencies ---

target_link_libraries(${lib}
    ${BornAgainParam_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(${lib}
    PUBLIC ${CMAKE_SOURCE_DIR}
    )
