############################################################################
# GUI unit tests
############################################################################

set(test UnitTestGUI)

if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()

if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)

include_directories(${ba3d_INCLUDE_DIRS} ${BornAgainGUI_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)
add_executable(${test} ${source_files} ${include_files})
target_link_libraries(${test} ${BornAgainGUI_LIBRARY} ${ba3d_LIBRARY} gtest)
target_link_libraries(${test} Qt5::Core Qt5::Test)

# add execution of TestCore just after compilation
add_custom_target(${test}_run ALL DEPENDS ${test} COMMAND ${test})
