include(GoogleTest) # provides gtest_discover_tests

set(test UnitTestCore)

file(GLOB source_files "*/*.cpp" ${CMAKE_SOURCE_DIR}/Tests/GTestWrapper/TestAll.cpp)

add_executable(${test} ${source_files})
target_include_directories(${test} PUBLIC ${CMAKE_SOURCE_DIR}/Tests/UnitTests/utilities)
target_link_libraries(${test} ${BornAgainCore_LIBRARY} gtest)
if(BORNAGAIN_GUI)
    target_include_directories(${test} PUBLIC ${Qt5Core_INCLUDE_DIRS})
    target_link_libraries(${test} ${Qt5Core_LIBRARIES})
endif()

gtest_discover_tests(${test} DISCOVERY_TIMEOUT 300 TEST_PREFIX Core.Unit.)
