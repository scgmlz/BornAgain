############################################################################
# Tests/Functional/PyCore/persistence/CMakeLists.txt
############################################################################

set(PYPERSIST_REF_DIR ${REFERENCE_DIR}/PyPersist)
set(PYPERSIST_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
file(MAKE_DIRECTORY ${PYPERSIST_OUT_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPYPERSIST_OUT_DIR=\\\"${PYPERSIST_OUT_DIR}\\\"")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPYPERSIST_REF_DIR=\\\"${PYPERSIST_REF_DIR}\\\"")

# for some reason these flags aren't propagated here by SetUpWindows.cmake
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc ")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHsc ")
    add_definitions(-DYAML_CPP_DLL)
endif()

include_directories(
    ${BornAgainCore_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${YAMLCPP_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/Core/Simulation
    ${CMAKE_CURRENT_SOURCE_DIR}/../../TestMachinery
)

add_executable(PyPersistenceTest main.cpp PyPersistenceTest.h PyPersistenceTest.cpp)
target_link_libraries(PyPersistenceTest BornAgainCore BornAgainTestMachinery)

# Python persistence test
function(test_example example tolerance)
    set(script_path ${PY_EXAMPLES_DIR}/${example}.py)
    get_filename_component(EXAMPLE_NAME ${script_path} NAME_WE)
    get_filename_component(EXAMPLE_DIR ${script_path} DIRECTORY)

    set(OUTPUT_DIR ${PYPERSIST_OUT_DIR})

    # modified example to run as a test
    set(example_mod ${CMAKE_CURRENT_BINARY_DIR}/${EXAMPLE_NAME}_mod.py)
    configure_file(example_template.py ${example_mod} @ONLY)

    add_test(PyPersistence/${EXAMPLE_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PyPersistenceTest
            ${example_mod} ${EXAMPLE_NAME} ${tolerance})
endfunction()

test_example("simulation/ex01_BasicParticles/CylindersAndPrisms" 2e-10)
test_example("simulation/ex01_BasicParticles/CylindersInBA" 2e-10)
test_example("simulation/ex01_BasicParticles/CylindersInDWBA" 2e-10)
test_example("simulation/ex01_BasicParticles/CylindersWithSizeDistribution" 2e-10)
test_example("simulation/ex01_BasicParticles/RotatedPyramids" 2e-10)
test_example("simulation/ex01_BasicParticles/TwoTypesOfCylindersWithSizeDistribution" 2e-10)
test_example("simulation/ex02_LayeredStructures/BuriedParticles" 2e-10)
test_example("simulation/ex02_LayeredStructures/CorrelatedRoughness" 2e-10)
test_example("simulation/ex03_InterferenceFunctions/ApproximationDA" 2e-10)
test_example("simulation/ex03_InterferenceFunctions/ApproximationLMA" 2e-10)
test_example("simulation/ex03_InterferenceFunctions/ApproximationSSCA" 2e-10)
test_example("simulation/ex03_InterferenceFunctions/CosineRipplesAtRectLattice" 2e-10)
test_example("simulation/ex03_InterferenceFunctions/Interference1DLattice" 2e-10)
test_example("simulation/ex03_InterferenceFunctions/Interference1DRadialParaCrystal" 2e-10)
test_example("simulation/ex03_InterferenceFunctions/Interference2DCenteredSquareLattice" 2e-10)
test_example("simulation/ex03_InterferenceFunctions/Interference2DParaCrystal" 2e-10)
test_example("simulation/ex03_InterferenceFunctions/Interference2DRotatedSquareLattice" 2e-10)
test_example("simulation/ex03_InterferenceFunctions/Interference2DSquareLattice" 2e-10)
test_example("simulation/ex03_InterferenceFunctions/Interference2DLatticeSumOfRotated" 2e-10)
test_example("simulation/ex03_InterferenceFunctions/RectangularGrating" 0.5)
test_example("simulation/ex03_InterferenceFunctions/SpheresAtHexLattice" 2e-10)
test_example("simulation/ex03_InterferenceFunctions/TriangularRipple" 2e-10)

test_example("simulation/ex04_ComplexShapes/CoreShellNanoparticles" 2e-10)
test_example("simulation/ex04_ComplexShapes/CustomFormFactor" 2e-10)
test_example("simulation/ex04_ComplexShapes/HexagonalLatticesWithBasis" 2e-10)

test_example("simulation/ex05_BeamAndDetector/BeamDivergence" 2e-10)
test_example("simulation/ex05_BeamAndDetector/DetectorResolutionFunction" 2e-10)
test_example("simulation/ex05_BeamAndDetector/OffSpecularSimulation" 2e-10)
test_example("simulation/ex05_BeamAndDetector/SpecularSimulation" 2e-10)
test_example("simulation/ex05_BeamAndDetector/ConstantBackground" 2e-10)

test_example("simulation/ex06_Miscellaneous/CylindersInAverageLayer" 2e-10)
test_example("simulation/ex06_Miscellaneous/HalfSpheresInAverageTopLayer" 2e-10)
test_example("simulation/ex06_Miscellaneous/MagneticSpheres" 2e-10)

test_example("fitting/ex01_SampleParametersIntro/SampleParametersIntro" 2e-10)
