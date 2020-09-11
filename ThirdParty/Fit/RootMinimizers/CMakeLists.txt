set(library_name RootMinimizers)

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

add_definitions(-DWARNINGMSG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMATH_NO_PLUGIN_MANAGER -DHAS_MINUIT2 -DR__HAS_MATHMORE")
if(NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4244 /wd4267")
endif()

add_library(${library_name} STATIC ${source_files})
# For the time being, it has to be STATIC
# because we don't have a DLL for the GSL library yet.
#   (at least not up to date and from reliable source
#    TODO: try https://www.nuget.org/packages/gsl-msvc14-x64)
# The ROOT code in directory mathcore depends on GSL.

target_include_directories(${library_name}
    PUBLIC ${include_dirs} ${GSL_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
target_link_libraries(${library_name} ${GSL_LIBRARIES} ${Boost_LIBRARIES})

set(${library_name}_INCLUDE_DIRS ${include_dirs} CACHE INTERNAL "")
set(${library_name}_LIBRARY ${library_name} CACHE INTERNAL "")
