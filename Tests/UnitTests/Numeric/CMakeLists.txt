include(GoogleTest)

set(test UnitTestNumeric)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGTEST_LINKED_AS_SHARED_LIBRARY=1")
endif()

include_directories(${CMAKE_SOURCE_DIR}/Tests/UnitTests/utilities)

file(GLOB source_files "*.cpp" "../utilities/TestAll.cpp")
file(GLOB include_files "*.h")

add_executable(${test} ${source_files} ${include_files})
target_link_libraries(${test} ${BornAgainCore_LIBRARY} gtest)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${test} PUBLIC "-Wno-deprecated-copy")
endif()

gtest_discover_tests(${test} TEST_PREFIX Core:Unit:Numeric:)
