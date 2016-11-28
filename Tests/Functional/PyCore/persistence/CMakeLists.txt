############################################################################
# Tests/Functional/PyCore/persistence/CMakeLists.txt
############################################################################

set(PYPERSIST_REF_DIR ${REFERENCE_DIR}/PyPersist)
set(PYPERSIST_OUT_DIR ${BUILD_REF_DIR}/PyPersist)
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

add_executable(PyPersistenceTest RunPyPersistenceTest.cpp PyPersistenceTest.h PyPersistenceTest.cpp)
target_link_libraries(PyPersistenceTest BornAgainCore BornAgainTestMachinery)
foreach(example ${PY_EXAMPLES})
endforeach()

# lppt = legacy python persistence test:
function(lppt example tolerance)
    set(script_path ${PY_EXAMPLES_DIR}/${example}.py)
    get_filename_component(script_name ${script_path} NAME_WE)
    add_test(PyPersistenceTest/${script_name} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PyPersistenceTest
        ${script_path} ${script_name} ${tolerance})
endfunction()

lppt("simulation/ex01_BasicParticles/AllFormFactorsAvailable" 2e-10)
lppt("simulation/ex01_BasicParticles/CylindersAndPrisms" 2e-10)
lppt("simulation/ex01_BasicParticles/CylindersInBA" 2e-10)
lppt("simulation/ex01_BasicParticles/CylindersInDWBA" 2e-10)
lppt("simulation/ex01_BasicParticles/CylindersWithSizeDistribution" 2e-10)
lppt("simulation/ex01_BasicParticles/RotatedPyramids" 2e-10)
lppt("simulation/ex01_BasicParticles/TwoTypesOfCylindersWithSizeDistribution" 2e-10)
lppt("simulation/ex02_LayeredStructures/CorrelatedRoughness" 2e-10)
lppt("simulation/ex03_InterferenceFunctions/ApproximationDA" 2e-10)
lppt("simulation/ex03_InterferenceFunctions/ApproximationLMA" 2e-10)
lppt("simulation/ex03_InterferenceFunctions/ApproximationSSCA" 2e-10)
lppt("simulation/ex03_InterferenceFunctions/CosineRipplesAtRectLattice" 2e-10)
lppt("simulation/ex03_InterferenceFunctions/Interference1DLattice" 2e-10)
lppt("simulation/ex03_InterferenceFunctions/Interference1DRadialParaCrystal" 2e-10)
lppt("simulation/ex03_InterferenceFunctions/Interference2DCenteredSquareLattice" 2e-10)
lppt("simulation/ex03_InterferenceFunctions/Interference2DLatticeSumOfRotated" 2e-10)
lppt("simulation/ex03_InterferenceFunctions/Interference2DParaCrystal" 2e-10)
lppt("simulation/ex03_InterferenceFunctions/Interference2DRotatedSquareLattice" 2e-10)
lppt("simulation/ex03_InterferenceFunctions/Interference2DSquareLattice" 2e-10)
lppt("simulation/ex03_InterferenceFunctions/RectangularGrating" 0.5)
lppt("simulation/ex03_InterferenceFunctions/SpheresAtHexLattice" 2e-10)
lppt("simulation/ex03_InterferenceFunctions/TriangularRipple" 2e-10)
lppt("simulation/ex04_ComplexShapes/CoreShellNanoparticles" 2e-10)
lppt("simulation/ex04_ComplexShapes/CustomFormFactor" 2e-10)
lppt("simulation/ex04_ComplexShapes/HexagonalLatticesWithBasis" 2e-10)
lppt("simulation/ex04_ComplexShapes/LargeParticlesFormFactor" 0.5)
lppt("simulation/ex05_BeamAndDetector/BeamDivergence" 2e-10)
lppt("simulation/ex05_BeamAndDetector/DetectorResolutionFunction" 2e-10)
lppt("simulation/ex05_BeamAndDetector/OffSpecularSimulation" 2e-10)
lppt("simulation/ex05_BeamAndDetector/RectangularDetector" 2e-10)
lppt("simulation/ex05_BeamAndDetector/SpecularSimulation" 2e-10)
lppt("simulation/ex06_Miscellaneous/AxesInDifferentUnits" 2e-10)
lppt("fitting/ex01_SampleParametersIntro/SampleParametersIntro" 2e-10)

# gppt = generic python persistence test:
function(gppt script wrapped_dir wrapped_name tolerance)
    configure_file(${PY_EXAMPLES_DIR}/${wrapped_dir}/${wrapped_name}.py
        ${CMAKE_BINARY_DIR}/lib/bornagain/${wrapped_name}.py COPYONLY)
    add_test(PyPersistenceTest/${script} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PyPersistenceTest
        ${CMAKE_CURRENT_SOURCE_DIR}/${script}.py ${script} ${tolerance})
endfunction()

# sppt = standard python persistence test:
function(sppt script wrapped_dir wrapped_name tolerance)
    configure_file(${PY_EXAMPLES_DIR}/${wrapped_dir}/${wrapped_name}.py
        ${CMAKE_BINARY_DIR}/lib/bornagain/${wrapped_name}.py COPYONLY)
    set(WRAPPED_MODULE ${wrapped_name})
    configure_file(standard_test.py.in ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${script}.py @ONLY)
    add_test(PyPersistenceTest/${script} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PyPersistenceTest
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${script}.py ${script} ${tolerance})
endfunction()

sppt("ex02_BuriedParticles" "simulation/ex02_LayeredStructures" "BuriedParticles" 2e-10)
