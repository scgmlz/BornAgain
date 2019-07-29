// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupInfoCatalogue.cpp
//! @brief     Implements class GroupInfoCatalogue
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GroupInfoCatalogue.h"
#include "item_constants.h"
#include "GUIHelpers.h"

GroupInfoCatalogue::GroupInfoCatalogue()
{
    GroupInfo info(Constants::FormFactorGroup);
    info.add(Constants::AnisoPyramidType, "Aniso Pyramid");
    info.add(Constants::BoxType, "Box");
    info.add(Constants::ConeType, "Cone");
    info.add(Constants::Cone6Type, "Cone6");
    info.add(Constants::CuboctahedronType, "Cuboctahedron");
    info.add(Constants::CylinderType, "Cylinder");
    info.add(Constants::DodecahedronType, "Dodecahedron");
    info.add(Constants::DotType, "Dot");
    info.add(Constants::EllipsoidalCylinderType, "Ellipsoidal Cylinder");
    info.add(Constants::FullSphereType, "Full Sphere");
    info.add(Constants::FullSpheroidType, "Full Spheroid");
    info.add(Constants::HemiEllipsoidType, "Hemi Ellipsoid");
    info.add(Constants::IcosahedronType, "Icosahedron");
    info.add(Constants::Prism3Type, "Prism3");
    info.add(Constants::Prism6Type, "Prism6");
    info.add(Constants::PyramidType, "Pyramid");
    info.add(Constants::Ripple1Type, "Ripple1");
    info.add(Constants::Ripple2Type, "Ripple2");
    info.add(Constants::TetrahedronType, "Tetrahedron");
    info.add(Constants::TruncatedCubeType, "Truncated Cube");
    info.add(Constants::TruncatedSphereType, "Truncated Sphere");
    info.add(Constants::TruncatedSpheroidType, "Truncated Spheroid");
    info.setDefaultType(Constants::CylinderType);
    addInfo(info);

    info = GroupInfo(Constants::RotationGroup);
    info.add(Constants::XRotationType, "X axis Rotation");
    info.add(Constants::YRotationType, "Y axis Rotation");
    info.add(Constants::ZRotationType, "Z axis Rotation");
    info.add(Constants::EulerRotationType, "Euler Rotation");
    info.setDefaultType(Constants::ZRotationType);
    addInfo(info);

    info = GroupInfo(Constants::LayerRoughnessGroup);
    info.add(Constants::LayerBasicRoughnessType, "Basic");
    info.add(Constants::LayerZeroRoughnessType, "No");
    info.setDefaultType(Constants::LayerZeroRoughnessType);
    addInfo(info);

    info = GroupInfo(Constants::DetectorGroup);
    info.add(Constants::SphericalDetectorType, "Spherical detector");
    info.add(Constants::RectangularDetectorType, "Rectangular detector");
    info.setDefaultType(Constants::SphericalDetectorType);
    addInfo(info);

    info = GroupInfo(Constants::DistributionGroup);
    info.add(Constants::DistributionGateType, "Gate distribution");
    info.add(Constants::DistributionLorentzType, "Lorentz distribution");
    info.add(Constants::DistributionGaussianType, "Gaussian distribution");
    info.add(Constants::DistributionLogNormalType, "Log Normal distribution");
    info.add(Constants::DistributionCosineType, "Cosine distribution");
    info.add(Constants::DistributionTrapezoidType, "Trapezoid distribution");
    info.setDefaultType(Constants::DistributionGaussianType);
    addInfo(info);

    info = GroupInfo(Constants::DistributionExtendedGroup);
    info.add(Constants::DistributionNoneType, "None");
    info.add(Constants::DistributionGateType, "Gate");
    info.add(Constants::DistributionLorentzType, "Lorentz");
    info.add(Constants::DistributionGaussianType, "Gaussian");
    info.add(Constants::DistributionLogNormalType, "Log Normal");
    info.add(Constants::DistributionCosineType, "Cosine");
    info.add(Constants::DistributionTrapezoidType, "Trapezoid");
    info.setDefaultType(Constants::DistributionNoneType);
    addInfo(info);

    info = GroupInfo(Constants::SymmetricDistributionGroup);
    info.add(Constants::DistributionNoneType, "None");
    info.add(Constants::DistributionLorentzType, "Lorentz");
    info.add(Constants::DistributionGaussianType, "Gaussian");
    info.add(Constants::DistributionCosineType, "Cosine");
    info.setDefaultType(Constants::DistributionNoneType);
    addInfo(info);

    info = GroupInfo(Constants::FTDistribution1DGroup);
    info.add(Constants::FTDistribution1DCauchyType, "Cauchy 1D");
    info.add(Constants::FTDistribution1DGaussType, "Gauss 1D");
    info.add(Constants::FTDistribution1DGateType, "Gate 1D");
    info.add(Constants::FTDistribution1DTriangleType, "Triangle 1D");
    info.add(Constants::FTDistribution1DCosineType, "Cosine 1D");
    info.add(Constants::FTDistribution1DVoigtType, "Voigt 1D");
    info.setDefaultType(Constants::FTDistribution1DCauchyType);
    addInfo(info);

    info = GroupInfo(Constants::FTDistribution2DGroup);
    info.add(Constants::FTDistribution2DCauchyType, "Cauchy 2D");
    info.add(Constants::FTDistribution2DGaussType, "Gauss 2D");
    info.add(Constants::FTDistribution2DGateType, "Gate 2D");
    info.add(Constants::FTDistribution2DConeType, "Cone 2D");
    info.add(Constants::FTDistribution2DVoigtType, "Voigt 2D");
    info.setDefaultType(Constants::FTDistribution2DCauchyType);
    addInfo(info);

    info = GroupInfo(Constants::FTDecayFunction1DGroup);
    info.add(Constants::FTDecayFunction1DCauchyType, "Cauchy 1D");
    info.add(Constants::FTDecayFunction1DGaussType, "Gauss 1D");
    info.add(Constants::FTDecayFunction1DTriangleType, "Triangle 1D");
    info.add(Constants::FTDecayFunction1DVoigtType, "Voigt 1D");
    info.setDefaultType(Constants::FTDecayFunction1DCauchyType);
    addInfo(info);

    info = GroupInfo(Constants::FTDecayFunction2DGroup);
    info.add(Constants::FTDecayFunction2DCauchyType, "Cauchy 2D");
    info.add(Constants::FTDecayFunction2DGaussType, "Gauss 2D");
    info.add(Constants::FTDecayFunction2DVoigtType, "Voigt 2D");
    info.setDefaultType(Constants::FTDecayFunction2DCauchyType);
    addInfo(info);

    info = GroupInfo(Constants::LatticeGroup);
    info.add(Constants::BasicLatticeType, "Basic");
    info.add(Constants::SquareLatticeType, "Square");
    info.add(Constants::HexagonalLatticeType, "Hexagonal");
    info.setDefaultType(Constants::HexagonalLatticeType);
    addInfo(info);

    info = GroupInfo(Constants::ResolutionFunctionGroup);
    info.add(Constants::ResolutionFunctionNoneType, "None");
    info.add(Constants::ResolutionFunction2DGaussianType, "2D Gaussian");
    info.setDefaultType(Constants::ResolutionFunctionNoneType);
    addInfo(info);

    info = GroupInfo(Constants::MinimizerLibraryGroup);
    info.add(Constants::MinuitMinimizerType, "Minuit2");
    info.add(Constants::GSLMultiMinimizerType, "GSL MultiMin");
    info.add(Constants::GeneticMinimizerType, "TMVA Genetic");
    info.add(Constants::GSLSimAnMinimizerType, "GSL Simulated Annealing");
    info.add(Constants::GSLLMAMinimizerType, "GSL Levenberg-Marquardt");
    info.add(Constants::TestMinimizerType, "Test minimizer");
    info.setDefaultType(Constants::MinuitMinimizerType);
    addInfo(info);

    info = GroupInfo(Constants::RealLimitsGroup);
    info.add(Constants::RealLimitsLimitlessType, "Unlimited");
    info.add(Constants::RealLimitsPositiveType, "Positive");
    info.add(Constants::RealLimitsNonnegativeType, "Nonnegative");
    info.add(Constants::RealLimitsLowerLimitedType, "LowerLimited");
    info.add(Constants::RealLimitsUpperLimitedType, "UpperLimited");
    info.add(Constants::RealLimitsLimitedType, "Limited");
    info.setDefaultType(Constants::RealLimitsLimitlessType);
    addInfo(info);

    info = GroupInfo(Constants::BackgroundGroup);
    info.add(Constants::BackgroundNoneType, "None");
    info.add(Constants::ConstantBackgroundType, "Constant background");
    info.add(Constants::PoissonNoiseBackgroundType, "Poisson noise");
    info.setDefaultType(Constants::BackgroundNoneType);
    addInfo(info);

    info = GroupInfo(Constants::MaterialDataGroup);
    info.add(Constants::MaterialRefractiveDataType, "Refractive index based");
    info.add(Constants::MaterialSLDDataType, "SLD based");
    info.setDefaultType(Constants::MaterialRefractiveDataType);
    addInfo(info);

    info = GroupInfo(Constants::FootprintGroup);
    info.add(Constants::FootprintNoneType, "None");
    info.add(Constants::FootprintGaussianType, "Gaussian footprint");
    info.add(Constants::FootprintSquareType, "Square footprint");
    info.setDefaultType(Constants::FootprintNoneType);
    addInfo(info);

    info = GroupInfo(Constants::AxesGroup);
    info.add(Constants::BasicAxisType, "Uniform axis");
    info.add(Constants::PointwiseAxisType, "Non-uniform axis");
    info.setDefaultType(Constants::BasicAxisType);
    addInfo(info);

    info = GroupInfo(Constants::VarianceFunctionGroup);
    info.add(Constants::VarianceSimFunctionType, "Simulation value based");
    info.add(Constants::VarianceConstantFunctionType, "Constant");
    info.setDefaultType(Constants::VarianceSimFunctionType);
    addInfo(info);
}

GroupInfo GroupInfoCatalogue::groupInfo(const QString& groupType) const
{
    for (auto& info : m_groups)
        if (info.groupType() == groupType)
            return info;

    throw GUIHelpers::Error("GroupInfoCatalogue::groupInfo() -> Error. No such group '"+
                            groupType+"'");
}

bool GroupInfoCatalogue::containsGroup(const QString& groupType) const
{
    for (auto& info : m_groups)
        if (info.groupType() == groupType)
            return true;

    return false;
}

void GroupInfoCatalogue::addInfo(const GroupInfo& info)
{
    if (containsGroup(info.groupType()))
        throw GUIHelpers::Error("GroupInfoCatalogue::addInfo -> Error. Already exists '"
                                + info.groupType() + "'");

    m_groups.push_back(info);
}
