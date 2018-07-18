############################################################################
# CMakeLists.txt file for building BornAgain/GUI libraries and executable
############################################################################
if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()

message(STATUS "Configuring BornAgain GUI")

if(BORNAGAIN_OPENGL)
    message(STATUS "Configuring BornAgain OpenGL")
    add_definitions(-DBORNAGAIN_OPENGL)
    add_subdirectory(ba3d)
endif()

add_subdirectory(coregui)

add_subdirectory(main)

set(BornAgainGUI_INCLUDE_DIRS ${BornAgainGUI_INCLUDE_DIRS} PARENT_SCOPE)
set(BornAgainGUI_LIBRARY ${BornAgainGUI_LIBRARY} PARENT_SCOPE)

set(ba3d_INCLUDE_DIRS ${ba3d_INCLUDE_DIRS} PARENT_SCOPE)
set(ba3d_LIBRARY ${ba3d_LIBRARY} PARENT_SCOPE)
