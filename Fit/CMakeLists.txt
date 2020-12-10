############################################################################
# CMakeLists.txt file for building libBornAgainFit
############################################################################

set(name Fit)
set(lib BornAgain${name})

# --- source and include files ---

file(GLOB source_files */*.cpp)
file(GLOB include_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */*.h)

# --- make the library ---

MakeLib(${name} ${lib} ${CMAKE_CURRENT_BINARY_DIR}/Wrap)

set(${lib}_LIBRARY ${lib} PARENT_SCOPE)

# --- external dependencies ---

target_include_directories(${lib}
    PUBLIC ${RootMinimizers_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
target_link_libraries(${lib} ${RootMinimizers_LIBRARY} ${Boost_LIBRARIES})
