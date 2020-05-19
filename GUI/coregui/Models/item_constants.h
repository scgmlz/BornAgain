// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/item_constants.h
//! @brief     Defines item constants
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ITEM_CONSTANTS_H
#define ITEM_CONSTANTS_H

#include <QString>

namespace Constants
{

// --- Items -------------------------------------------------------------------

using ModelType = QString;

const ModelType Yes = "Yes";
const ModelType No = "No";

const ModelType RootItemType = "ROOT_ITEM";

const ModelType LayerType = "Layer";
const ModelType MesoCrystalType = "MesoCrystal";
const ModelType MultiLayerType = "MultiLayer";
const ModelType ParticleType = "Particle";
const ModelType ParticleLayoutType = "ParticleLayout";
const ModelType ParticleCoreShellType = "ParticleCoreShell";
const ModelType ParticleDistributionType = "ParticleDistribution";
const ModelType ParticleCompositionType = "ParticleComposition";
const ModelType RotationType = "Rotation";
const ModelType InterferenceFunction1DLatticeType = "Interference1DLattice";
const ModelType InterferenceFunction2DLatticeType = "Interference2DLattice";
const ModelType InterferenceFunction2DParaCrystalType = "Interference2DParaCrystal";
const ModelType InterferenceFunctionFinite2DLatticeType = "InterferenceFinite2DLattice";
const ModelType InterferenceFunctionHardDiskType = "InterferenceHardDisk";
const ModelType InterferenceFunctionRadialParaCrystalType = "InterferenceRadialParaCrystal";
const ModelType GISASInstrumentType = "GISASInstrument";
const ModelType OffSpecInstrumentType = "OffSpecInstrument";
const ModelType SpecularInstrumentType = "SpecularInstrument";
const ModelType DepthProbeInstrumentType = "DepthProbeInstrument";
const ModelType GISASBeamType = "GISASBeam";
const ModelType SpecularBeamType = "SpecularBeam";

const ModelType FormFactorType = "FormFactor";
const ModelType AnisoPyramidType = "AnisoPyramid";
const ModelType BoxType = "Box";
const ModelType ConeType = "Cone";
const ModelType Cone6Type = "Cone6";
const ModelType CuboctahedronType = "Cuboctahedron";
const ModelType CylinderType = "Cylinder";
const ModelType DodecahedronType = "Dodecahedron";
const ModelType DotType = "Dot";
const ModelType EllipsoidalCylinderType = "EllipsoidalCylinder";
const ModelType FullSphereType = "FullSphere";
const ModelType FullSpheroidType = "FullSpheroid";
const ModelType HemiEllipsoidType = "HemiEllipsoid";
const ModelType IcosahedronType = "Icosahedron";
const ModelType Prism3Type = "Prism3";
const ModelType Prism6Type = "Prism6";
const ModelType PyramidType = "Pyramid";
const ModelType Ripple1BoxType = "Ripple1Box";
const ModelType Ripple1GaussType = "Ripple1Gauss";
const ModelType Ripple1LorentzType = "Ripple1Lorentz";
const ModelType Ripple2Type = "Ripple2";
const ModelType TetrahedronType = "Tetrahedron";
const ModelType TruncatedCubeType = "TruncatedCube";
const ModelType TruncatedSphereType = "TruncatedSphere";
const ModelType TruncatedSpheroidType = "TruncatedSpheroid";

const ModelType XRotationType = "XRotation";
const ModelType YRotationType = "YRotation";
const ModelType ZRotationType = "ZRotation";
const ModelType EulerRotationType = "EulerRotation";

const ModelType PropertyType = "Property";
const ModelType VectorType = "Vector";
const ModelType GroupItemType = "GroupProperty";

const ModelType LayerBasicRoughnessType = "LayerBasicRoughness";
const ModelType LayerZeroRoughnessType = "LayerZeroRoughness";

const ModelType SphericalDetectorType = "SphericalDetector";
const ModelType RectangularDetectorType = "RectangularDetector";

const ModelType DistributionNoneType = "DistributionNone";
const ModelType DistributionGateType = "DistributionGate";
const ModelType DistributionLorentzType = "DistributionLorentz";
const ModelType DistributionGaussianType = "DistributionGaussian";
const ModelType DistributionLogNormalType = "DistributionLogNormal";
const ModelType DistributionCosineType = "DistributionCosine";
const ModelType DistributionTrapezoidType = "DistributionTrapezoid";

const ModelType FTDistribution1DCauchyType = "FTDistribution1DCauchy";
const ModelType FTDistribution1DGaussType = "FTDistribution1DGauss";
const ModelType FTDistribution1DGateType = "FTDistribution1DGate";
const ModelType FTDistribution1DTriangleType = "FTDistribution1DTriangle";
const ModelType FTDistribution1DCosineType = "FTDistribution1DCosine";
const ModelType FTDistribution1DVoigtType = "FTDistribution1DVoigt";

const ModelType FTDistribution2DCauchyType = "FTDistribution2DCauchy";
const ModelType FTDistribution2DGaussType = "FTDistribution2DGauss";
const ModelType FTDistribution2DGateType = "FTDistribution2DGate";
const ModelType FTDistribution2DConeType = "FTDistribution2DCone";
const ModelType FTDistribution2DVoigtType = "FTDistribution2DVoigt";

const ModelType FTDecayFunction1DCauchyType = "FTDecayFunction1DCauchy";
const ModelType FTDecayFunction1DGaussType = "FTDecayFunction1DGauss";
const ModelType FTDecayFunction1DTriangleType = "FTDecayFunction1DTriangle";
const ModelType FTDecayFunction1DVoigtType = "FTDecayFunction1DVoigt";

const ModelType FTDecayFunction2DCauchyType = "FTDecayFunction2DCauchy";
const ModelType FTDecayFunction2DGaussType = "FTDecayFunction2DGauss";
const ModelType FTDecayFunction2DVoigtType = "FTDecayFunction2DVoigt";

const ModelType BasicLatticeType = "BasicLattice";
const ModelType SquareLatticeType = "SquareLattice";
const ModelType HexagonalLatticeType = "HexagonalLattice";

const ModelType MaterialType = "Material";
const ModelType MaterialContainerType = "MaterialContainer";

const ModelType MaterialRefractiveDataType = "MaterialRefractiveData";
const ModelType MaterialSLDDataType = "MaterialSLDData";

const ModelType MagneticFieldType = "MagneticField";

const ModelType ParameterContainerType = "Parameter Container";
const ModelType ParameterType = "Parameter";
const ModelType ParameterLabelType = "Parameter Label";

const ModelType FitParameterContainerType = "FitParameterContainer";
const ModelType FitParameterType = "FitParameter";
const ModelType FitParameterLinkType = "FitParameterLink";
const ModelType FitSuiteType = "FitSuite";

const ModelType JobItemType = "JobItem";
const ModelType IntensityDataType = "IntensityData";
const ModelType SpecularDataType = "SpecularData";
const ModelType Data1DViewItemType = "Data1DViewItem";
const ModelType DataPropertyContainerType = "DataPropertyContainer";
const ModelType DataItem1DPropertiesType = "DataItem1DProperties";

const ModelType BasicAxisType = "BasicAxis";
const ModelType PointwiseAxisType = "PointwiseAxis";
const ModelType AmplitudeAxisType = "AmplitudeAxis";

const ModelType BeamDistributionType = "BeamDistribution";
const ModelType BeamWavelengthType = "BeamWavelength";
const ModelType BeamAzimuthalAngleType = "BeamAzimuthalAngle";
const ModelType BeamInclinationAngleType = "BeamInclinationAngle";
const ModelType SpecularBeamInclinationType = "SpecularBeamInclinationAxis";
const ModelType SpecularBeamWavelengthType = "SpecularBeamWavelength";

const ModelType ResolutionFunctionNoneType = "ResolutionFunctionNone";
const ModelType ResolutionFunction2DGaussianType = "ResolutionFunction2DGaussian";

const ModelType MaskContainerType = "MaskContainer";
const ModelType RectangleMaskType = "RectangleMask";
const ModelType PolygonMaskType = "PolygonMask";
const ModelType PolygonPointType = "PolygonPoint";
const ModelType EllipseMaskType = "EllipseMask";
const ModelType VerticalLineMaskType = "VerticalLineMask";
const ModelType HorizontalLineMaskType = "HorizontalLineMask";
const ModelType MaskAllType = "MaskAllMask";

const ModelType RegionOfInterestType = "RegionOfInterest";

const ModelType SimulationOptionsType = "SimulationOptions";

const ModelType RealDataType = "RealData";

const ModelType MinimizerContainerType = "MinimizerContainer";
const ModelType MinuitMinimizerType = "Minuit2";
const ModelType GSLMultiMinimizerType = "GSLMultiMin";
const ModelType GSLLMAMinimizerType = "GSLLMA";
const ModelType GSLSimAnMinimizerType = "GSLSimAn";
const ModelType GeneticMinimizerType = "Genetic";
const ModelType TestMinimizerType = "Test";

const ModelType RealLimitsLimitlessType = "RealLimitsLimitless";
const ModelType RealLimitsPositiveType = "RealLimitsPositive";
const ModelType RealLimitsNonnegativeType = "RealLimitsNonnegative";
const ModelType RealLimitsLowerLimitedType = "RealLimitsLowerLimited";
const ModelType RealLimitsUpperLimitedType = "RealLimitsUpperLimited";
const ModelType RealLimitsLimitedType = "RealLimitsLimited";

const ModelType ProjectionContainerType = "ProjectionContainer";

const ModelType BackgroundNoneType = "NoBackground";
const ModelType ConstantBackgroundType = "ConstantBackground";
const ModelType PoissonNoiseBackgroundType = "PoissonNoiseBackground";

const ModelType FootprintNoneType = "NoFootprint";
const ModelType FootprintGaussianType = "GaussianFootrpint";
const ModelType FootprintSquareType = "SquareFootprint";

const ModelType VarianceConstantFunctionType = "VarianceConstantFunction";
const ModelType VarianceSimFunctionType = "VarianceSimFunction";

// --- Groups ------------------------------------------------------------------

const ModelType FormFactorGroup = "Form Factor";
const ModelType RotationGroup = "Rotation group";
const ModelType LayerRoughnessGroup = "Roughness";
const ModelType DetectorGroup = "Detector group";
const ModelType DistributionGroup = "Distribution group";
const ModelType DistributionExtendedGroup = "Distribution extended group";
const ModelType SymmetricDistributionGroup = "Symmetric distribution group";
const ModelType FTDistribution1DGroup = "PDF 1D";
const ModelType FTDistribution2DGroup = "PDF 2D";
const ModelType FTDecayFunction1DGroup = "Decay function 1D";
const ModelType FTDecayFunction2DGroup = "Decay function 2D";
const ModelType LatticeGroup = "Lattice group";
const ModelType MaterialGroup = "Material group";
const ModelType ResolutionFunctionGroup = "Resolution function group";
const ModelType MinimizerLibraryGroup = "Minimizer library group";
const ModelType RealLimitsGroup = "RealLimits group";
const ModelType BackgroundGroup = "Background group";
const ModelType MaterialDataGroup = "Material data group";
const ModelType FootprintGroup = "Footprint group";
const ModelType AxesGroup = "Axes group";
const ModelType VarianceFunctionGroup = "Variance group";

// --- Units&Constants----------------------------------------------------------

const ModelType UnitsNbins = "nbins";
const ModelType UnitsRadians = "Radians";
const ModelType UnitsDegrees = "Degrees";
const ModelType UnitsMm = "mm";
const ModelType UnitsQyQz = "q-space";

const ModelType STATUS_IDLE = "Idle";
const ModelType STATUS_RUNNING = "Running";
const ModelType STATUS_FITTING = "Fitting";
const ModelType STATUS_COMPLETED = "Completed";
const ModelType STATUS_CANCELED = "Canceled";
const ModelType STATUS_FAILED = "Failed";

const ModelType GRADIENT_GRAYSCALE = "Grayscale";
const ModelType GRADIENT_HOT = "Hot";
const ModelType GRADIENT_COLD = "Cold";
const ModelType GRADIENT_NIGHT = "Night";
const ModelType GRADIENT_CANDY = "Candy";
const ModelType GRADIENT_GEOGRAPHY = "Geography";
const ModelType GRADIENT_ION = "Ion";
const ModelType GRADIENT_THERMAL = "Thermal";
const ModelType GRADIENT_POLAR = "Polar";
const ModelType GRADIENT_SPECTRUM = "Spectrum";
const ModelType GRADIENT_JET = "Jet";
const ModelType GRADIENT_HUES = "Hues";

const ModelType JOB_RUN_IMMEDIATELY = "Immediately";
const ModelType JOB_RUN_IN_BACKGROUND = "In background";
const ModelType JOB_BACKUP = "_backup";

const ModelType SIMULATION_ANALYTICAL = "Analytical";
const ModelType SIMULATION_MONTECARLO = "Monte-Carlo Integration";

const ModelType ALIGNMENT_GENERIC = "Generic";
const ModelType ALIGNMENT_TO_SAMPLE = "Perpendicular to sample x-axis";
const ModelType ALIGNMENT_TO_DIRECT_BEAM = "Perpendicular to direct beam";
const ModelType ALIGNMENT_TO_REFLECTED_BEAM = "Perpendicular to reflected beam";
const ModelType ALIGNMENT_TO_REFLECTED_BEAM_DPOS = "Perpendicular to reflected beam (dpos)";

const ModelType FITPAR_FIXED = "fixed";
const ModelType FITPAR_LIMITED = "limited";
const ModelType FITPAR_LOWERLIMITED = "lower limited";
const ModelType FITPAR_UPPERLIMITED = "upper limited";
const ModelType FITPAR_FREE = "free";

const ModelType DistributionSigmaFactor = "Sigma factor";

const ModelType LAYOUT_DA = "Decoupling Approximation";
const ModelType LAYOUT_SSCA = "Size Space Coupling Approximation";

const ModelType AMBIENT_LAYER_MATERIAL = "Ambient Layer Material";
const ModelType AVERAGE_LAYER_MATERIAL = "Average Layer Material";

// --- Presentation types ----------------------------------------------------------

const QString IntensityDataPresentation = "Color Map";
const QString SpecularDataPresentation = "Reflectometry";
const QString IntensityProjectionsPresentation = "Projections";
const QString FitComparisonPresentation2D = "Fit 2D Data";
const QString FitComparisonPresentation1D = "Fit 1D Data";
const QString MaskEditorPresentation = "Mask Editor";

// --- Custom variants ----------------------------------------------------------

const ModelType ExternalPropertyType = "ExternalProperty";
const ModelType ComboPropertyType = "ComboProperty";

// --- Custom editors for variant propertues ---
const ModelType DefaultEditorType = "Default";
const ModelType ScientificEditorType = "SceintificDouble";
const ModelType ScientificSpinBoxType = "ScientificSpinBox";
const ModelType MaterialEditorExternalType = "ExtMaterialEditor";
const ModelType ColorEditorExternalType = "ExtColorEditor";
const ModelType MultiSelectionComboEditorType = "MultiSelectionComboEditor";
} // namespace Constants

#endif // ITEM_CONSTANTS_H
