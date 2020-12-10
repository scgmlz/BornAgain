//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/SampleBuilderFactory.cpp
//! @brief     Implement class SampleBuilderFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/SampleBuilderFactory.h"
#include "Sample/StandardSamples/BoxCompositionBuilder.h"
#include "Sample/StandardSamples/BoxesSquareLatticeBuilder.h"
#include "Sample/StandardSamples/CoreShellParticleBuilder.h"
#include "Sample/StandardSamples/CustomMorphologyBuilder.h"
#include "Sample/StandardSamples/CylindersAndPrismsBuilder.h"
#include "Sample/StandardSamples/CylindersBuilder.h"
#include "Sample/StandardSamples/FeNiBilayerBuilder.h"
#include "Sample/StandardSamples/HomogeneousMultilayerBuilder.h"
#include "Sample/StandardSamples/LatticeBuilder.h"
#include "Sample/StandardSamples/LayersWithAbsorptionBuilder.h"
#include "Sample/StandardSamples/LayersWithAbsorptionBySLDBuilder.h"
#include "Sample/StandardSamples/MagneticLayersBuilder.h"
#include "Sample/StandardSamples/MagneticParticlesBuilder.h"
#include "Sample/StandardSamples/MesoCrystalBuilder.h"
#include "Sample/StandardSamples/MultiLayerWithNCRoughnessBuilder.h"
#include "Sample/StandardSamples/MultipleLayoutBuilder.h"
#include "Sample/StandardSamples/ParaCrystalBuilder.h"
#include "Sample/StandardSamples/ParticleCompositionBuilder.h"
#include "Sample/StandardSamples/ParticleDistributionsBuilder.h"
#include "Sample/StandardSamples/ParticleInVacuumBuilder.h"
#include "Sample/StandardSamples/PercusYevickBuilder.h"
#include "Sample/StandardSamples/PlainMultiLayerBySLDBuilder.h"
#include "Sample/StandardSamples/ResonatorBuilder.h"
#include "Sample/StandardSamples/RipplesBuilder.h"
#include "Sample/StandardSamples/RotatedPyramidsBuilder.h"
#include "Sample/StandardSamples/SizeDistributionModelsBuilder.h"
#include "Sample/StandardSamples/SlicedCompositionBuilder.h"
#include "Sample/StandardSamples/SlicedCylindersBuilder.h"
#include "Sample/StandardSamples/ThickAbsorptiveSampleBuilder.h"
#include "Sample/StandardSamples/TransformationsBuilder.h"
#include "Sample/StandardSamples/TwoDimLatticeBuilder.h"
#include "Sample/StandardSamples/TwoLayerRoughnessBuilder.h"

SampleBuilderFactory::SampleBuilderFactory() {
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

    registerItem("SquareLattice2DBuilder", create_new<SquareLattice2DBuilder>);

    registerItem("CenteredSquareLattice2DBuilder", create_new<CenteredSquareLattice2DBuilder>);

    registerItem("RotatedSquareLattice2DBuilder", create_new<RotatedSquareLattice2DBuilder>);

    registerItem("FiniteSquareLattice2DBuilder", create_new<FiniteSquareLattice2DBuilder>);

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

    registerItem("SimpleMagneticRotationBuilder", create_new<SimpleMagneticRotationBuilder>);

    registerItem("MagneticLayerBuilder", create_new<MagneticLayerBuilder>);

    registerItem("FeNiBilayerBuilder", create_new<FeNiBilayerBuilder>);

    registerItem("FeNiBilayerTanhBuilder", create_new<FeNiBilayerTanhBuilder>);

    registerItem("FeNiBilayerNCBuilder", create_new<FeNiBilayerNCBuilder>);

    registerItem("FeNiBilayerSpinFlipBuilder", create_new<FeNiBilayerSpinFlipBuilder>);

    registerItem("FeNiBilayerSpinFlipTanhBuilder", create_new<FeNiBilayerSpinFlipTanhBuilder>);

    registerItem("FeNiBilayerSpinFlipNCBuilder", create_new<FeNiBilayerSpinFlipNCBuilder>);

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

    registerItem("ParticleInVacuumBuilder", create_new<ParticleInVacuumBuilder>);

    registerItem("TransformBoxBuilder", create_new<TransformBoxBuilder>);

    registerItem("LayersWithAbsorptionBuilder", create_new<LayersWithAbsorptionBuilder>);

    registerItem("LayersWithAbsorptionBySLDBuilder", create_new<LayersWithAbsorptionBySLDBuilder>);

    registerItem("BoxesSquareLattice2DBuilder", create_new<BoxesSquareLattice2DBuilder>);

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

MultiLayer* SampleBuilderFactory::createSampleByName(const std::string& name) {
    return createItemPtr(name)->buildSample();
}
