include(GoogleTest) # provides gtest_discover_tests

set(test UnitTestNumeric)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGTEST_LINKED_AS_SHARED_LIBRARY=1")
endif()

include_directories(${CMAKE_SOURCE_DIR}/Tests/UnitTests/utilities)

file(GLOB source_files "*.cpp" ${CMAKE_SOURCE_DIR}/Tests/GTestWrapper/TestAll.cpp)

add_executable(${test} ${source_files})
target_link_libraries(${test} ${BornAgainCore_LIBRARY} gtest)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${test} PUBLIC "-Wno-deprecated-copy")
endif()

gtest_discover_tests(${test} DISCOVERY_TIMEOUT 300 TEST_PREFIX "Numeric.")
