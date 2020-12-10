#  BornAgain: simulate and fit scattering at grazing incidence
#
#  @file      Examples/cpp/modules/FindBornAgain.cmake
#  @brief     Finds BornAgain installation
#
#  Usage:     find_package(BornAgain REQUIRED)
#
#  Outcome:   defines
#             - BORNAGAIN_INCLUDE_DIR  PATH to the include directory
#             - BORNAGAIN_LIBRARIES    BornAgain libraries
#
#  @homepage  http://www.bornagainproject.org
#  @license   GNU General Public License v3 or higher (see COPYING)
#  @copyright Forschungszentrum Jülich GmbH 2016
#  @authors   Scientific Computing Group at MLZ Garching
#  @authors   J. Burle, C. Durniak, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke


set(BORNAGAINSYS $ENV{BORNAGAINSYS})
set(CoreComponents "Base;Param;Sample;Device;Core")

if(BORNAGAINSYS)
    set(BORNAGAIN_LIBRARY_DIR ${BORNAGAINSYS}/lib/BornAgain-1.18)
    set(BORNAGAIN_INCLUDE_DIR ${BORNAGAINSYS}/include/BornAgain-1.18)
endif()

foreach(lib ${CoreComponents})
    message(STATUS ${lib})
    find_library (BORNAGAIN_${lib}  _libBornAgain${lib}.so 
    PATHS ${BORNAGAIN_LIBRARY_DIR}
    HINTS ${BORNAGAIN_LIBRARY_DIR})
    list(APPEND BORNAGAIN_LIBRARIES ${BORNAGAIN_${lib}})
endforeach()

find_path(BORNAGAIN_INCLUDE_DIR BAVersion.h
    PATHS /usr/include /usr/local/include /opt/local/include ${BORNAGAIN_INCLUDE_DIR}
    PATH_SUFFIXES BornAgain
    HINTS ${BORNAGAIN_INCLUDE_DIR}
)

# 32-bits systems require special Eigen options
execute_process(COMMAND uname -m OUTPUT_VARIABLE SYSCTL_OUTPUT)
if(NOT ${SYSCTL_OUTPUT} MATCHES x86_64)
    add_definitions(-DEIGEN_DONT_ALIGN_STATICALLY=1)
endif()

message(STATUS "BORNAGAIN_LIBRARIES   ${BORNAGAIN_LIBRARIES}")
message(STATUS "BORNAGAIN_INCLUDE_DIR ${BORNAGAIN_INCLUDE_DIR}")
mark_as_advanced(BORNAGAIN_LIBRARIES BORNAGAIN_INCLUDE_DIR)

if(NOT BORNAGAIN_LIBRARIES OR NOT BORNAGAIN_INCLUDE_DIR)
   if(BornAgain_FIND_REQUIRED)
       message( FATAL_ERROR "FindBornAgain: can't find BornAgain header or library" )
   endif()
endif()
