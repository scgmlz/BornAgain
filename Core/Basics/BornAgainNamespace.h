// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/BornAgainNamespace.h
//! @brief     Defines BornAgain namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BORNAGAINNAMESPACE_H
#define BORNAGAINNAMESPACE_H

#include <string>

//! Mostly names of classes and parameters.

namespace BornAgain
{
// Axis constants
const std::string PHI_AXIS_NAME = "phi_f";
const std::string ALPHA_AXIS_NAME = "alpha_f";
const std::string U_AXIS_NAME = "u";
const std::string V_AXIS_NAME = "v";
const size_t X_AXIS_INDEX = 0;
const size_t Y_AXIS_INDEX = 1;

// Simulation types
const std::string GISASSimulationType = "GISASSimulation";
const std::string OffSpecSimulationType = "OffSpecSimulation";

// Instrument related constants
const std::string InstrumentType = "Instrument";
const std::string ResolutionFunction2D = "ResolutionFunction2D";
const std::string DetectorType = "Detector";
const std::string SphericalDetectorType = "SphericalDetector";
const std::string RectangularDetectorType = "RectangularDetector";
const std::string IsGISAXSDetectorType = "IsGISAXSDetector";
const std::string BeamType = "Beam";

// ISample object types
const std::string MultiLayerType = "MultiLayer";
const std::string LayerType = "Layer";
const std::string LayerInterfaceType = "LayerInterface";
const std::string ParticleLayoutType = "ParticleLayout";
const std::string ParticleType = "Particle";
const std::string ParticleCoreShellType = "ParticleCoreShell";
const std::string ParticleDistributionType = "ParticleDistribution";
const std::string ParticleCompositionType = "ParticleComposition";
const std::string TransformationType = "Rotation";

const std::string LayerBasicRoughnessType = "LayerBasicRoughness";
const std::string LayerZeroRoughnessType = "LayerZeroRoughness";

const std::string InterferenceFunctionNoneType = "InterferenceNone";
const std::string InterferenceFunctionRadialParaCrystalType = "InterferenceRadialParaCrystal";
const std::string InterferenceFunction2DParaCrystalType = "Interference2DParaCrystal";
const std::string InterferenceFunction1DLatticeType = "Interference1DLattice";
const std::string InterferenceFunction2DLatticeType = "Interference2DLattice";

const std::string CrystalType = "Crystal";
const std::string MesoCrystalType = "MesoCrystal";

const std::string FFAnisoPyramidType = "AnisoPyramid";
const std::string FFBoxType = "Box";
const std::string FFConeType = "Cone";
const std::string FFCone6Type = "Cone6";
const std::string FFCuboctahedronType = "Cuboctahedron";
const std::string FFCylinderType = "Cylinder";
const std::string FFDodecahedronType = "Dodecahedron";
const std::string FFEllipsoidalCylinderType = "EllipsoidalCylinder";
const std::string FFFullSphereType = "FullSphere";
const std::string FFFullSpheroidType = "FullSpheroid";
const std::string FFGaussType = "FormFactorGauss";
const std::string FFHemiEllipsoidType = "HemiEllipsoid";
const std::string FFLongBoxGaussType = "FormFactorLongBoxGauss";
const std::string FFIcosahedronType = "Icosahedron";
const std::string FFLongBoxLorentzType = "FormFactorLongBoxLorentz";
const std::string FFLorentzType = "FormFactorLorentz";
const std::string FFPrism3Type = "Prism3";
const std::string FFPrism6Type = "Prism6";
const std::string FFPyramidType = "Pyramid";
const std::string FFRipple1Type = "Ripple1";
const std::string FFRipple2Type = "Ripple2";
const std::string FFLongRipple1GaussType = "LongRipple1Gauss";
const std::string FFLongRipple1LorentzType = "LongRipple1Lorentz";
const std::string FFLongRipple2GaussType = "LongRipple2Gauss";
const std::string FFLongRipple2LorentzType = "LongRipple2Lorentz";
const std::string FFTetrahedronType = "Tetrahedron";
const std::string FFTruncatedCubeType = "TruncatedCube";
const std::string FFTruncatedSphereType = "TruncatedSphere";
const std::string FFTruncatedSpheroidType = "TruncatedSpheroid";

const std::string FormFactorCrystalType = "FormFactorCrystal";
const std::string FormFactorSphereGaussianRadiusType = "FormFactorSphereGaussianRadius";
const std::string FormFactorSphereLogNormalRadiusType = "FormFactorSphereLogNormalRadius";
const std::string FormFactorSphereUniformRadiusType = "FormFactorSphereUniformRadius";
const std::string FormFactorTrivialType = "FormFactorTrivial";
const std::string FormFactorDWBAType = "FormFactorDWBA";
const std::string FormFactorPolarizedDWBAType = "FormFactorDWBAPol";

const std::string FormFactorDecoratorFactorType = "FormFactorDecoratorFactor";
const std::string FormFactorDecoratorPositionFactorType = "FormFactorDecoratorPositionFactor";
const std::string FormFactorDecoratorRotationType = "FormFactorDecoratorRotation";
const std::string FormFactorDecoratorDebyeWallerType = "FormFactorDecoratorDebyeWaller";
const std::string FormFactorDecoratorMaterialType = "FormFactorDecoratorMaterial";
const std::string FormFactorWeightedType = "FormFactorWeighted";

const std::string XRotationType = "XRotation";
const std::string YRotationType = "YRotation";
const std::string ZRotationType = "ZRotation";
const std::string EulerRotationType = "EulerRotation";

const std::string DistributionNoneType = "DistributionNone";
const std::string DistributionGateType = "DistributionGate";
const std::string DistributionLorentzType = "DistributionLorentz";
const std::string DistributionGaussianType = "DistributionGaussian";
const std::string DistributionLogNormalType = "DistributionLogNormal";
const std::string DistributionCosineType = "DistributionCosine";

const std::string FTDistribution1DCauchyType = "FTDistribution1DCauchy";
const std::string FTDistribution1DGaussType = "FTDistribution1DGauss";
const std::string FTDistribution1DGateType = "FTDistribution1DGate";
const std::string FTDistribution1DTriangleType = "FTDistribution1DTriangle";
const std::string FTDistribution1DCosineType = "FTDistribution1DCosine";
const std::string FTDistribution1DVoigtType = "FTDistribution1DVoigt";

const std::string FTDistribution2DCauchyType = "FTDistribution2DCauchy";
const std::string FTDistribution2DGaussType = "FTDistribution2DGauss";
const std::string FTDistribution2DGateType = "FTDistribution2DGate";
const std::string FTDistribution2DConeType = "FTDistribution2DCone";
const std::string FTDistribution2DVoigtType = "FTDistribution2DVoigt";

const std::string FTDecayFunction1DCauchyType = "FTDecayFunction1DCauchy";
const std::string FTDecayFunction1DGaussType = "FTDecayFunction1DGauss";
const std::string FTDecayFunction1DTriangleType = "FTDecayFunction1DTriangle";
const std::string FTDecayFunction1DVoigtType = "FTDecayFunction1DVoigt";

const std::string FTDecayFunction2DCauchyType = "FTDecayFunction2DCauchy";
const std::string FTDecayFunction2DGaussType = "FTDecayFunction2DGauss";
const std::string FTDecayFunction2DVoigtType = "FTDecayFunction2DVoigt";

// Parameter names (dimensions, angles, ...)
const std::string Abundance = "Abundance";
const std::string PositionX = "PositionX";
const std::string PositionY = "PositionY";
const std::string PositionZ = "PositionZ";
const std::string Radius = "Radius";
const std::string RadiusX = "RadiusX";
const std::string RadiusY = "RadiusY";
const std::string MeanRadius = "MeanRadius";
const std::string SigmaRadius = "SigmaRadius";
const std::string FullWidth = "FullWidth";
const std::string Edge = "Edge";
const std::string BaseEdge = "BaseEdge";
const std::string Length = "Length";
const std::string RemovedLength = "RemovedLength";
const std::string Width = "Width";
const std::string Height = "Height";
const std::string HeightRatio = "HeightRatio";
const std::string HeightFlattening = "HeightFlattening";
const std::string Intensity = "Intensity";
const std::string Wavelength = "Wavelength";
const std::string Angle = "Angle";
const std::string Alpha = "Alpha";
const std::string Beta = "Beta";
const std::string Gamma = "Gamma";
const std::string Delta = "Delta";
const std::string Phi = "Phi";
const std::string Xi = "Xi";
const std::string Minimum = "Min";
const std::string Maximum = "Max";
const std::string Mean = "Mean";
const std::string StdDeviation = "StdDev";
const std::string HWHM = "HWHM";
const std::string Median = "Median";
const std::string ScaleParameter = "ScaleParameter";
const std::string Sigma = "Sigma";
const std::string Eta = "Eta";
const std::string Omega = "Omega";
const std::string DecayLength = "DecayLength";
const std::string DecayLengthX = "DecayLengthX";
const std::string DecayLengthY = "DecayLengthY";
const std::string CoherenceLengthX = "CoherenceLengthX";
const std::string CoherenceLengthY = "CoherenceLengthY";
const std::string SigmaX = "SigmaX";
const std::string SigmaY = "SigmaY";
const std::string HeightDWFactor = "HeightDWFactor";
const std::string RadiusDWFactor = "RadiusDWFactor";
const std::string AsymmetryLength = "AsymmetryLength";
const std::string LatticeLength = "LatticeLength";
const std::string LatticeLength1 = "LatticeLength1";
const std::string LatticeLength2 = "LatticeLength2";
const std::string LatticeAngle = "Alpha";
const std::string DampingLength = "DampingLength";
const std::string DomainSize = "DomainSize";
const std::string DomainSize1 = "DomainSize1";
const std::string DomainSize2 = "DomainSize2";
const std::string PeakDistance = "PeakDistance";
const std::string SizeSpaceCoupling = "SizeSpaceCoupling";
const std::string Thickness = "Thickness";
const std::string Hurst = "Hurst";
const std::string CorrelationLength = "CorrelationLength";
const std::string CrossCorrelationLength = "CrossCorrelationLength";
const std::string Inclination = "InclinationAngle";
const std::string Azimuth = "AzimuthalAngle";
}

#endif // BORNAGAINNAMESPACE_H
