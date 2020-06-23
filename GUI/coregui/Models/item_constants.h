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

const QString Yes = "Yes";
const QString No = "No";

const QString RootItemType = "ROOT_ITEM";

const QString LayerType = "Layer";
const QString MesoCrystalType = "MesoCrystal";
const QString MultiLayerType = "MultiLayer";
const QString ParticleType = "Particle";
const QString ParticleLayoutType = "ParticleLayout";
const QString ParticleCoreShellType = "ParticleCoreShell";
const QString ParticleDistributionType = "ParticleDistribution";
const QString ParticleCompositionType = "ParticleComposition";
const QString RotationType = "Rotation";
const QString InterferenceFunction1DLatticeType = "Interference1DLattice";
const QString InterferenceFunction2DLatticeType = "Interference2DLattice";
const QString InterferenceFunction2DParaCrystalType = "Interference2DParaCrystal";
const QString InterferenceFunctionFinite2DLatticeType = "InterferenceFinite2DLattice";
const QString InterferenceFunctionHardDiskType = "InterferenceHardDisk";
const QString InterferenceFunctionRadialParaCrystalType = "InterferenceRadialParaCrystal";
const QString GISASInstrumentType = "GISASInstrument";
const QString OffSpecInstrumentType = "OffSpecInstrument";
const QString SpecularInstrumentType = "SpecularInstrument";
const QString DepthProbeInstrumentType = "DepthProbeInstrument";
const QString GISASBeamType = "GISASBeam";
const QString SpecularBeamType = "SpecularBeam";

const QString FormFactorType = "FormFactor";
const QString AnisoPyramidType = "AnisoPyramid";
const QString BarGaussType = "BarGauss";
const QString BarLorentzType = "BarLorentz";
const QString BoxType = "Box";
const QString ConeType = "Cone";
const QString Cone6Type = "Cone6";
const QString CuboctahedronType = "Cuboctahedron";
const QString CylinderType = "Cylinder";
const QString DodecahedronType = "Dodecahedron";
const QString DotType = "Dot";
const QString EllipsoidalCylinderType = "EllipsoidalCylinder";
const QString FullSphereType = "FullSphere";
const QString FullSpheroidType = "FullSpheroid";
const QString HemiEllipsoidType = "HemiEllipsoid";
const QString IcosahedronType = "Icosahedron";
const QString Prism3Type = "Prism3";
const QString Prism6Type = "Prism6";
const QString PyramidType = "Pyramid";
const QString Ripple1BoxType = "Ripple1Box";
const QString Ripple1GaussType = "Ripple1Gauss";
const QString Ripple1LorentzType = "Ripple1Lorentz";
const QString Ripple2BoxType = "Ripple2Box";
const QString Ripple2GaussType = "Ripple2Gauss";
const QString Ripple2LorentzType = "Ripple2Lorentz";
const QString TetrahedronType = "Tetrahedron";
const QString TruncatedCubeType = "TruncatedCube";
const QString TruncatedSphereType = "TruncatedSphere";
const QString TruncatedSpheroidType = "TruncatedSpheroid";

const QString XRotationType = "XRotation";
const QString YRotationType = "YRotation";
const QString ZRotationType = "ZRotation";
const QString EulerRotationType = "EulerRotation";

const QString PropertyType = "Property";
const QString VectorType = "Vector";
const QString GroupItemType = "GroupProperty";

const QString LayerBasicRoughnessType = "LayerBasicRoughness";
const QString LayerZeroRoughnessType = "LayerZeroRoughness";

const QString SphericalDetectorType = "SphericalDetector";
const QString RectangularDetectorType = "RectangularDetector";

const QString DistributionNoneType = "DistributionNone";
const QString DistributionGateType = "DistributionGate";
const QString DistributionLorentzType = "DistributionLorentz";
const QString DistributionGaussianType = "DistributionGaussian";
const QString DistributionLogNormalType = "DistributionLogNormal";
const QString DistributionCosineType = "DistributionCosine";
const QString DistributionTrapezoidType = "DistributionTrapezoid";

const QString FTDistribution1DCauchyType = "FTDistribution1DCauchy";
const QString FTDistribution1DGaussType = "FTDistribution1DGauss";
const QString FTDistribution1DGateType = "FTDistribution1DGate";
const QString FTDistribution1DTriangleType = "FTDistribution1DTriangle";
const QString FTDistribution1DCosineType = "FTDistribution1DCosine";
const QString FTDistribution1DVoigtType = "FTDistribution1DVoigt";

const QString FTDistribution2DCauchyType = "FTDistribution2DCauchy";
const QString FTDistribution2DGaussType = "FTDistribution2DGauss";
const QString FTDistribution2DGateType = "FTDistribution2DGate";
const QString FTDistribution2DConeType = "FTDistribution2DCone";
const QString FTDistribution2DVoigtType = "FTDistribution2DVoigt";

const QString FTDecayFunction1DCauchyType = "FTDecayFunction1DCauchy";
const QString FTDecayFunction1DGaussType = "FTDecayFunction1DGauss";
const QString FTDecayFunction1DTriangleType = "FTDecayFunction1DTriangle";
const QString FTDecayFunction1DVoigtType = "FTDecayFunction1DVoigt";

const QString FTDecayFunction2DCauchyType = "FTDecayFunction2DCauchy";
const QString FTDecayFunction2DGaussType = "FTDecayFunction2DGauss";
const QString FTDecayFunction2DVoigtType = "FTDecayFunction2DVoigt";

const QString BasicLatticeType = "BasicLattice";
const QString SquareLatticeType = "SquareLattice";
const QString HexagonalLatticeType = "HexagonalLattice";

const QString MaterialType = "Material";
const QString MaterialContainerType = "MaterialContainer";

const QString MaterialRefractiveDataType = "MaterialRefractiveData";
const QString MaterialSLDDataType = "MaterialSLDData";

const QString MagneticFieldType = "MagneticField";

const QString ParameterContainerType = "Parameter Container";
const QString ParameterType = "Parameter";
const QString ParameterLabelType = "Parameter Label";

const QString FitParameterContainerType = "FitParameterContainer";
const QString FitParameterType = "FitParameter";
const QString FitParameterLinkType = "FitParameterLink";
const QString FitSuiteType = "FitSuite";

const QString JobItemType = "JobItem";
const QString IntensityDataType = "IntensityData";
const QString SpecularDataType = "SpecularData";
const QString Data1DViewItemType = "Data1DViewItem";
const QString DataPropertyContainerType = "DataPropertyContainer";
const QString DataItem1DPropertiesType = "DataItem1DProperties";

const QString BasicAxisType = "BasicAxis";
const QString PointwiseAxisType = "PointwiseAxis";
const QString AmplitudeAxisType = "AmplitudeAxis";

const QString BeamDistributionType = "BeamDistribution";
const QString BeamWavelengthType = "BeamWavelength";
const QString BeamAzimuthalAngleType = "BeamAzimuthalAngle";
const QString BeamInclinationAngleType = "BeamInclinationAngle";
const QString SpecularBeamInclinationType = "SpecularBeamInclinationAxis";
const QString SpecularBeamWavelengthType = "SpecularBeamWavelength";

const QString ResolutionFunctionNoneType = "ResolutionFunctionNone";
const QString ResolutionFunction2DGaussianType = "ResolutionFunction2DGaussian";

const QString MaskContainerType = "MaskContainer";
const QString RectangleMaskType = "RectangleMask";
const QString PolygonMaskType = "PolygonMask";
const QString PolygonPointType = "PolygonPoint";
const QString EllipseMaskType = "EllipseMask";
const QString VerticalLineMaskType = "VerticalLineMask";
const QString HorizontalLineMaskType = "HorizontalLineMask";
const QString MaskAllType = "MaskAllMask";

const QString RegionOfInterestType = "RegionOfInterest";

const QString SimulationOptionsType = "SimulationOptions";

const QString RealDataType = "RealData";

const QString MinimizerContainerType = "MinimizerContainer";
const QString MinuitMinimizerType = "Minuit2";
const QString GSLMultiMinimizerType = "GSLMultiMin";
const QString GSLLMAMinimizerType = "GSLLMA";
const QString GSLSimAnMinimizerType = "GSLSimAn";
const QString GeneticMinimizerType = "Genetic";
const QString TestMinimizerType = "Test";

const QString RealLimitsLimitlessType = "RealLimitsLimitless";
const QString RealLimitsPositiveType = "RealLimitsPositive";
const QString RealLimitsNonnegativeType = "RealLimitsNonnegative";
const QString RealLimitsLowerLimitedType = "RealLimitsLowerLimited";
const QString RealLimitsUpperLimitedType = "RealLimitsUpperLimited";
const QString RealLimitsLimitedType = "RealLimitsLimited";

const QString ProjectionContainerType = "ProjectionContainer";

const QString BackgroundNoneType = "NoBackground";
const QString ConstantBackgroundType = "ConstantBackground";
const QString PoissonNoiseBackgroundType = "PoissonNoiseBackground";

const QString FootprintNoneType = "NoFootprint";
const QString FootprintGaussianType = "GaussianFootrpint";
const QString FootprintSquareType = "SquareFootprint";

const QString VarianceConstantFunctionType = "VarianceConstantFunction";
const QString VarianceSimFunctionType = "VarianceSimFunction";

// --- Groups ------------------------------------------------------------------

const QString FormFactorGroup = "Form Factor";
const QString RotationGroup = "Rotation group";
const QString LayerRoughnessGroup = "Roughness";
const QString DetectorGroup = "Detector group";
const QString DistributionGroup = "Distribution group";
const QString DistributionExtendedGroup = "Distribution extended group";
const QString SymmetricDistributionGroup = "Symmetric distribution group";
const QString FTDistribution1DGroup = "PDF 1D";
const QString FTDistribution2DGroup = "PDF 2D";
const QString FTDecayFunction1DGroup = "Decay function 1D";
const QString FTDecayFunction2DGroup = "Decay function 2D";
const QString LatticeGroup = "Lattice group";
const QString MaterialGroup = "Material group";
const QString ResolutionFunctionGroup = "Resolution function group";
const QString MinimizerLibraryGroup = "Minimizer library group";
const QString RealLimitsGroup = "RealLimits group";
const QString BackgroundGroup = "Background group";
const QString MaterialDataGroup = "Material data group";
const QString FootprintGroup = "Footprint group";
const QString AxesGroup = "Axes group";
const QString VarianceFunctionGroup = "Variance group";

// --- Units&Constants----------------------------------------------------------

const QString UnitsNbins = "nbins";
const QString UnitsRadians = "Radians";
const QString UnitsDegrees = "Degrees";
const QString UnitsMm = "mm";
const QString UnitsQyQz = "q-space";

const QString STATUS_IDLE = "Idle";
const QString STATUS_RUNNING = "Running";
const QString STATUS_FITTING = "Fitting";
const QString STATUS_COMPLETED = "Completed";
const QString STATUS_CANCELED = "Canceled";
const QString STATUS_FAILED = "Failed";

const QString GRADIENT_GRAYSCALE = "Grayscale";
const QString GRADIENT_HOT = "Hot";
const QString GRADIENT_COLD = "Cold";
const QString GRADIENT_NIGHT = "Night";
const QString GRADIENT_CANDY = "Candy";
const QString GRADIENT_GEOGRAPHY = "Geography";
const QString GRADIENT_ION = "Ion";
const QString GRADIENT_THERMAL = "Thermal";
const QString GRADIENT_POLAR = "Polar";
const QString GRADIENT_SPECTRUM = "Spectrum";
const QString GRADIENT_JET = "Jet";
const QString GRADIENT_HUES = "Hues";

const QString JOB_RUN_IMMEDIATELY = "Immediately";
const QString JOB_RUN_IN_BACKGROUND = "In background";
const QString JOB_BACKUP = "_backup";

const QString SIMULATION_ANALYTICAL = "Analytical";
const QString SIMULATION_MONTECARLO = "Monte-Carlo Integration";

const QString ALIGNMENT_GENERIC = "Generic";
const QString ALIGNMENT_TO_SAMPLE = "Perpendicular to sample x-axis";
const QString ALIGNMENT_TO_DIRECT_BEAM = "Perpendicular to direct beam";
const QString ALIGNMENT_TO_REFLECTED_BEAM = "Perpendicular to reflected beam";
const QString ALIGNMENT_TO_REFLECTED_BEAM_DPOS = "Perpendicular to reflected beam (dpos)";

const QString FITPAR_FIXED = "fixed";
const QString FITPAR_LIMITED = "limited";
const QString FITPAR_LOWERLIMITED = "lower limited";
const QString FITPAR_UPPERLIMITED = "upper limited";
const QString FITPAR_FREE = "free";

const QString DistributionSigmaFactor = "Sigma factor";

const QString LAYOUT_DA = "Decoupling Approximation";
const QString LAYOUT_SSCA = "Size Space Coupling Approximation";

const QString AMBIENT_LAYER_MATERIAL = "Ambient Layer Material";
const QString AVERAGE_LAYER_MATERIAL = "Average Layer Material";

// --- Presentation types ----------------------------------------------------------

const QString IntensityDataPresentation = "Color Map";
const QString SpecularDataPresentation = "Reflectometry";
const QString IntensityProjectionsPresentation = "Projections";
const QString FitComparisonPresentation2D = "Fit 2D Data";
const QString FitComparisonPresentation1D = "Fit 1D Data";
const QString MaskEditorPresentation = "Mask Editor";

// --- Custom variants ----------------------------------------------------------

const QString ExternalPropertyType = "ExternalProperty";
const QString ComboPropertyType = "ComboProperty";

// --- Custom editors for variant properties ---
const QString DefaultEditorType = "Default";
const QString ScientificEditorType = "SceintificDouble";
const QString ScientificSpinBoxType = "ScientificSpinBox";
const QString MaterialEditorExternalType = "ExtMaterialEditor";
const QString ColorEditorExternalType = "ExtColorEditor";
const QString MultiSelectionComboEditorType = "MultiSelectionComboEditor";

} // namespace Constants

#endif // ITEM_CONSTANTS_H
