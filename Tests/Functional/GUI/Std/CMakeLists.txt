include(GoogleTest) # provides gtest_discover_tests

set(test TestGuiStd)

file(GLOB source_files "*.cpp" "../../Std/Run.cpp")

add_executable(${test} ${source_files} ${CMAKE_SOURCE_DIR}/Tests/GTestWrapper/TestAll.cpp)
target_include_directories(${test} PUBLIC
    ${BornAgainGUI_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/ThirdParty/common/gtest/gtest-1.8.0/include)
target_link_libraries(${test} BornAgainGUI gtest)

gtest_discover_tests(${test} DISCOVERY_TIMEOUT 300 TEST_PREFIX Gui.)
