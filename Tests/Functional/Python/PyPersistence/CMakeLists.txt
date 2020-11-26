############################################################################
# Tests/Functional/PyCore/persistence/CMakeLists.txt
############################################################################

set(OUTPUT_DIR ${TEST_OUTPUT_DIR_PY_PERSIST})
file(MAKE_DIRECTORY ${OUTPUT_DIR})

# Python persistence test
function(test_example example tolerance)
    set(script_path ${PY_EXAMPLES_DIR}/${example}.py)
    get_filename_component(EXAMPLE_NAME ${script_path} NAME_WE)
    get_filename_component(EXAMPLE_DIR ${script_path} DIRECTORY)

    set(test_name PyPersistence.${EXAMPLE_NAME})

    set(PYPERSIST_TOLERANCE ${tolerance})

    # modified example to run as a test
    set(example_mod ${OUTPUT_DIR}/${EXAMPLE_NAME}_mod.py)
    configure_file(PyPersistence.py.in ${example_mod} @ONLY)

    add_test(${test_name} ${Python3_EXECUTABLE} -B ${example_mod})
endfunction()

test_example(sim01_Particles/CylindersAndPrisms 2e-10)
test_example(sim01_Particles/CylindersInBA 2e-10)
test_example(sim01_Particles/CylindersInDWBA 2e-10)
test_example(sim01_Particles/CylindersWithSizeDistribution 2e-10)
test_example(sim01_Particles/RotatedPyramids 2e-10)
test_example(sim01_Particles/TwoTypesOfCylindersWithSizeDistribution 2e-10)

test_example(sim02_Complexes/CoreShellNanoparticles 2e-10)
test_example(sim02_Complexes/CustomFormFactor 2e-10)
test_example(sim02_Complexes/HexagonalLatticesWithBasis 2e-10)

test_example(sim03_Structures/ApproximationDA 2e-10)
test_example(sim03_Structures/ApproximationLMA 2e-10)
test_example(sim03_Structures/ApproximationSSCA 2e-10)
test_example(sim03_Structures/CosineRipplesAtRectLattice 2e-10)
test_example(sim03_Structures/Interference1DLattice 1.5)
test_example(sim03_Structures/Interference1DRadialParaCrystal 2e-10)
test_example(sim03_Structures/Interference2DCenteredSquareLattice 2e-10)
test_example(sim03_Structures/Interference2DParaCrystal 2e-10)
test_example(sim03_Structures/Interference2DRotatedSquareLattice 2e-10)
test_example(sim03_Structures/Interference2DSquareLattice 2e-10)
test_example(sim03_Structures/Interference2DLatticeSumOfRotated 2e-10)
test_example(sim03_Structures/RectangularGrating 0.5)
test_example(sim03_Structures/SpheresAtHexLattice 2e-10)
test_example(sim03_Structures/TriangularRipple 2e-10)

test_example(sim04_Multilayers/BuriedParticles 2e-10)
test_example(sim04_Multilayers/CorrelatedRoughness 2e-10)
test_example(sim04_Multilayers/CylindersInAverageLayer 2e-10)
test_example(sim04_Multilayers/HalfSpheresInAverageTopLayer 2e-10)

test_example(sim05_Magnetism/MagneticSpheres 2e-10)

test_example(sim11_Device/BeamDivergence 2e-10)
test_example(sim11_Device/DetectorResolutionFunction 2e-10)
test_example(sim11_Device/OffSpecularSimulation 2e-10)
test_example(sim11_Device/ConstantBackground 2e-10)

test_example(sim21_Reflectometry/BasicSpecularSimulation 2e-10)
test_example(sim21_Reflectometry/BeamAngularDivergence 2e-10)
test_example(sim21_Reflectometry/BeamFullDivergence 2e-10)
test_example(sim21_Reflectometry/TimeOfFlightReflectometry 2e-10)
test_example(sim21_Reflectometry/TOFRWithResolution 2e-10)

test_example(sim29_DepthProbe/DepthProbe 2e-10)

test_example(sim31_Parameterization/SimulationParameters 2e-10)
