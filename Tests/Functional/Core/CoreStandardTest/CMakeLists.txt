############################################################################
# Tests/Functional/Core/CMakeLists.txt
############################################################################

# CoreStandardTest cases:
set(test_cases
    ApproximationDA
    ApproximationLMA
    ApproximationSSCA
    Basic2DParaCrystal
    BeamDivergence
    BoxCompositionRotateX
    BoxCompositionRotateY
    BoxCompositionRotateZ
    BoxCompositionRotateZandY
    BoxesWithSpecular
    BoxStackComposition
    CenteredSquareLattice
    ConstantBackground
    CoreShellBoxRotateZandY
    CoreShellParticle
    CosineRipple
    CustomMorphology
    CylindersAndPrisms
    CylindersInSSCA
    CylindersWithSizeDistribution
    DetectorResolution
    FormFactors
    FormFactorsAbs
    GISASAbsorptiveSLDLayers
    HexParaCrystal
    LargeCylindersMonteCarlo
    Lattice1D
    MagneticParticleZeroField
    MagneticSpheres
    MagneticSubstrateZeroField
    MagneticRotation
    MesoCrystal
    MultiLayerWithRoughness
    MultipleLayout
    ParticleComposition
    RadialParaCrystal
    RectDetectorGeneric
    RectDetectorPerpToDirectBeam
    RectDetectorPerpToReflectedBeam
    RectDetectorPerpToReflectedBeamDpos
    RectDetectorPerpToSample
    RectParaCrystal
    RotatedCylinder
    RotatedPyramids
    RotatedSquareLattice
    FiniteSquareLattice
    SimulationWithMasks
    SquareLattice
    TransformBox
    TriangularRipple
    AsymRipple
    TwoTypesCylindersDistribution
    SphericalDetWithRoi
    RectDetWithRoi
    SlicedComposition
    RotatedPyramidsDistribution
    SpheresWithLimitsDistribution
    ConesWithLimitsDistribution
    HomogeneousTiNiSample
    HomogeneousTiNiSampleWithAbsorption
    RoughnessInSpecular
    GaussianBeamFootprint
    SquareBeamFootprint
    SpecularDivergentBeam
    OffSpecularResonator
    DepthProbeTest
    )

add_executable(CoreStandardTest main.cpp CoreStandardTest.h CoreStandardTest.cpp)
target_link_libraries(CoreStandardTest BornAgainCore BornAgainTestMachinery)
foreach(test_case ${test_cases})
    add_test(CoreStandardTest/${test_case}
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CoreStandardTest ${test_case})
endforeach()
