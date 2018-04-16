############################################################################
# Tests/Functional/GUI/CMakeLists.txt
############################################################################

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
    CylindersAndPrisms
    CylindersWithSizeDistribution
    DetectorResolution
    FormFactors
    GISASAbsorptiveSLDLayers
    HexParaCrystal
    LargeCylindersMonteCarlo
    Lattice1D
    MagneticSpheres
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
    OffSpecularResonator
    SquareBeamFootprint
    GaussianBeamFootprint
    SpecularDivergentBeam
    HomogeneousTiNiSampleWithAbsorption
)

add_executable(GUIStandardTest main.cpp GUIStandardTest.cpp GUIStandardTest.h )
target_link_libraries(GUIStandardTest BornAgainCore BornAgainGUI BornAgainTestMachinery)

qt5_use_modules(GUIStandardTest Widgets Core Gui Designer PrintSupport Network)
foreach(test_case ${test_cases})
    add_test(GUIStandardTest/${test_case} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GUIStandardTest ${test_case})
endforeach()
