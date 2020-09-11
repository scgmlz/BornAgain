// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ItemCatalog.cpp
//! @brief     Implements class ItemCatalog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/ItemCatalog.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/BackgroundItems.h"
#include "GUI/coregui/Models/BeamAngleItems.h"
#include "GUI/coregui/Models/BeamItems.h"
#include "GUI/coregui/Models/BeamWavelengthItem.h"
#include "GUI/coregui/Models/Data1DViewItem.h"
#include "GUI/coregui/Models/DataProperties.h"
#include "GUI/coregui/Models/DataPropertyContainer.h"
#include "GUI/coregui/Models/DepthProbeInstrumentItem.h"
#include "GUI/coregui/Models/DetectorItems.h"
#include "GUI/coregui/Models/FTDecayFunctionItems.h"
#include "GUI/coregui/Models/FTDistributionItems.h"
#include "GUI/coregui/Models/FitParameterItems.h"
#include "GUI/coregui/Models/FitSuiteItem.h"
#include "GUI/coregui/Models/FootprintItems.h"
#include "GUI/coregui/Models/FormFactorItems.h"
#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/InterferenceFunctionItems.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/Lattice2DItems.h"
#include "GUI/coregui/Models/LayerItem.h"
#include "GUI/coregui/Models/LayerRoughnessItems.h"
#include "GUI/coregui/Models/MaskItems.h"
#include "GUI/coregui/Models/MaterialDataItems.h"
#include "GUI/coregui/Models/MaterialItem.h"
#include "GUI/coregui/Models/MaterialItemContainer.h"
#include "GUI/coregui/Models/MesoCrystalItem.h"
#include "GUI/coregui/Models/MinimizerItem.h"
#include "GUI/coregui/Models/MultiLayerItem.h"
#include "GUI/coregui/Models/ParameterTreeItems.h"
#include "GUI/coregui/Models/ParticleCompositionItem.h"
#include "GUI/coregui/Models/ParticleCoreShellItem.h"
#include "GUI/coregui/Models/ParticleDistributionItem.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/ParticleLayoutItem.h"
#include "GUI/coregui/Models/PointwiseAxisItem.h"
#include "GUI/coregui/Models/ProjectionItems.h"
#include "GUI/coregui/Models/PropertyItem.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/RealLimitsItems.h"
#include "GUI/coregui/Models/RectangularDetectorItem.h"
#include "GUI/coregui/Models/ResolutionFunctionItems.h"
#include "GUI/coregui/Models/RotationItems.h"
#include "GUI/coregui/Models/SimulationOptionsItem.h"
#include "GUI/coregui/Models/SpecularBeamInclinationItem.h"
#include "GUI/coregui/Models/SpecularDataItem.h"
#include "GUI/coregui/Models/SphericalDetectorItem.h"
#include "GUI/coregui/Models/TransformationItem.h"
#include "GUI/coregui/Models/VectorItem.h"
#include "GUI/coregui/utils/GUIHelpers.h"

ItemCatalog::ItemCatalog()
{
    add("MultiLayer", create_new<MultiLayerItem>);
    add("Layer", create_new<LayerItem>);
    add("ParticleLayout", create_new<ParticleLayoutItem>);
    add("Particle", create_new<ParticleItem>);
    add("Rotation", create_new<TransformationItem>);
    add("ParticleCoreShell", create_new<ParticleCoreShellItem>);
    add("ParticleComposition", create_new<ParticleCompositionItem>);
    add("ParticleDistribution", create_new<ParticleDistributionItem>);
    add("MesoCrystal", create_new<MesoCrystalItem>);
    add("Interference1DLattice", create_new<InterferenceFunction1DLatticeItem>);
    add("Interference2DLattice", create_new<InterferenceFunction2DLatticeItem>);
    add("Interference2DParaCrystal", create_new<InterferenceFunction2DParaCrystalItem>);
    add("InterferenceFinite2DLattice", create_new<InterferenceFunctionFinite2DLatticeItem>);
    add("InterferenceHardDisk", create_new<InterferenceFunctionHardDiskItem>);
    add("InterferenceRadialParaCrystal", create_new<InterferenceFunctionRadialParaCrystalItem>);
    add("GISASInstrument", create_new<GISASInstrumentItem>);
    add("OffSpecInstrument", create_new<OffSpecInstrumentItem>);
    add("SpecularInstrument", create_new<SpecularInstrumentItem>);
    add("GISASBeam", create_new<GISASBeamItem>);
    add("SpecularBeam", create_new<SpecularBeamItem>);
    add("NoBackground", create_new<BackgroundNoneItem>);
    add("ConstantBackground", create_new<ConstantBackgroundItem>);
    add("PoissonNoiseBackground", create_new<PoissonNoiseBackgroundItem>);
    add("NoFootprint", create_new<FootprintNoneItem>);
    add("GaussianFootrpint", create_new<FootprintGaussianItem>);
    add("SquareFootprint", create_new<FootprintSquareItem>);
    add("Vector", create_new<VectorItem>);
    add("Property", create_new<PropertyItem>);

    add("AnisoPyramid", create_new<AnisoPyramidItem>);
    add("BarGauss", create_new<BarGaussItem>);
    add("BarLorentz", create_new<BarLorentzItem>);
    add("Box", create_new<BoxItem>);
    add("Cone", create_new<ConeItem>);
    add("Cone6", create_new<Cone6Item>);
    add("Cuboctahedron", create_new<CuboctahedronItem>);
    add("Dodecahedron", create_new<DodecahedronItem>);
    add("Dot", create_new<DotItem>);
    add("Cylinder", create_new<CylinderItem>);
    add("EllipsoidalCylinder", create_new<EllipsoidalCylinderItem>);
    add("FullSphere", create_new<FullSphereItem>);
    add("FullSpheroid", create_new<FullSpheroidItem>);
    add("HemiEllipsoid", create_new<HemiEllipsoidItem>);
    add("Icosahedron", create_new<IcosahedronItem>);
    add("Prism3", create_new<Prism3Item>);
    add("Prism6", create_new<Prism6Item>);
    add("Pyramid", create_new<PyramidItem>);
    add("CosineRippleBox", create_new<CosineRippleBoxItem>);
    add("CosineRippleGauss", create_new<CosineRippleGaussItem>);
    add("CosineRippleLorentz", create_new<CosineRippleLorentzItem>);
    add("SawtoothRippleBox", create_new<SawtoothRippleBoxItem>);
    add("SawtoothRippleGauss", create_new<SawtoothRippleGaussItem>);
    add("SawtoothRippleLorentz", create_new<SawtoothRippleLorentzItem>);
    add("Tetrahedron", create_new<TetrahedronItem>);
    add("TruncatedCube", create_new<TruncatedCubeItem>);
    add("TruncatedSphere", create_new<TruncatedSphereItem>);
    add("TruncatedSpheroid", create_new<TruncatedSpheroidItem>);

    add("XRotation", create_new<XRotationItem>);
    add("YRotation", create_new<YRotationItem>);
    add("ZRotation", create_new<ZRotationItem>);
    add("EulerRotation", create_new<EulerRotationItem>);

    add("LayerBasicRoughness", create_new<LayerBasicRoughnessItem>);
    add("LayerZeroRoughness", create_new<LayerZeroRoughnessItem>);

    add("SphericalDetector", create_new<SphericalDetectorItem>);
    add("RectangularDetector", create_new<RectangularDetectorItem>);

    add("DistributionNone", create_new<DistributionNoneItem>);
    add("DistributionGate", create_new<DistributionGateItem>);
    add("DistributionLorentz", create_new<DistributionLorentzItem>);
    add("DistributionGaussian", create_new<DistributionGaussianItem>);
    add("DistributionLogNormal", create_new<DistributionLogNormalItem>);
    add("DistributionCosine", create_new<DistributionCosineItem>);
    add("DistributionTrapezoid", create_new<DistributionTrapezoidItem>);

    add("FTDistribution1DCauchy", create_new<FTDistribution1DCauchyItem>);
    add("FTDistribution1DGauss", create_new<FTDistribution1DGaussItem>);
    add("FTDistribution1DGate", create_new<FTDistribution1DGateItem>);
    add("FTDistribution1DTriangle", create_new<FTDistribution1DTriangleItem>);
    add("FTDistribution1DCosine", create_new<FTDistribution1DCosineItem>);
    add("FTDistribution1DVoigt", create_new<FTDistribution1DVoigtItem>);

    add("FTDistribution2DCauchy", create_new<FTDistribution2DCauchyItem>);
    add("FTDistribution2DGauss", create_new<FTDistribution2DGaussItem>);
    add("FTDistribution2DGate", create_new<FTDistribution2DGateItem>);
    add("FTDistribution2DCone", create_new<FTDistribution2DConeItem>);
    add("FTDistribution2DVoigt", create_new<FTDistribution2DVoigtItem>);

    add("FTDecayFunction1DCauchy", create_new<FTDecayFunction1DCauchyItem>);
    add("FTDecayFunction1DGauss", create_new<FTDecayFunction1DGaussItem>);
    add("FTDecayFunction1DTriangle", create_new<FTDecayFunction1DTriangleItem>);
    add("FTDecayFunction1DVoigt", create_new<FTDecayFunction1DVoigtItem>);

    add("FTDecayFunction2DCauchy", create_new<FTDecayFunction2DCauchyItem>);
    add("FTDecayFunction2DGauss", create_new<FTDecayFunction2DGaussItem>);
    add("FTDecayFunction2DVoigt", create_new<FTDecayFunction2DVoigtItem>);

    add("BasicLattice", create_new<BasicLatticeItem>);
    add("SquareLattice", create_new<SquareLatticeItem>);
    add("HexagonalLattice", create_new<HexagonalLatticeItem>);

    add("Material", create_new<MaterialItem>);
    add("MaterialContainer", create_new<MaterialItemContainer>);

    add("MaterialRefractiveData", create_new<MaterialRefractiveDataItem>);
    add("MaterialSLDData", create_new<MaterialSLDDataItem>);

    add("JobItem", create_new<JobItem>);

    add("IntensityData", create_new<IntensityDataItem>);
    add("SpecularData", create_new<SpecularDataItem>);
    add("Data1DViewItem", create_new<Data1DViewItem>);
    add("DataPropertyContainer", create_new<DataPropertyContainer>);
    add("DataItem1DProperties", create_new<Data1DProperties>);

    add("BasicAxis", create_new<BasicAxisItem>);
    add("PointwiseAxis", create_new<PointwiseAxisItem>);
    add("AmplitudeAxis", create_new<AmplitudeAxisItem>);

    add("BeamWavelength", create_new<BeamWavelengthItem>);
    add("BeamAzimuthalAngle", create_new<BeamAzimuthalAngleItem>);
    add("BeamInclinationAngle", create_new<BeamInclinationAngleItem>);
    add("SpecularBeamInclinationAxis", create_new<SpecularBeamInclinationItem>);
    add("SpecularBeamWavelength", create_new<SpecularBeamWavelengthItem>);

    add("ResolutionFunctionNone", create_new<ResolutionFunctionNoneItem>);
    add("ResolutionFunction2DGaussian", create_new<ResolutionFunction2DGaussianItem>);

    add("MaskContainer", create_new<MaskContainerItem>);
    add("RectangleMask", create_new<RectangleItem>);
    add("PolygonPoint", create_new<PolygonPointItem>);
    add("PolygonMask", create_new<PolygonItem>);
    add("VerticalLineMask", create_new<VerticalLineItem>);
    add("HorizontalLineMask", create_new<HorizontalLineItem>);
    add("EllipseMask", create_new<EllipseItem>);
    add("MaskAllMask", create_new<MaskAllItem>);

    add("RegionOfInterest", create_new<RegionOfInterestItem>);

    add("GroupProperty", create_new<GroupItem>);

    add("Parameter Container", create_new<ParameterContainerItem>);
    add("Parameter Label", create_new<ParameterLabelItem>);
    add("Parameter", create_new<ParameterItem>);

    add("FitParameterContainer", create_new<FitParameterContainerItem>);
    add("FitParameter", create_new<FitParameterItem>);
    add("FitParameterLink", create_new<FitParameterLinkItem>);
    add("FitSuite", create_new<FitSuiteItem>);

    add("SimulationOptions", create_new<SimulationOptionsItem>);

    add("RealData", create_new<RealDataItem>);

    add("MinimizerContainer", create_new<MinimizerContainerItem>);
    add("Minuit2", create_new<MinuitMinimizerItem>);
    add("GSLMultiMin", create_new<GSLMultiMinimizerItem>);
    add("Genetic", create_new<GeneticMinimizerItem>);
    add("GSLSimAn", create_new<SimAnMinimizerItem>);
    add("GSLLMA", create_new<GSLLMAMinimizerItem>);
    add("Test", create_new<TestMinimizerItem>);

    add("RealLimitsLimitless", create_new<LimitlessItem>);
    add("RealLimitsPositive", create_new<PositiveItem>);
    add("RealLimitsNonnegative", create_new<NonnegativeItem>);
    add("RealLimitsLowerLimited", create_new<LowerLimitedItem>);
    add("RealLimitsUpperLimited", create_new<UpperLimitedItem>);
    add("RealLimitsLimited", create_new<LimitedItem>);

    add("ProjectionContainer", create_new<ProjectionContainerItem>);

    add("DepthProbeInstrument", create_new<DepthProbeInstrumentItem>);
}

std::unique_ptr<SessionItem> ItemCatalog::createItemPtr(const QString& modelType) const
{
    if (!m_data.contains(modelType))
        throw GUIHelpers::Error("ItemFactory::createItem() -> Error: Model name does not exist: "
                                + modelType);

    return m_data.createItemPtr(modelType);
}

QStringList ItemCatalog::validTopItemTypes()
{
    return {"MultiLayer",
            "Layer",
            "ParticleLayout",
            "Particle",
            "ParticleCoreShell",
            "ParticleComposition",
            "MesoCrystal",
            "ParticleDistribution",
            "Rotation",
            "Interference1DLattice",
            "Interference2DLattice",
            "Interference2DParaCrystal",
            "InterferenceFinite2DLattice",
            "InterferenceHardDisk",
            "InterferenceRadialParaCrystal"};
}

void ItemCatalog::add(const QString& modelType, std::function<SessionItem*()> f)
{
    m_data.registerItem(modelType, f);
}
