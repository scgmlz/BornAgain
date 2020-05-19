// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ItemCatalogue.cpp
//! @brief     Implements class ItemCatalogue
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ItemCatalogue.h"
#include "AxesItems.h"
#include "BackgroundItems.h"
#include "BeamAngleItems.h"
#include "BeamItems.h"
#include "BeamWavelengthItem.h"
#include "Data1DViewItem.h"
#include "DataProperties.h"
#include "DataPropertyContainer.h"
#include "DepthProbeInstrumentItem.h"
#include "DetectorItems.h"
#include "FTDecayFunctionItems.h"
#include "FTDistributionItems.h"
#include "FitParameterItems.h"
#include "FitSuiteItem.h"
#include "FootprintItems.h"
#include "FormFactorItems.h"
#include "GUIHelpers.h"
#include "GroupItem.h"
#include "InstrumentItems.h"
#include "IntensityDataItem.h"
#include "InterferenceFunctionItems.h"
#include "JobItem.h"
#include "Lattice2DItems.h"
#include "LayerItem.h"
#include "LayerRoughnessItems.h"
#include "MaskItems.h"
#include "MaterialDataItems.h"
#include "MaterialItem.h"
#include "MaterialItemContainer.h"
#include "MesoCrystalItem.h"
#include "MinimizerItem.h"
#include "MultiLayerItem.h"
#include "ParameterTreeItems.h"
#include "ParticleCompositionItem.h"
#include "ParticleCoreShellItem.h"
#include "ParticleDistributionItem.h"
#include "ParticleItem.h"
#include "ParticleLayoutItem.h"
#include "PointwiseAxisItem.h"
#include "ProjectionItems.h"
#include "PropertyItem.h"
#include "RealDataItem.h"
#include "RealLimitsItems.h"
#include "RectangularDetectorItem.h"
#include "ResolutionFunctionItems.h"
#include "RotationItems.h"
#include "SimulationOptionsItem.h"
#include "SpecularBeamInclinationItem.h"
#include "SpecularDataItem.h"
#include "SphericalDetectorItem.h"
#include "TransformationItem.h"
#include "VectorItem.h"

ItemCatalogue::ItemCatalogue()
{
    init_top_item_types();

    add(Constants::MultiLayerType, create_new<MultiLayerItem>);
    add(Constants::LayerType, create_new<LayerItem>);
    add(Constants::ParticleLayoutType, create_new<ParticleLayoutItem>);
    add(Constants::ParticleType, create_new<ParticleItem>);
    add(Constants::RotationType, create_new<TransformationItem>);
    add(Constants::ParticleCoreShellType, create_new<ParticleCoreShellItem>);
    add(Constants::ParticleCompositionType, create_new<ParticleCompositionItem>);
    add(Constants::ParticleDistributionType, create_new<ParticleDistributionItem>);
    add(Constants::MesoCrystalType, create_new<MesoCrystalItem>);
    add(Constants::InterferenceFunction1DLatticeType,
        create_new<InterferenceFunction1DLatticeItem>);
    add(Constants::InterferenceFunction2DLatticeType,
        create_new<InterferenceFunction2DLatticeItem>);
    add(Constants::InterferenceFunction2DParaCrystalType,
        create_new<InterferenceFunction2DParaCrystalItem>);
    add(Constants::InterferenceFunctionFinite2DLatticeType,
        create_new<InterferenceFunctionFinite2DLatticeItem>);
    add(Constants::InterferenceFunctionHardDiskType, create_new<InterferenceFunctionHardDiskItem>);
    add(Constants::InterferenceFunctionRadialParaCrystalType,
        create_new<InterferenceFunctionRadialParaCrystalItem>);
    add(Constants::GISASInstrumentType, create_new<GISASInstrumentItem>);
    add(Constants::OffSpecInstrumentType, create_new<OffSpecInstrumentItem>);
    add(Constants::SpecularInstrumentType, create_new<SpecularInstrumentItem>);
    add(Constants::GISASBeamType, create_new<GISASBeamItem>);
    add(Constants::SpecularBeamType, create_new<SpecularBeamItem>);
    add(Constants::BackgroundNoneType, create_new<BackgroundNoneItem>);
    add(Constants::ConstantBackgroundType, create_new<ConstantBackgroundItem>);
    add(Constants::PoissonNoiseBackgroundType, create_new<PoissonNoiseBackgroundItem>);
    add(Constants::FootprintNoneType, create_new<FootprintNoneItem>);
    add(Constants::FootprintGaussianType, create_new<FootprintGaussianItem>);
    add(Constants::FootprintSquareType, create_new<FootprintSquareItem>);
    add(Constants::VectorType, create_new<VectorItem>);
    add(Constants::PropertyType, create_new<PropertyItem>);

    add(Constants::AnisoPyramidType, create_new<AnisoPyramidItem>);
    add(Constants::BoxType, create_new<BoxItem>);
    add(Constants::ConeType, create_new<ConeItem>);
    add(Constants::Cone6Type, create_new<Cone6Item>);
    add(Constants::CuboctahedronType, create_new<CuboctahedronItem>);
    add(Constants::DodecahedronType, create_new<DodecahedronItem>);
    add(Constants::DotType, create_new<DotItem>);
    add(Constants::CylinderType, create_new<CylinderItem>);
    add(Constants::EllipsoidalCylinderType, create_new<EllipsoidalCylinderItem>);
    add(Constants::FullSphereType, create_new<FullSphereItem>);
    add(Constants::FullSpheroidType, create_new<FullSpheroidItem>);
    add(Constants::HemiEllipsoidType, create_new<HemiEllipsoidItem>);
    add(Constants::IcosahedronType, create_new<IcosahedronItem>);
    add(Constants::Prism3Type, create_new<Prism3Item>);
    add(Constants::Prism6Type, create_new<Prism6Item>);
    add(Constants::PyramidType, create_new<PyramidItem>);
    add(Constants::Ripple1BoxType, create_new<Ripple1BoxItem>);
    add(Constants::Ripple1GaussType, create_new<Ripple1GaussItem>);
    add(Constants::Ripple1LorentzType, create_new<Ripple1LorentzItem>);
    add(Constants::Ripple2Type, create_new<Ripple2Item>);
    add(Constants::TetrahedronType, create_new<TetrahedronItem>);
    add(Constants::TruncatedCubeType, create_new<TruncatedCubeItem>);
    add(Constants::TruncatedSphereType, create_new<TruncatedSphereItem>);
    add(Constants::TruncatedSpheroidType, create_new<TruncatedSpheroidItem>);

    add(Constants::XRotationType, create_new<XRotationItem>);
    add(Constants::YRotationType, create_new<YRotationItem>);
    add(Constants::ZRotationType, create_new<ZRotationItem>);
    add(Constants::EulerRotationType, create_new<EulerRotationItem>);

    add(Constants::LayerBasicRoughnessType, create_new<LayerBasicRoughnessItem>);
    add(Constants::LayerZeroRoughnessType, create_new<LayerZeroRoughnessItem>);

    add(Constants::SphericalDetectorType, create_new<SphericalDetectorItem>);
    add(Constants::RectangularDetectorType, create_new<RectangularDetectorItem>);

    add(Constants::DistributionNoneType, create_new<DistributionNoneItem>);
    add(Constants::DistributionGateType, create_new<DistributionGateItem>);
    add(Constants::DistributionLorentzType, create_new<DistributionLorentzItem>);
    add(Constants::DistributionGaussianType, create_new<DistributionGaussianItem>);
    add(Constants::DistributionLogNormalType, create_new<DistributionLogNormalItem>);
    add(Constants::DistributionCosineType, create_new<DistributionCosineItem>);
    add(Constants::DistributionTrapezoidType, create_new<DistributionTrapezoidItem>);

    add(Constants::FTDistribution1DCauchyType, create_new<FTDistribution1DCauchyItem>);
    add(Constants::FTDistribution1DGaussType, create_new<FTDistribution1DGaussItem>);
    add(Constants::FTDistribution1DGateType, create_new<FTDistribution1DGateItem>);
    add(Constants::FTDistribution1DTriangleType, create_new<FTDistribution1DTriangleItem>);
    add(Constants::FTDistribution1DCosineType, create_new<FTDistribution1DCosineItem>);
    add(Constants::FTDistribution1DVoigtType, create_new<FTDistribution1DVoigtItem>);

    add(Constants::FTDistribution2DCauchyType, create_new<FTDistribution2DCauchyItem>);
    add(Constants::FTDistribution2DGaussType, create_new<FTDistribution2DGaussItem>);
    add(Constants::FTDistribution2DGateType, create_new<FTDistribution2DGateItem>);
    add(Constants::FTDistribution2DConeType, create_new<FTDistribution2DConeItem>);
    add(Constants::FTDistribution2DVoigtType, create_new<FTDistribution2DVoigtItem>);

    add(Constants::FTDecayFunction1DCauchyType, create_new<FTDecayFunction1DCauchyItem>);
    add(Constants::FTDecayFunction1DGaussType, create_new<FTDecayFunction1DGaussItem>);
    add(Constants::FTDecayFunction1DTriangleType, create_new<FTDecayFunction1DTriangleItem>);
    add(Constants::FTDecayFunction1DVoigtType, create_new<FTDecayFunction1DVoigtItem>);

    add(Constants::FTDecayFunction2DCauchyType, create_new<FTDecayFunction2DCauchyItem>);
    add(Constants::FTDecayFunction2DGaussType, create_new<FTDecayFunction2DGaussItem>);
    add(Constants::FTDecayFunction2DVoigtType, create_new<FTDecayFunction2DVoigtItem>);

    add(Constants::BasicLatticeType, create_new<BasicLatticeItem>);
    add(Constants::SquareLatticeType, create_new<SquareLatticeItem>);
    add(Constants::HexagonalLatticeType, create_new<HexagonalLatticeItem>);

    add(Constants::MaterialType, create_new<MaterialItem>);
    add(Constants::MaterialContainerType, create_new<MaterialItemContainer>);

    add(Constants::MaterialRefractiveDataType, create_new<MaterialRefractiveDataItem>);
    add(Constants::MaterialSLDDataType, create_new<MaterialSLDDataItem>);

    add(Constants::JobItemType, create_new<JobItem>);

    add(Constants::IntensityDataType, create_new<IntensityDataItem>);
    add(Constants::SpecularDataType, create_new<SpecularDataItem>);
    add(Constants::Data1DViewItemType, create_new<Data1DViewItem>);
    add(Constants::DataPropertyContainerType, create_new<DataPropertyContainer>);
    add(Constants::DataItem1DPropertiesType, create_new<Data1DProperties>);

    add(Constants::BasicAxisType, create_new<BasicAxisItem>);
    add(Constants::PointwiseAxisType, create_new<PointwiseAxisItem>);
    add(Constants::AmplitudeAxisType, create_new<AmplitudeAxisItem>);

    add(Constants::BeamWavelengthType, create_new<BeamWavelengthItem>);
    add(Constants::BeamAzimuthalAngleType, create_new<BeamAzimuthalAngleItem>);
    add(Constants::BeamInclinationAngleType, create_new<BeamInclinationAngleItem>);
    add(Constants::SpecularBeamInclinationType, create_new<SpecularBeamInclinationItem>);
    add(Constants::SpecularBeamWavelengthType, create_new<SpecularBeamWavelengthItem>);

    add(Constants::ResolutionFunctionNoneType, create_new<ResolutionFunctionNoneItem>);
    add(Constants::ResolutionFunction2DGaussianType, create_new<ResolutionFunction2DGaussianItem>);

    add(Constants::MaskContainerType, create_new<MaskContainerItem>);
    add(Constants::RectangleMaskType, create_new<RectangleItem>);
    add(Constants::PolygonPointType, create_new<PolygonPointItem>);
    add(Constants::PolygonMaskType, create_new<PolygonItem>);
    add(Constants::VerticalLineMaskType, create_new<VerticalLineItem>);
    add(Constants::HorizontalLineMaskType, create_new<HorizontalLineItem>);
    add(Constants::EllipseMaskType, create_new<EllipseItem>);
    add(Constants::MaskAllType, create_new<MaskAllItem>);

    add(Constants::RegionOfInterestType, create_new<RegionOfInterestItem>);

    add(Constants::GroupItemType, create_new<GroupItem>);

    add(Constants::ParameterContainerType, create_new<ParameterContainerItem>);
    add(Constants::ParameterLabelType, create_new<ParameterLabelItem>);
    add(Constants::ParameterType, create_new<ParameterItem>);

    add(Constants::FitParameterContainerType, create_new<FitParameterContainerItem>);
    add(Constants::FitParameterType, create_new<FitParameterItem>);
    add(Constants::FitParameterLinkType, create_new<FitParameterLinkItem>);
    add(Constants::FitSuiteType, create_new<FitSuiteItem>);

    add(Constants::SimulationOptionsType, create_new<SimulationOptionsItem>);

    add(Constants::RealDataType, create_new<RealDataItem>);

    add(Constants::MinimizerContainerType, create_new<MinimizerContainerItem>);
    add(Constants::MinuitMinimizerType, create_new<MinuitMinimizerItem>);
    add(Constants::GSLMultiMinimizerType, create_new<GSLMultiMinimizerItem>);
    add(Constants::GeneticMinimizerType, create_new<GeneticMinimizerItem>);
    add(Constants::GSLSimAnMinimizerType, create_new<SimAnMinimizerItem>);
    add(Constants::GSLLMAMinimizerType, create_new<GSLLMAMinimizerItem>);
    add(Constants::TestMinimizerType, create_new<TestMinimizerItem>);

    add(Constants::RealLimitsLimitlessType, create_new<LimitlessItem>);
    add(Constants::RealLimitsPositiveType, create_new<PositiveItem>);
    add(Constants::RealLimitsNonnegativeType, create_new<NonnegativeItem>);
    add(Constants::RealLimitsLowerLimitedType, create_new<LowerLimitedItem>);
    add(Constants::RealLimitsUpperLimitedType, create_new<UpperLimitedItem>);
    add(Constants::RealLimitsLimitedType, create_new<LimitedItem>);

    add(Constants::ProjectionContainerType, create_new<ProjectionContainerItem>);

    add(Constants::DepthProbeInstrumentType, create_new<DepthProbeInstrumentItem>);
}

bool ItemCatalogue::contains(const QString& modelType) const
{
    return m_data.contains(modelType);
}

std::unique_ptr<SessionItem> ItemCatalogue::create(const QString& modelType) const
{
    return m_data.create(modelType);
}

QStringList ItemCatalogue::validTopItemTypes() const
{
    return m_valid_top_item_types;
}

void ItemCatalogue::add(const QString& modelType, ItemCatalogue::factory_function_t f)
{
    m_data.registerItem(modelType, f);
}

void ItemCatalogue::init_top_item_types()
{
    m_valid_top_item_types.clear();

    m_valid_top_item_types << Constants::MultiLayerType << Constants::LayerType
                           << Constants::ParticleLayoutType << Constants::ParticleType
                           << Constants::ParticleCoreShellType << Constants::ParticleCompositionType
                           << Constants::MesoCrystalType << Constants::ParticleDistributionType
                           << Constants::RotationType
                           << Constants::InterferenceFunction1DLatticeType
                           << Constants::InterferenceFunction2DLatticeType
                           << Constants::InterferenceFunction2DParaCrystalType
                           << Constants::InterferenceFunctionFinite2DLatticeType
                           << Constants::InterferenceFunctionHardDiskType
                           << Constants::InterferenceFunctionRadialParaCrystalType;
}
