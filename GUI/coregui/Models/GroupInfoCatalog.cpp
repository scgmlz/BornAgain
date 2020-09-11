// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupInfoCatalog.cpp
//! @brief     Implements class GroupInfoCatalog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/GroupInfoCatalog.h"
#include "GUI/coregui/utils/GUIHelpers.h"

GroupInfoCatalog::GroupInfoCatalog()
{
    GroupInfo info("Form Factor");
    info.add("AnisoPyramid", "Aniso Pyramid");
    info.add("BarGauss", "BarGauss");
    info.add("BarLorentz", "BarLorentz");
    info.add("Box", "Box");
    info.add("Cone", "Cone");
    info.add("Cone6", "Cone6");
    info.add("Cuboctahedron", "Cuboctahedron");
    info.add("Cylinder", "Cylinder");
    info.add("Dodecahedron", "Dodecahedron");
    info.add("Dot", "Dot");
    info.add("EllipsoidalCylinder", "Ellipsoidal Cylinder");
    info.add("FullSphere", "Full Sphere");
    info.add("FullSpheroid", "Full Spheroid");
    info.add("HemiEllipsoid", "Hemi Ellipsoid");
    info.add("Icosahedron", "Icosahedron");
    info.add("Prism3", "Prism3");
    info.add("Prism6", "Prism6");
    info.add("Pyramid", "Pyramid");
    info.add("CosineRippleBox", "CosineRippleBox");
    info.add("CosineRippleGauss", "CosineRippleGauss");
    info.add("CosineRippleLorentz", "CosineRippleLorentz");
    info.add("SawtoothRippleBox", "SawtoothRippleBox");
    info.add("SawtoothRippleGauss", "SawtoothRippleGauss");
    info.add("SawtoothRippleLorentz", "SawtoothRippleLorentz");
    info.add("Tetrahedron", "Tetrahedron");
    info.add("TruncatedCube", "Truncated Cube");
    info.add("TruncatedSphere", "Truncated Sphere");
    info.add("TruncatedSpheroid", "Truncated Spheroid");
    info.setDefaultType("Cylinder");
    addInfo(info);

    info = GroupInfo("Rotation group");
    info.add("XRotation", "X axis Rotation");
    info.add("YRotation", "Y axis Rotation");
    info.add("ZRotation", "Z axis Rotation");
    info.add("EulerRotation", "Euler Rotation");
    info.setDefaultType("ZRotation");
    addInfo(info);

    info = GroupInfo("Roughness");
    info.add("LayerBasicRoughness", "Basic");
    info.add("LayerZeroRoughness", "No");
    info.setDefaultType("LayerZeroRoughness");
    addInfo(info);

    info = GroupInfo("Detector group");
    info.add("SphericalDetector", "Spherical detector");
    info.add("RectangularDetector", "Rectangular detector");
    info.setDefaultType("SphericalDetector");
    addInfo(info);

    info = GroupInfo("Distribution group");
    info.add("DistributionGate", "Gate distribution");
    info.add("DistributionLorentz", "Lorentz distribution");
    info.add("DistributionGaussian", "Gaussian distribution");
    info.add("DistributionLogNormal", "Log Normal distribution");
    info.add("DistributionCosine", "Cosine distribution");
    info.add("DistributionTrapezoid", "Trapezoid distribution");
    info.setDefaultType("DistributionGaussian");
    addInfo(info);

    info = GroupInfo("Distribution extended group");
    info.add("DistributionNone", "None");
    info.add("DistributionGate", "Gate");
    info.add("DistributionLorentz", "Lorentz");
    info.add("DistributionGaussian", "Gaussian");
    info.add("DistributionLogNormal", "Log Normal");
    info.add("DistributionCosine", "Cosine");
    info.add("DistributionTrapezoid", "Trapezoid");
    info.setDefaultType("DistributionNone");
    addInfo(info);

    info = GroupInfo("Symmetric distribution group");
    info.add("DistributionNone", "None");
    info.add("DistributionLorentz", "Lorentz");
    info.add("DistributionGaussian", "Gaussian");
    info.add("DistributionCosine", "Cosine");
    info.setDefaultType("DistributionNone");
    addInfo(info);

    info = GroupInfo("PDF 1D");
    info.add("FTDistribution1DCauchy", "Cauchy 1D");
    info.add("FTDistribution1DGauss", "Gauss 1D");
    info.add("FTDistribution1DGate", "Gate 1D");
    info.add("FTDistribution1DTriangle", "Triangle 1D");
    info.add("FTDistribution1DCosine", "Cosine 1D");
    info.add("FTDistribution1DVoigt", "Voigt 1D");
    info.setDefaultType("FTDistribution1DCauchy");
    addInfo(info);

    info = GroupInfo("PDF 2D");
    info.add("FTDistribution2DCauchy", "Cauchy 2D");
    info.add("FTDistribution2DGauss", "Gauss 2D");
    info.add("FTDistribution2DGate", "Gate 2D");
    info.add("FTDistribution2DCone", "Cone 2D");
    info.add("FTDistribution2DVoigt", "Voigt 2D");
    info.setDefaultType("FTDistribution2DCauchy");
    addInfo(info);

    info = GroupInfo("Decay function 1D");
    info.add("FTDecayFunction1DCauchy", "Cauchy 1D");
    info.add("FTDecayFunction1DGauss", "Gauss 1D");
    info.add("FTDecayFunction1DTriangle", "Triangle 1D");
    info.add("FTDecayFunction1DVoigt", "Voigt 1D");
    info.setDefaultType("FTDecayFunction1DCauchy");
    addInfo(info);

    info = GroupInfo("Decay function 2D");
    info.add("FTDecayFunction2DCauchy", "Cauchy 2D");
    info.add("FTDecayFunction2DGauss", "Gauss 2D");
    info.add("FTDecayFunction2DVoigt", "Voigt 2D");
    info.setDefaultType("FTDecayFunction2DCauchy");
    addInfo(info);

    info = GroupInfo("Lattice group");
    info.add("BasicLattice", "Basic");
    info.add("SquareLattice", "Square");
    info.add("HexagonalLattice", "Hexagonal");
    info.setDefaultType("HexagonalLattice");
    addInfo(info);

    info = GroupInfo("Resolution function group");
    info.add("ResolutionFunctionNone", "None");
    info.add("ResolutionFunction2DGaussian", "2D Gaussian");
    info.setDefaultType("ResolutionFunctionNone");
    addInfo(info);

    info = GroupInfo("Minimizer library group");
    info.add("Minuit2", "Minuit2");
    info.add("GSLMultiMin", "GSL MultiMin");
    info.add("Genetic", "TMVA Genetic");
    info.add("GSLSimAn", "GSL Simulated Annealing");
    info.add("GSLLMA", "GSL Levenberg-Marquardt");
    info.add("Test", "Test minimizer");
    info.setDefaultType("Minuit2");
    addInfo(info);

    info = GroupInfo("RealLimits group");
    info.add("RealLimitsLimitless", "Unlimited");
    info.add("RealLimitsPositive", "Positive");
    info.add("RealLimitsNonnegative", "Nonnegative");
    info.add("RealLimitsLowerLimited", "LowerLimited");
    info.add("RealLimitsUpperLimited", "UpperLimited");
    info.add("RealLimitsLimited", "Limited");
    info.setDefaultType("RealLimitsLimitless");
    addInfo(info);

    info = GroupInfo("Background group");
    info.add("NoBackground", "None");
    info.add("ConstantBackground", "Constant background");
    info.add("PoissonNoiseBackground", "Poisson noise");
    info.setDefaultType("NoBackground");
    addInfo(info);

    info = GroupInfo("Material data group");
    info.add("MaterialRefractiveData", "Refractive index based");
    info.add("MaterialSLDData", "SLD based");
    info.setDefaultType("MaterialRefractiveData");
    addInfo(info);

    info = GroupInfo("Footprint group");
    info.add("NoFootprint", "None");
    info.add("GaussianFootrpint", "Gaussian footprint");
    info.add("SquareFootprint", "Square footprint");
    info.setDefaultType("NoFootprint");
    addInfo(info);

    info = GroupInfo("Axes group");
    info.add("BasicAxis", "Uniform axis");
    info.add("PointwiseAxis", "Non-uniform axis");
    info.setDefaultType("BasicAxis");
    addInfo(info);

    info = GroupInfo("Variance group");
    info.add("VarianceSimFunction", "Simulation value based");
    info.add("VarianceConstantFunction", "Constant");
    info.setDefaultType("VarianceSimFunction");
    addInfo(info);
}

GroupInfo GroupInfoCatalog::groupInfo(const QString& groupType) const
{
    for (auto& info : m_groups)
        if (info.groupType() == groupType)
            return info;

    throw GUIHelpers::Error("GroupInfoCatalog::groupInfo() -> Error. No such group '" + groupType
                            + "'");
}

bool GroupInfoCatalog::containsGroup(const QString& groupType) const
{
    for (auto& info : m_groups)
        if (info.groupType() == groupType)
            return true;

    return false;
}

void GroupInfoCatalog::addInfo(const GroupInfo& info)
{
    if (containsGroup(info.groupType()))
        throw GUIHelpers::Error("GroupInfoCatalog::addInfo -> Error. Already exists '"
                                + info.groupType() + "'");

    m_groups.push_back(info);
}
