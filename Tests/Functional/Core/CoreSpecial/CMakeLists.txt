include(GoogleTest) # provides gtest_discover_tests

set(test TestCoreSpecial)

set(source_files
    BatchSimulation.cpp
    FourierTransformationTest.cpp
    CoreIOPathTest.cpp
    )

add_executable(${test} ${source_files} ${CMAKE_SOURCE_DIR}/Tests/GTestWrapper/TestAll.cpp)
target_include_directories(${test}
    PUBLIC
    ${CMAKE_SOURCE_DIR}/Tests/UnitTests/utilities
    ${CMAKE_SOURCE_DIR}/ThirdParty/common/gtest/gtest-1.8.0/include)
target_link_libraries(${test} ${BornAgainCore_LIBRARY} gtest)

gtest_discover_tests(${test} DISCOVERY_TIMEOUT 300 TEST_PREFIX "Core.Special.")
