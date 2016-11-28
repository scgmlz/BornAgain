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

# ppt = python persistence test:
function(ppt example tolerance)
    set(script ${PY_EXAMPLES_DIR}/${example})
    get_filename_component(script_dir  ${script} DIRECTORY)
    get_filename_component(script_name ${script} NAME_WE)
    get_filename_component(script_ext  ${script} EXT)
    if (NOT ${script_ext} STREQUAL ".py" )
        message(SEND_ERROR
            "Unexpected file name extension '${script_ext}' in Python script ${script}")
        continue()
    endif()
    add_test(PyPersistenceTest/${script_name} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PyPersistenceTest
        ${script_dir} ${script_name} ${tolerance})
endfunction()

ppt("simulation/ex01_BasicParticles/AllFormFactorsAvailable.py" 2e-10)
ppt("simulation/ex01_BasicParticles/CylindersAndPrisms.py" 2e-10)
ppt("simulation/ex01_BasicParticles/CylindersInBA.py" 2e-10)
ppt("simulation/ex01_BasicParticles/CylindersInDWBA.py" 2e-10)
ppt("simulation/ex01_BasicParticles/CylindersWithSizeDistribution.py" 2e-10)
ppt("simulation/ex01_BasicParticles/RotatedPyramids.py" 2e-10)
ppt("simulation/ex01_BasicParticles/TwoTypesOfCylindersWithSizeDistribution.py" 2e-10)
ppt("simulation/ex02_LayeredStructures/BuriedParticles.py" 2e-10)
ppt("simulation/ex02_LayeredStructures/CorrelatedRoughness.py" 2e-10)
ppt("simulation/ex03_InterferenceFunctions/ApproximationDA.py" 2e-10)
ppt("simulation/ex03_InterferenceFunctions/ApproximationLMA.py" 2e-10)
ppt("simulation/ex03_InterferenceFunctions/ApproximationSSCA.py" 2e-10)
ppt("simulation/ex03_InterferenceFunctions/CosineRipplesAtRectLattice.py" 2e-10)
ppt("simulation/ex03_InterferenceFunctions/Interference1DLattice.py" 2e-10)
ppt("simulation/ex03_InterferenceFunctions/Interference1DRadialParaCrystal.py" 2e-10)
ppt("simulation/ex03_InterferenceFunctions/Interference2DCenteredSquareLattice.py" 2e-10)
ppt("simulation/ex03_InterferenceFunctions/Interference2DLatticeSumOfRotated.py" 2e-10)
ppt("simulation/ex03_InterferenceFunctions/Interference2DParaCrystal.py" 2e-10)
ppt("simulation/ex03_InterferenceFunctions/Interference2DRotatedSquareLattice.py" 2e-10)
ppt("simulation/ex03_InterferenceFunctions/Interference2DSquareLattice.py" 2e-10)
ppt("simulation/ex03_InterferenceFunctions/RectangularGrating.py" 0.5)
ppt("simulation/ex03_InterferenceFunctions/SpheresAtHexLattice.py" 2e-10)
ppt("simulation/ex03_InterferenceFunctions/TriangularRipple.py" 2e-10)
ppt("simulation/ex04_ComplexShapes/CoreShellNanoparticles.py" 2e-10)
ppt("simulation/ex04_ComplexShapes/CustomFormFactor.py" 2e-10)
ppt("simulation/ex04_ComplexShapes/HexagonalLatticesWithBasis.py" 2e-10)
ppt("simulation/ex04_ComplexShapes/LargeParticlesFormFactor.py" 0.5)
ppt("simulation/ex05_BeamAndDetector/BeamDivergence.py" 2e-10)
ppt("simulation/ex05_BeamAndDetector/DetectorResolutionFunction.py" 2e-10)
ppt("simulation/ex05_BeamAndDetector/OffSpecularSimulation.py" 2e-10)
ppt("simulation/ex05_BeamAndDetector/RectangularDetector.py" 2e-10)
ppt("simulation/ex05_BeamAndDetector/SpecularSimulation.py" 2e-10)
ppt("simulation/ex06_Miscellaneous/AxesInDifferentUnits.py" 2e-10)
ppt("fitting/ex01_SampleParametersIntro/SampleParametersIntro.py" 2e-10)
