############################################################################
# CMakeLists.txt file for building libRootMinimizers package
############################################################################
set(library_name RootMinimizers)

# --- source and include files ---------
set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/base
    ${CMAKE_CURRENT_SOURCE_DIR}/mathcore
)

file(GLOB source_files
    "Minuit2/*.cxx"
    "mathcore/*.cxx"
    "mathcore/Math/*.cxx"
    "Fit/*.cxx"
    "TMVA/*.cxx"
    "base/*.cxx"
)

file(GLOB include_files
    "base/*.h"
    "Minuit2/*.h"
    "Math/*.h"
    "mathcore/Math/*.h"
    "Fit/*.h"
    "TMVA/*.h"
    "base/*.h"
)

# --- definitions ---------
add_definitions(-DWARNINGMSG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMATH_NO_PLUGIN_MANAGER -DHAS_MINUIT2 -DR__HAS_MATHMORE")
if(NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4244 /wd4267")
endif()

# --- making library ------------
add_library(${library_name} SHARED ${source_files} ${include_files})
set(${library_name}_INCLUDE_DIRS ${include_dirs} CACHE INTERNAL "")
set(${library_name}_LIBRARY ${library_name} CACHE INTERNAL "")

# --- external dependencies ---
target_include_directories(${library_name} PUBLIC ${GSL_INCLUDE_DIR})
target_link_libraries(${library_name} ${GSL_LIBRARIES})
target_include_directories(${library_name} PUBLIC ${include_dirs})
