set(test TestPyEmbedded)

set(test_cases
    SysPath
    ImportNumpy
    FunctionCall
    MethodCall
    CompiledFunction
    ObjectExtract
    EmbeddedMultiLayer
    ExportToPythonAndBack
    ModuleFunctionsList
)

include_directories(
    ${Python_INCLUDE_DIRS}
    ${Python_NumPy_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/auto/Wrap
)

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

add_executable(${test} ${include_files} ${source_files})
target_link_libraries(${test} BornAgainCore BornAgainTestMachinery)

foreach(test_case ${test_cases})
    add_test(${test}/${test_case} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test} ${test_case})
endforeach()

