include(GoogleTest)

set(test UnitTestGUI)

file(GLOB source_files "*.cpp")

find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/Tests/UnitTests/utilities)

set(CMAKE_AUTOMOC ON)
add_executable(${test} ${source_files})
target_link_libraries(${test} ${BornAgainGUI_LIBRARY} gtest)
target_link_libraries(${test} Qt5::Core Qt5::Test)

gtest_discover_tests(${test} DISCOVERY_TIMEOUT 300 TEST_PREFIX GUI.Unit.)
