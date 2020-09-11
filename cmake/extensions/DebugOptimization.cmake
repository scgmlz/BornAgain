# DebugOptimization.cmake
#
# description: add debug optimization (gcc only)
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
# copyright: 2016 scientific computing group, Forshungszentrum Juelich GmbH
#
# license: see LICENSE
#

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Og")
else()
  message(WARNING "C compiler is not GNU; debug optimization has no effect")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og")
else()
  message(WARNING "C compiler is not GNU; debug optimization has no effect")
endif()

