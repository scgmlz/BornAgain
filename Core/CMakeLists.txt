############################################################################
# CMakeLists.txt file for building libBornAgainCore
############################################################################

set(name Core)
set(lib BornAgain${name})

file(GLOB source_files */*.cpp)
file(GLOB include_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */*.h)

if((NOT Cerf_IS_CPP) AND (NOT WIN32)) # TEMPORARY
    list(APPEND source_files ${CMAKE_SOURCE_DIR}/ThirdParty/Core/cerf_wrapper/cerf_ptr.c)
endif()
if(${Cerf_IS_CPP})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCERF_AS_CPP=ON")
endif()

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

target_link_libraries(${lib} ${BornAgainFit_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})

if(BORNAGAIN_TIFF_SUPPORT)
    target_compile_definitions(${lib} PUBLIC -DBORNAGAIN_TIFF_SUPPORT)
    target_include_directories(${lib} PUBLIC ${TIFF_INCLUDE_DIR})
    target_link_libraries(${lib} ${TIFF_LIBRARIES})
endif()

target_include_directories(${lib}
    PUBLIC ${CMAKE_SOURCE_DIR} ${Boost_INCLUDE_DIRS} ${FFTW3_INCLUDE_DIR} ${GSL_INCLUDE_DIR}
    ${tspectrum_INCLUDE_DIR}
    ${Cerf_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/ThirdParty/Core/cerf_wrapper # TEMPORARY
    SYSTEM PUBLIC ${EIGEN3_INCLUDE_DIRS}
    )
if(BORNAGAIN_GUI)
    target_include_directories(${lib} PUBLIC ${Qt5Core_INCLUDE_DIRS}) # needed by Assert.h
    target_link_libraries(${lib} ${Qt5Core_LIBRARIES})
endif()

target_link_libraries(${lib} ${Boost_LIBRARIES} ${FFTW3_LIBRARIES} ${GSL_LIBRARIES}
    ${tspectrum_LIBRARY} ${Cerf_LIBRARIES})

if(BORNAGAIN_MPI)
    add_definitions(-DBORNAGAIN_MPI)
    target_include_directories(${lib} PUBLIC ${MPI_INCLUDE_PATH})
    target_link_libraries(${lib} ${MPI_LIBRARIES})
endif()
