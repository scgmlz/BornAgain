###############################################################################
# Run unmodified examples
###############################################################################

set(test_script ${TOOL_DIR}/code/batch-plot.py)

set(output_dir ${TEST_OUTPUT_DIR_PY_EXAMPLES})
file(MAKE_DIRECTORY ${output_dir})

# Run one Python example.
# Check whether the example passes.
# Don't check results.
# If there are matplotlib commands, skip plt.show().
function(run_example example label)
    get_filename_component(name ${example} NAME_WE)
    set(test_name Example.run.${name})
    add_test(${test_name}
        env PYTHONPATH=${CMAKE_LIBRARY_OUTPUT_DIRECTORY} NOSHOW=TRUE
        ${Python3_EXECUTABLE} ${test_script} -s ${example} ${output_dir})
    if(NOT label STREQUAL "")
        set_tests_properties(${test_name} PROPERTIES LABELS ${label})
    endif()
endfunction()

function(run_examples examples label)
    foreach(example ${examples})
        run_example(${example} "${label}")
    endforeach()
endfunction()

# Examples from scatter2d; all but one prototype get the label XL
set(prototype ${EXAMPLES_DIR}/scatter2d/CylindersInDWBA.py)
file(GLOB examples ${EXAMPLES_DIR}/scatter2d/*.py)
list(REMOVE_ITEM examples ${prototype})
if (WIN32)
    # Convergence problem in Gauss-Kronrod integration
    list(REMOVE_ITEM examples ${EXAMPLES_DIR}/scatter2d/Interference2DParaCrystal.py)
endif()
run_example(${prototype} "")
run_examples("${examples}" "XL")

# Examples from other directories
file(GLOB examples
    ${EXAMPLES_DIR}/specular/*.py
    ${EXAMPLES_DIR}/varia/*.py
    ${EXAMPLES_DIR}/fit55_Specular/FitSpecularBasics.py)
list(REMOVE_ITEM examples ${EXAMPLES_DIR}/varia/SimulationParameters.py)
run_examples("${examples}" "")

############################################################################
# Check results of modified examples
############################################################################

set(OUTPUT_DIR ${TEST_OUTPUT_DIR_PY_PERSIST})
file(MAKE_DIRECTORY ${OUTPUT_DIR})

# Python persistence test
function(test_example example tolerance)
    set(script_path ${EXAMPLES_DIR}/${example}.py)
    get_filename_component(EXAMPLE_NAME ${script_path} NAME_WE)
    get_filename_component(EXAMPLE_DIR ${script_path} DIRECTORY)

    set(test_name Example.persist.${EXAMPLE_NAME})

    set(PYPERSIST_TOLERANCE ${tolerance})

    # modified example to run as a test
    set(example_mod ${OUTPUT_DIR}/${EXAMPLE_NAME}_mod.py)
    configure_file(PyPersistence.py.in ${example_mod} @ONLY)

    add_test(${test_name} ${Python3_EXECUTABLE} -B ${example_mod})
endfunction()

test_example(scatter2d/ApproximationDA 2e-10)
test_example(scatter2d/ApproximationLMA 2e-10)
test_example(scatter2d/ApproximationSSCA 2e-10)
test_example(scatter2d/BeamDivergence 2e-10)
test_example(scatter2d/BuriedParticles 2e-10)
test_example(scatter2d/ConstantBackground 2e-10)
test_example(scatter2d/CoreShellNanoparticles 2e-10)
test_example(scatter2d/CorrelatedRoughness 2e-10)
test_example(scatter2d/CosineRipplesAtRectLattice 2e-10)
test_example(scatter2d/CylindersAndPrisms 2e-10)
test_example(scatter2d/CylindersInAverageLayer 2e-10)
test_example(scatter2d/CylindersInBA 2e-10)
test_example(scatter2d/CylindersInDWBA 2e-10)
test_example(scatter2d/CylindersWithSizeDistribution 2e-10)
test_example(scatter2d/DetectorResolutionFunction 2e-10)
test_example(scatter2d/DodecahedraSAS.py 2e-10)
test_example(scatter2d/HalfSpheresInAverageTopLayer 2e-10)
test_example(scatter2d/HexagonalLatticesWithBasis 2e-10)
test_example(scatter2d/Interference1DRadialParaCrystal 2e-10)
test_example(scatter2d/Interference2DCenteredSquareLattice 2e-10)
test_example(scatter2d/Interference2DLatticeSumOfRotated 2e-10)
test_example(scatter2d/Interference2DParaCrystal 2e-10)
test_example(scatter2d/Interference2DRotatedSquareLattice 2e-10)
test_example(scatter2d/Interference2DSquareLattice 2e-10)
test_example(scatter2d/MagneticSpheres 2e-10)
test_example(scatter2d/RectangularGrating 0.5)
test_example(scatter2d/RotatedPyramids 2e-10)
test_example(scatter2d/SpheresAtHexLattice 2e-10)
test_example(scatter2d/TriangularRipple 2e-10)
test_example(scatter2d/TwoTypesOfCylindersWithSizeDistribution 2e-10)

test_example(specular/BasicSpecularSimulation 2e-10)
test_example(specular/BeamAngularDivergence 2e-10)
test_example(specular/BeamFullDivergence 2e-10)
test_example(specular/TOFRWithResolution 2e-10)
test_example(specular/TimeOfFlightReflectometry 2e-10)

test_example(varia/CustomFormFactor 2e-10)
test_example(varia/DepthProbe 2e-10)
test_example(varia/Interference1DLattice 1.5)
test_example(varia/OffSpecularSimulation 2e-10)

# TODO replace after revision of parameter machinery
# test_example(varia/SimulationParameters 2e-10)
