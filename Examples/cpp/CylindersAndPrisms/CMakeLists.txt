#  BornAgain: simulate and fit scattering at grazing incidence
#
#  @file      Examples/cpp/CylindersAndPrisms/CMakeLists.txt
#  @brief     Demonstrates how to compile a main program that uses the BornAgain C++ API.
#
#  @homepage  http://www.bornagainproject.org
#  @license   GNU General Public License v3 or higher (see COPYING)
#  @copyright Forschungszentrum Jülich GmbH 2016
#  @authors   Scientific Computing Group at MLZ Garching
#  @authors   J. Burle, C. Durniak, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(CylindersAndPrisms)

add_executable(CylindersAndPrisms CylindersAndPrisms.cpp)

# path to the cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/../modules)

# find libraries
find_package(BornAgain REQUIRED)
find_package(Eigen3 REQUIRED)

include_as_system_directory("${EIGEN3_INCLUDE_DIRS}")
include_directories(${BORNAGAIN_INCLUDE_DIR})

target_link_libraries(CylindersAndPrisms ${BORNAGAIN_LIBRARIES})
