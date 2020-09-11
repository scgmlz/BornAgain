############################################################################
# Tests/Functional/PyCore/persistence/CMakeLists.txt
############################################################################

set(OUTPUT_DIR ${TEST_OUTPUT_DIR}/Functional/Python/PyPersist)
file(MAKE_DIRECTORY ${OUTPUT_DIR})

set(PYPERSIST_REFERENCE_DIR ${TEST_REFERENCE_DIR}/Python)

# Python persistence test
function(test_example example tolerance)
    set(script_path ${PY_EXAMPLES_DIR}/${example}.py)
    get_filename_component(EXAMPLE_NAME ${script_path} NAME_WE)
    get_filename_component(EXAMPLE_DIR ${script_path} DIRECTORY)

    set(test_name PyPersistence/${EXAMPLE_NAME})

    set(PYPERSIST_TOLERANCE ${tolerance})

    # modified example to run as a test
    set(example_mod ${OUTPUT_DIR}/${EXAMPLE_NAME}_mod.py)
    configure_file(example_template.py ${example_mod} @ONLY)

    add_test(${test_name} ${Python3_EXECUTABLE} "-B" "${example_mod}")
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
test_example("simulation/ex03_InterferenceFunctions/Interference1DLattice" 1.5)
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
test_example("simulation/ex05_BeamAndDetector/ConstantBackground" 2e-10)

test_example("simulation/ex06_Reflectometry/BasicSpecularSimulation" 2e-10)
test_example("simulation/ex06_Reflectometry/BeamAngularDivergence" 2e-10)
test_example("simulation/ex06_Reflectometry/BeamFullDivergence" 2e-10)
test_example("simulation/ex06_Reflectometry/TimeOfFlightReflectometry" 2e-10)
test_example("simulation/ex06_Reflectometry/TOFRWithResolution" 2e-10)

test_example("simulation/ex07_Miscellaneous/CylindersInAverageLayer" 2e-10)
test_example("simulation/ex07_Miscellaneous/DepthProbe" 2e-10)
test_example("simulation/ex07_Miscellaneous/HalfSpheresInAverageTopLayer" 2e-10)
test_example("simulation/ex07_Miscellaneous/MagneticSpheres" 2e-10)

test_example("simulation/ex07_Miscellaneous/SimulationParameters" 2e-10)
