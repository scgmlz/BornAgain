project(ba3d)
cmake_minimum_required (VERSION 3.1 FATAL_ERROR)
if(POLICY CMP0071)
    cmake_policy(SET CMP0071 NEW)
endif()

set(CMAKE_CXX_STANDARD 14)
if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets OpenGL)

if(${Qt5Core_VERSION} VERSION_LESS "5.5.1")
    message (FATAL_ERROR "Qt 5.5.1+ is required, have ${Qt5Core_VERSION_STRING}")
endif()

set(include_dirs ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${include_dirs})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory (ba3d)
add_subdirectory (showcase)
add_subdirectory (demo)

set(library_name ba3d)
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)
