#---------------------------------------------------------------------------------------------------
#  CheckCompiler.cmake
#---------------------------------------------------------------------------------------------------

#--- Set a default build type for single-configuration CMake generators if no build type is set ---

if(NOT CMAKE_BUILD_TYPE)
    #  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

#--- Need to locate thead libraries and options to set properly some compilation flags ---

find_package(Threads)

#--- Print the final compiler flags ---

message(STATUS "BornAgain Platform: ${BORNAGAIN_PLATFORM}")
message(STATUS "BornAgain Architecture: ${BORNAGAIN_ARCHITECTURE}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

set(all_cxx_flags ${CMAKE_CXX_FLAGS})
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    string(APPEND all_cxx_flags " ${CMAKE_CXX_FLAGS_RELEASE}")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    string(APPEND all_cxx_flags " ${CMAKE_CXX_FLAGS_DEBUG}")
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    string(APPEND all_cxx_flags " ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
endif()

message(STATUS "Compiler Flags: ${all_cxx_flags}")
message(STATUS "Shared linker Flags: ${CMAKE_SHARED_LINKER_FLAGS}")
message(STATUS "Exe linker Flags: ${CMAKE_EXE_LINKER_FLAGS}")
