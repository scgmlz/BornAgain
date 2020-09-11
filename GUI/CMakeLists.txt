############################################################################
# CMakeLists.txt file for building BornAgain/GUI libraries and executable
############################################################################

message(STATUS "Configuring BornAgain GUI")

set(CMAKE_AUTOMOC ON)

add_subdirectory(ba3d)
add_subdirectory(coregui)
add_subdirectory(main)

set(BornAgainGUI_INCLUDE_DIRS ${BornAgainGUI_INCLUDE_DIRS} PARENT_SCOPE)
set(BornAgainGUI_LIBRARY ${BornAgainGUI_LIBRARY} PARENT_SCOPE)

set(ba3d_INCLUDE_DIRS ${ba3d_INCLUDE_DIRS} PARENT_SCOPE)
set(ba3d_LIBRARY ${ba3d_LIBRARY} PARENT_SCOPE)
