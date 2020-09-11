# CoverageFunction.cmake
#
# description: find coverage tools and provide function add_coverage_target
#
# usage: from build directory
#
#        cmake .. -DCMAKE_BUILD_TYPE=Debug
#        ctest   (or make check)
#        cmake --build . --config Debug --target coverage
#
# author: Jonathan Fisher
#         j.fisher@fz-juelich.de, jonathan.m.fisher@gmail.com
#
# copyright: 2016 Scientific Computing Group, Forschungszentrum Juelich GmbH
#
# license: see LICENSE

find_program(GCOV_COMMAND gcov)
find_program(LCOV_COMMAND lcov)
find_program(GENHTML_COMMAND genhtml)

if(GCOV_COMMAND)
    set(CMAKE_GCOV_FOUND TRUE)
else()
    message(ERROR "could not locate gcov executable, cannot add code coverage custom target!")
endif()

if(LCOV_COMMAND)
    set(CMAKE_LCOV_FOUND TRUE)
else()
    message(ERROR "could not locate lcov executable, cannot add code coverage custom target!")
endif()

if(GENHTML_COMMAND)
    set(CMAKE_GENHTML_FOUND TRUE)
else()
    message(ERROR "could not locate genhtml executable, cannot add code coverage custom target!")
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -coverage")
else()
    message(ERROR "C compiler is not GNU; don't know how to set code coverage flags!")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -coverage")
else()
    message(ERROR "CXX compiler is not GNU; don't know how to set code coverage flags!")
endif()

# function to add a coverage target
# it will scan the working directory for coverage info, ignoring the directories in ignore_directories
function(add_coverage_target targetname ignore_directories html_dir)

    if (NOT CMAKE_GCOV_FOUND)
        message(FATAL_ERROR "gcov not found! aborting")
    endif()

    if (NOT CMAKE_LCOV_FOUND)
        message(FATAL_ERROR "lcov not found! aborting")
    endif()

    if (NOT CMAKE_GENHTML_FOUND)
        message(FATAL_ERROR "genhtml not found! aborting")
    endif()

    set(lcov_output "${CMAKE_CURRENT_BINARY_DIR}/${targetname}.info")

    add_custom_target(${targetname}
        COMMAND ${LCOV_COMMAND} --directory ${CMAKE_CURRENT_BINARY_DIR} --capture --output-file ${lcov_output})

    add_custom_target(${targetname}_reset
        COMMAND ${LCOV_COMMAND} --directory ${CMAKE_CURRENT_BINARY_DIR} --zerocounters)

    foreach(dirname ${ignore_directories})
        message(STATUS "ignoring dirname = ${dirname} in code coverage")
        add_custom_command(TARGET ${targetname}
            COMMAND ${LCOV_COMMAND} --remove ${lcov_output} ${dirname} --output-file ${lcov_output}.clean
            COMMAND ${CMAKE_COMMAND} -E rename ${lcov_output}.clean ${lcov_output})
    endforeach()

    add_custom_command(TARGET ${targetname} POST_BUILD
        COMMAND ${GENHTML_COMMAND} ${lcov_output} --output-directory ${html_dir}
        COMMENT "open index.html in your webbrowser to see the code coverage report.")

endfunction()
