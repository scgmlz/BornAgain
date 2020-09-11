// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/SampleBuilderFactory.cpp
//! @brief     Implement class SampleBuilderFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/SampleBuilderFactory.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/StandardSamples/BoxCompositionBuilder.h"
#include "Core/StandardSamples/BoxesSquareLatticeBuilder.h"
#include "Core/StandardSamples/CoreShellParticleBuilder.h"
#include "Core/StandardSamples/CustomMorphologyBuilder.h"
#include "Core/StandardSamples/CylindersAndPrismsBuilder.h"
#include "Core/StandardSamples/CylindersBuilder.h"
#include "Core/StandardSamples/HomogeneousMultilayerBuilder.h"
#include "Core/StandardSamples/LatticeBuilder.h"
#include "Core/StandardSamples/LayersWithAbsorptionBuilder.h"
#include "Core/StandardSamples/LayersWithAbsorptionBySLDBuilder.h"
#include "Core/StandardSamples/MagneticLayersBuilder.h"
#include "Core/StandardSamples/MagneticParticlesBuilder.h"
#include "Core/StandardSamples/MesoCrystalBuilder.h"
#include "Core/StandardSamples/MultiLayerWithNCRoughnessBuilder.h"
#include "Core/StandardSamples/MultiLayerWithRoughnessBuilder.h"
#include "Core/StandardSamples/MultipleLayoutBuilder.h"
#include "Core/StandardSamples/ParaCrystalBuilder.h"
#include "Core/StandardSamples/ParticleCompositionBuilder.h"
#include "Core/StandardSamples/ParticleDistributionsBuilder.h"
#include "Core/StandardSamples/ParticleInTheAirBuilder.h"
#include "Core/StandardSamples/PercusYevickBuilder.h"
#include "Core/StandardSamples/PlainMultiLayerBySLDBuilder.h"
#include "Core/StandardSamples/ResonatorBuilder.h"
#include "Core/StandardSamples/RipplesBuilder.h"
#include "Core/StandardSamples/RotatedPyramidsBuilder.h"
#include "Core/StandardSamples/SizeDistributionModelsBuilder.h"
#include "Core/StandardSamples/SlicedCylindersBuilder.h"
#include "Core/StandardSamples/SlicedParticleBuilder.h"
#include "Core/StandardSamples/ThickAbsorptiveSampleBuilder.h"
#include "Core/StandardSamples/TransformationsBuilder.h"
#include "Core/StandardSamples/TwoDimLatticeBuilder.h"
#include "Core/StandardSamples/TwoLayerRoughnessBuilder.h"

SampleBuilderFactory::SampleBuilderFactory()
{
    registerItem("CylindersAndPrismsBuilder", create_new<CylindersAndPrismsBuilder>);

    registerItem("TwoTypesCylindersDistributionBuilder",
                 create_new<TwoTypesCylindersDistributionBuilder>);

    registerItem("CylindersInBABuilder", create_new<CylindersInBABuilder>);
    registerItem("CylindersInDWBABuilder", create_new<CylindersInDWBABuilder>);
    registerItem("LargeCylindersInDWBABuilder", create_new<LargeCylindersInDWBABuilder>);

    registerItem("CylindersWithSizeDistributionBuilder",
                 create_new<CylindersWithSizeDistributionBuilder>);

    registerItem("RadialParaCrystalBuilder", create_new<RadialParaCrystalBuilder>);

    registerItem("HardDiskBuilder", create_new<HardDiskBuilder>);

    registerItem("Basic2DParaCrystalBuilder", create_new<Basic2DParaCrystalBuilder>);

    registerItem("HexParaCrystalBuilder", create_new<HexParaCrystalBuilder>);

    registerItem("Lattice1DBuilder", create_new<Lattice1DBuilder>);

    registerItem("RectParaCrystalBuilder", create_new<RectParaCrystalBuilder>);

    registerItem("Basic2DLatticeBuilder", create_new<Basic2DLatticeBuilder>);

    registerItem("SquareLatticeBuilder", create_new<SquareLatticeBuilder>);

    registerItem("CenteredSquareLatticeBuilder", create_new<CenteredSquareLatticeBuilder>);

    registerItem("RotatedSquareLatticeBuilder", create_new<RotatedSquareLatticeBuilder>);

    registerItem("FiniteSquareLatticeBuilder", create_new<FiniteSquareLatticeBuilder>);

    registerItem("SuperLatticeBuilder", create_new<SuperLatticeBuilder>);

    registerItem("CustomMorphologyBuilder", create_new<CustomMorphologyBuilder>);

    registerItem("RotatedPyramidsBuilder", create_new<RotatedPyramidsBuilder>);

    registerItem("CoreShellParticleBuilder", create_new<CoreShellParticleBuilder>);

    registerItem("CoreShellBoxRotateZandYBuilder", create_new<CoreShellBoxRotateZandYBuilder>);

    registerItem("SizeDistributionDAModelBuilder", create_new<SizeDistributionDAModelBuilder>);

    registerItem("SizeDistributionLMAModelBuilder", create_new<SizeDistributionLMAModelBuilder>);

    registerItem("SizeDistributionSSCAModelBuilder", create_new<SizeDistributionSSCAModelBuilder>);

    registerItem("CylindersInSSCABuilder", create_new<CylindersInSSCABuilder>);

    registerItem("MesoCrystalBuilder", create_new<MesoCrystalBuilder>);

    registerItem("MagneticParticleZeroFieldBuilder", create_new<MagneticParticleZeroFieldBuilder>);

    registerItem("MagneticCylindersBuilder", create_new<MagneticCylindersBuilder>);

    registerItem("MagneticSubstrateZeroFieldBuilder",
                 create_new<MagneticSubstrateZeroFieldBuilder>);

    registerItem("SimpleMagneticLayerBuilder", create_new<SimpleMagneticLayerBuilder>);

    registerItem("MagneticLayerBuilder", create_new<MagneticLayerBuilder>);

    registerItem("MagneticRotationBuilder", create_new<MagneticRotationBuilder>);

    registerItem("MagneticSpheresBuilder", create_new<MagneticSpheresBuilder>);

    registerItem("MultiLayerWithRoughnessBuilder", create_new<MultiLayerWithRoughnessBuilder>);

    registerItem("MultiLayerWithNCRoughnessBuilder", create_new<MultiLayerWithNCRoughnessBuilder>);

    registerItem("TwoLayerRoughnessBuilder", create_new<TwoLayerRoughnessBuilder>);

    registerItem("MultipleLayoutBuilder", create_new<MultipleLayoutBuilder>);

    registerItem("TriangularRippleBuilder", create_new<TriangularRippleBuilder>);

    registerItem("AsymRippleBuilder", create_new<AsymRippleBuilder>);

    registerItem("CosineRippleBuilder", create_new<CosineRippleBuilder>);

    registerItem("ParticleCompositionBuilder", create_new<ParticleCompositionBuilder>);

    registerItem("BoxCompositionRotateXBuilder", create_new<BoxCompositionRotateXBuilder>);

    registerItem("BoxCompositionRotateYBuilder", create_new<BoxCompositionRotateYBuilder>);

    registerItem("BoxCompositionRotateZBuilder", create_new<BoxCompositionRotateZBuilder>);

    registerItem("BoxCompositionRotateZandYBuilder", create_new<BoxCompositionRotateZandYBuilder>);

    registerItem("BoxStackCompositionBuilder", create_new<BoxStackCompositionBuilder>);

    registerItem("ParticleInTheAirBuilder", create_new<ParticleInTheAirBuilder>);

    registerItem("TransformBoxBuilder", create_new<TransformBoxBuilder>);

    registerItem("LayersWithAbsorptionBuilder", create_new<LayersWithAbsorptionBuilder>);

    registerItem("LayersWithAbsorptionBySLDBuilder", create_new<LayersWithAbsorptionBySLDBuilder>);

    registerItem("BoxesSquareLatticeBuilder", create_new<BoxesSquareLatticeBuilder>);

    registerItem("RotatedCylindersBuilder", create_new<RotatedCylindersBuilder>);

    registerItem("SlicedCompositionBuilder", create_new<SlicedCompositionBuilder>);

    registerItem("RotatedPyramidsDistributionBuilder",
                 create_new<RotatedPyramidsDistributionBuilder>);

    registerItem("SpheresWithLimitsDistributionBuilder",
                 create_new<SpheresWithLimitsDistributionBuilder>);

    registerItem("ConesWithLimitsDistributionBuilder",
                 create_new<ConesWithLimitsDistributionBuilder>);

    registerItem("LinkedBoxDistributionBuilder", create_new<LinkedBoxDistributionBuilder>);

    registerItem("HomogeneousMultilayerBuilder", create_new<HomogeneousMultilayerBuilder>);

    registerItem("PlainMultiLayerBySLDBuilder", create_new<PlainMultiLayerBySLDBuilder>);

    registerItem("ResonatorBuilder", create_new<ResonatorBuilder>);

    registerItem("SlicedCylindersBuilder", create_new<SlicedCylindersBuilder>);

    registerItem("SLDSlicedCylindersBuilder", create_new<SLDSlicedCylindersBuilder>);

    registerItem("AveragedSlicedCylindersBuilder", create_new<AveragedSlicedCylindersBuilder>);

    registerItem("ThickAbsorptiveSampleBuilder", create_new<ThickAbsorptiveSampleBuilder>);
}

//! Retrieves a SampleBuilder from the registry, does the build, and returns the result.

MultiLayer* SampleBuilderFactory::createSample(const std::string& name)
{
    return createItemPtr(name)->buildSample();
}
