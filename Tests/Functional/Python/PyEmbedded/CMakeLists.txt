include(GoogleTest) # provides gtest_discover_tests

set(test TestPyEmbedded)

file(GLOB source_files "*.cpp")

add_executable(${test} ${source_files} ${CMAKE_SOURCE_DIR}/Tests/GTestWrapper/TestAll.cpp)
target_include_directories(${test}
    PUBLIC
    ${CMAKE_SOURCE_DIR}/ThirdParty/common/gtest/gtest-1.8.0/include
    ${Python3_INCLUDE_DIRS}
    ${Python3_NumPy_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/auto/Wrap
)

target_link_libraries(${test} BornAgainCore gtest)

gtest_discover_tests(${test})
