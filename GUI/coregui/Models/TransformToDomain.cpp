// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/TransformToDomain.cpp
//! @brief     Implements class TransformToDomain
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "TransformToDomain.h"
#include "BeamAngleItems.h"
#include "BeamItem.h"
#include "BeamWavelengthItem.h"
#include "BornAgainNamespace.h"
#include "ComboProperty.h"
#include "DetectorItems.h"
#include "Distributions.h"
#include "FTDecayFunctionItems.h"
#include "FTDistributionItems.h"
#include "GISASSimulation.h"
#include "GUIHelpers.h"
#include "IResolutionFunction2D.h"
#include "InterferenceFunction1DLattice.h"
#include "InterferenceFunction2DLattice.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "InterferenceFunctionItems.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "LatticeTypeItems.h"
#include "LayerItem.h"
#include "LayerRoughnessItems.h"
#include "MaskItems.h"
#include "MaterialUtils.h"
#include "MultiLayerItem.h"
#include "ParameterPattern.h"
#include "ParticleCompositionItem.h"
#include "ParticleCoreShellItem.h"
#include "ParticleDistributionItem.h"
#include "ParticleItem.h"
#include "ParticleLayoutItem.h"
#include "RotationItems.h"
#include "SimulationOptionsItem.h"
#include "TransformationItem.h"
#include "Units.h"
#include "VectorItem.h"

std::unique_ptr<IMaterial> TransformToDomain::createDomainMaterial(const SessionItem& item)
{
    MaterialProperty material_property;
    if (item.modelType() == Constants::ParticleType) {
        material_property
            = item.getItemValue(ParticleItem::P_MATERIAL).value<MaterialProperty>();
    } else if (item.modelType() == Constants::LayerType) {
        material_property
            = item.getItemValue(LayerItem::P_MATERIAL).value<MaterialProperty>();
    }
    if (!material_property.isDefined())
        throw GUIHelpers::Error(
            "TransformToDomain::createDomainMaterial() -> Error. Unknown item to create material");

    return MaterialUtils::createDomainMaterial(material_property);
}

std::unique_ptr<MultiLayer> TransformToDomain::createMultiLayer(const SessionItem& item)
{
    auto P_multilayer = GUIHelpers::make_unique<MultiLayer>();
    auto cross_corr_length
        = item.getItemValue(MultiLayerItem::P_CROSS_CORR_LENGTH).toDouble();
    if (cross_corr_length > 0)
        P_multilayer->setCrossCorrLength(cross_corr_length);
    return P_multilayer;
}

std::unique_ptr<Layer> TransformToDomain::createLayer(const SessionItem& item)
{
    return GUIHelpers::make_unique<Layer>(
        *createDomainMaterial(item),
        item.getItemValue(LayerItem::P_THICKNESS).toDouble());
}

std::unique_ptr<LayerRoughness>
TransformToDomain::createLayerRoughness(const SessionItem& roughnessItem)
{
    if (roughnessItem.modelType() == Constants::LayerZeroRoughnessType) {
        return nullptr;
    } else if (roughnessItem.modelType() == Constants::LayerBasicRoughnessType) {
        return GUIHelpers::make_unique<LayerRoughness>(
            roughnessItem.getItemValue(LayerBasicRoughnessItem::P_SIGMA).toDouble(),
            roughnessItem.getItemValue(LayerBasicRoughnessItem::P_HURST).toDouble(),
            roughnessItem.getItemValue(LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH)
                .toDouble());
    } else {
        throw GUIHelpers::Error("TransformToDomain::createLayerRoughness() -> Error.");
    }
}

std::unique_ptr<ParticleLayout>
TransformToDomain::createParticleLayout(const SessionItem& item)
{
    auto P_layout = GUIHelpers::make_unique<ParticleLayout>();
    auto prop = item.getItemValue(ParticleLayoutItem::P_APPROX).value<ComboProperty>();
    QString approximation = prop.getValue();
    if (approximation == QString("Decoupling Approximation")) {
        P_layout->setApproximation(ILayout::DA);
    } else if (approximation == QString("Size Space Coupling Approximation")) {
        P_layout->setApproximation(ILayout::SSCA);
    }
    auto total_density
        = item.getItemValue(ParticleLayoutItem::P_TOTAL_DENSITY).value<double>();
    P_layout->setTotalParticleSurfaceDensity(total_density);
    return P_layout;
}

std::unique_ptr<IParticle> TransformToDomain::createIParticle(const SessionItem& item)
{
    std::unique_ptr<IParticle> P_particle;
    if (item.modelType() == Constants::ParticleType) {
        auto& particle_item = static_cast<const ParticleItem&>(item);
        P_particle = particle_item.createParticle();
    } else if (item.modelType() == Constants::ParticleCoreShellType) {
        auto& particle_coreshell_item = static_cast<const ParticleCoreShellItem&>(item);
        P_particle = particle_coreshell_item.createParticleCoreShell();
    } else if (item.modelType() == Constants::ParticleCompositionType) {
        auto& particle_composition_item = static_cast<const ParticleCompositionItem&>(item);
        P_particle = particle_composition_item.createParticleComposition();
    }
    return P_particle;
}

std::unique_ptr<ParticleDistribution> TransformToDomain::createParticleDistribution(
        const SessionItem& item)
{
    auto& particle_distribution = static_cast<const ParticleDistributionItem&>(item);
    auto P_part_distr = particle_distribution.createParticleDistribution();
    return P_part_distr;
}

std::unique_ptr<IDistribution1D>
TransformToDomain::createDistribution(const SessionItem& item)
{
    auto distr_item = dynamic_cast<const DistributionItem*>(&item);
    Q_ASSERT(distr_item);
    return distr_item->createDistribution();
}

std::unique_ptr<IInterferenceFunction>
TransformToDomain::createInterferenceFunction(const SessionItem& item)
{
    std::unique_ptr<IInterferenceFunction> P_result{};
    if (item.modelType() == Constants::InterferenceFunctionRadialParaCrystalType) {
        double peak_distance
            = item.getItemValue(InterferenceFunctionRadialParaCrystalItem::P_PEAK_DISTANCE)
                  .toDouble();
        double damping_length
            = item.getItemValue(
                       InterferenceFunctionRadialParaCrystalItem::P_DAMPING_LENGTH).toDouble();
        double domain_size
            = item.getItemValue(InterferenceFunctionRadialParaCrystalItem::P_DOMAIN_SIZE)
                  .toDouble();
        double kappa = item.getItemValue(
                                InterferenceFunctionRadialParaCrystalItem::P_KAPPA).toDouble();
        auto P_iff = GUIHelpers::make_unique<InterferenceFunctionRadialParaCrystal>(peak_distance,
                                                                                    damping_length);
        P_iff->setDomainSize(domain_size);
        P_iff->setKappa(kappa);
        auto pdfItem = item.getGroupItem(InterferenceFunctionRadialParaCrystalItem::P_PDF);
        Q_ASSERT(pdfItem);
        std::unique_ptr<IFTDistribution1D> P_pdf(
            dynamic_cast<FTDistribution1DItem*>(pdfItem)->createFTDistribution());
        Q_ASSERT(P_pdf);
        P_iff->setProbabilityDistribution(*P_pdf);
        P_result = std::move(P_iff);
    } else if (item.modelType() == Constants::InterferenceFunction2DParaCrystalType) {
        auto latticeItem
                = item.getGroupItem(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE);
        Q_ASSERT(latticeItem);
        double length_1 {0.0}, length_2 {0.0}, alpha_lattice {0.0};
        if (latticeItem->modelType() == Constants::BasicLatticeType) {
            length_1 = latticeItem->getItemValue(BasicLatticeTypeItem::P_LATTICE_LENGTH1)
                           .toDouble();
            length_2 = latticeItem->getItemValue(BasicLatticeTypeItem::P_LATTICE_LENGTH2)
                           .toDouble();
            alpha_lattice = Units::deg2rad(
                latticeItem->getItemValue(BasicLatticeTypeItem::P_LATTICE_ANGLE)
                    .toDouble());
        } else if (latticeItem->modelType() == Constants::SquareLatticeType) {
            length_1 = latticeItem->getItemValue(SquareLatticeTypeItem::P_LATTICE_LENGTH)
                           .toDouble();
            length_2 = length_1;
            alpha_lattice = M_PI / 2.0;
        } else if (latticeItem->modelType() == Constants::HexagonalLatticeType) {
            length_1 = latticeItem->getItemValue(
                                        HexagonalLatticeTypeItem::P_LATTICE_LENGTH).toDouble();
            length_2 = length_1;
            alpha_lattice = M_TWOPI / 3.0;
        } else {
            throw GUIHelpers::Error("TransformToDomain::createInterferenceFunction() -> Error");
        }

        auto P_iff = GUIHelpers::make_unique<InterferenceFunction2DParaCrystal>(
            length_1, length_2, alpha_lattice,
            Units::deg2rad(
                item.getItemValue(InterferenceFunction2DParaCrystalItem::P_ROTATION_ANGLE)
                    .toDouble()),
            item.getItemValue(InterferenceFunction2DParaCrystalItem::P_DAMPING_LENGTH)
                .toDouble());
        P_iff->setDomainSizes(
            item.getItemValue(InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE1)
                .toDouble(),
            item.getItemValue(InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE2)
                .toDouble());
        P_iff->setIntegrationOverXi(
            item.getItemValue(InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION)
                .toBool());

        auto pdf1Item = item.getGroupItem(InterferenceFunction2DParaCrystalItem::P_PDF1);
        Q_ASSERT(pdf1Item);
        std::unique_ptr<IFTDistribution2D> P_pdf1(
            dynamic_cast<FTDistribution2DItem*>(pdf1Item)->createFTDistribution());
        Q_ASSERT(P_pdf1.get());

        auto pdf2Item = item.getGroupItem(InterferenceFunction2DParaCrystalItem::P_PDF2);
        Q_ASSERT(pdf2Item);
        std::unique_ptr<IFTDistribution2D> P_pdf2(
            dynamic_cast<FTDistribution2DItem*>(pdf2Item)->createFTDistribution());
        Q_ASSERT(P_pdf2.get());

        P_iff->setProbabilityDistributions(*P_pdf1, *P_pdf2);
        P_result = std::move(P_iff);
    } else if (item.modelType() == Constants::InterferenceFunction1DLatticeType) {
        double length =
                item.getItemValue(InterferenceFunction1DLatticeItem::P_LENGTH).toDouble();
        double angle = Units::deg2rad(
                item.getItemValue(InterferenceFunction1DLatticeItem::P_ROTATION_ANGLE)
                       .toDouble());
        auto P_iff = GUIHelpers::make_unique<InterferenceFunction1DLattice>(length, angle);
        auto pdfItem = item.getGroupItem(InterferenceFunction1DLatticeItem::P_DECAY_FUNCTION);
        Q_ASSERT(pdfItem);
        std::unique_ptr<IFTDecayFunction1D> P_pdf(
            dynamic_cast<FTDecayFunction1DItem*>(pdfItem)->createFTDecayFunction());
        Q_ASSERT(P_pdf);
        P_iff->setDecayFunction(*P_pdf);
        P_result = std::move(P_iff);
    } else if (item.modelType() == Constants::InterferenceFunction2DLatticeType) {
        auto latticeItem = item.getGroupItem(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE);
        Q_ASSERT(latticeItem);

        double length_1 {0.0}, length_2 {0.0}, angle {0.0};
        if (latticeItem->modelType() == Constants::BasicLatticeType) {
            length_1 = latticeItem->getItemValue(BasicLatticeTypeItem::P_LATTICE_LENGTH1)
                           .toDouble();
            length_2 = latticeItem->getItemValue(BasicLatticeTypeItem::P_LATTICE_LENGTH2)
                           .toDouble();
            angle = Units::deg2rad(
                latticeItem->getItemValue(BasicLatticeTypeItem::P_LATTICE_ANGLE)
                    .toDouble());
        } else if (latticeItem->modelType() == Constants::SquareLatticeType) {
            length_1 = latticeItem->getItemValue(SquareLatticeTypeItem::P_LATTICE_LENGTH)
                           .toDouble();
            length_2 = length_1;
            angle = M_PI / 2.0;
        } else if (latticeItem->modelType() == Constants::HexagonalLatticeType) {
            length_1 = latticeItem->getItemValue(
                                        HexagonalLatticeTypeItem::P_LATTICE_LENGTH).toDouble();
            length_2 = length_1;
            angle = M_TWOPI / 3.0;
        } else {
            throw GUIHelpers::Error("TransformToDomain::createInterferenceFunction() -> Error");
        }
        double xi = Units::deg2rad(
            item.getItemValue(InterferenceFunction2DLatticeItem::P_ROTATION_ANGLE)
                .toDouble());
        auto P_iff
            = GUIHelpers::make_unique<InterferenceFunction2DLattice>(length_1, length_2, angle, xi);
        auto pdfItem = item.getGroupItem(InterferenceFunction2DLatticeItem::P_DECAY_FUNCTION);
        Q_ASSERT(pdfItem);
        std::unique_ptr<IFTDecayFunction2D> P_pdf(
            dynamic_cast<FTDecayFunction2DItem*>(pdfItem)->createFTDecayFunction());
        Q_ASSERT(P_pdf);
        P_iff->setDecayFunction(*P_pdf);
        P_result = std::move(P_iff);
    }
    return P_result;
}

std::unique_ptr<Instrument> TransformToDomain::createInstrument(const SessionItem& item)
{
    Q_UNUSED(item);
    return GUIHelpers::make_unique<Instrument>();
}

std::unique_ptr<Beam> TransformToDomain::createBeam(const SessionItem& item)
{
    auto P_beam = GUIHelpers::make_unique<Beam>();

    auto beamItem = dynamic_cast<const BeamItem*>(&item);
    P_beam->setIntensity(beamItem->getIntensity());
    double lambda = beamItem->getWavelength();
    double inclination_angle = Units::deg2rad(beamItem->getInclinationAngle());
    double azimuthal_angle = Units::deg2rad(beamItem->getAzimuthalAngle());
    P_beam->setCentralK(lambda, inclination_angle, azimuthal_angle);

    return P_beam;
}

void TransformToDomain::initInstrumentFromDetectorItem(const SessionItem& detectorItem,
                                                       Instrument* instrument)
{
    auto subDetector = detectorItem.getGroupItem(DetectorItem::P_DETECTOR);
    Q_ASSERT(subDetector);

    double scale(1.0);
    if(auto sphericalDetector = dynamic_cast<SphericalDetectorItem*>(subDetector)) {
        scale = Units::degree;
        auto detector = sphericalDetector->createDetector();
        instrument->setDetector(*detector);
        auto resfunc = sphericalDetector->createResolutionFunction();
        if(resfunc) instrument->setDetectorResolutionFunction(*resfunc);
    }

    else if(auto rectangularDetector = dynamic_cast<RectangularDetectorItem*>(subDetector)) {
        auto detector = rectangularDetector->createDetector();
        instrument->setDetector(*detector);
        auto resfunc = rectangularDetector->createResolutionFunction();
        if(resfunc) instrument->setDetectorResolutionFunction(*resfunc);

    } else {
        throw GUIHelpers::Error(
            "TransformToDomain::initInstrumentWithDetectorItem() -> Error. Unknown model type "
            + subDetector->modelType());
    }

    if(auto maskContainerItem = detectorItem.getChildOfType(Constants::MaskContainerType)) {
        for(int i_row = maskContainerItem->childItems().size(); i_row>0; --i_row) {
            if(auto maskItem = dynamic_cast<MaskItem*>(
                   maskContainerItem->childItems().at(i_row-1))) {

                if(maskItem->modelType() == Constants::RegionOfInterestType) {
                    double xlow = scale*maskItem->getItemValue(RectangleItem::P_XLOW).toDouble();
                    double ylow = scale*maskItem->getItemValue(RectangleItem::P_YLOW).toDouble();
                    double xup = scale*maskItem->getItemValue(RectangleItem::P_XUP).toDouble();
                    double yup = scale*maskItem->getItemValue(RectangleItem::P_YUP).toDouble();
                    instrument->getDetector()->setRegionOfInterest(xlow, ylow, xup, yup);

                } else {
                    std::unique_ptr<IShape2D > shape(maskItem->createShape(scale));
                    bool mask_value = maskItem->getItemValue(MaskItem::P_MASK_VALUE).toBool();
                    instrument->getDetector()->addMask(*shape, mask_value);
                }
            }
        }
    }
}

//! adds DistributionParameters to the Simulation
void TransformToDomain::addDistributionParametersToSimulation(const SessionItem& beam_item,
                                                              GISASSimulation* simulation)
{
    ParameterPattern pattern_wavelength;
    pattern_wavelength.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Wavelength);
    ParameterPattern pattern_alpha;
    pattern_alpha.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Inclination);
    ParameterPattern pattern_phi;
    pattern_phi.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Azimuth);
    if (beam_item.modelType() == Constants::BeamType) {
        if (auto beamWavelength
            = dynamic_cast<BeamWavelengthItem*>(beam_item.getItem(BeamItem::P_WAVELENGTH))) {
            auto P_par_distr = beamWavelength->getParameterDistributionForName(
                        pattern_wavelength.toStdString());
            if (P_par_distr)
                simulation->addParameterDistribution(*P_par_distr);
        }
        if (auto inclinationAngle = dynamic_cast<BeamInclinationAngleItem*>(
                beam_item.getItem(BeamItem::P_INCLINATION_ANGLE))) {
            auto P_par_distr = inclinationAngle->getParameterDistributionForName(
                        pattern_alpha.toStdString());
            if (P_par_distr)
                simulation->addParameterDistribution(*P_par_distr);
        }
        if (auto azimuthalAngle = dynamic_cast<BeamAzimuthalAngleItem*>(
                beam_item.getItem(BeamItem::P_AZIMUTHAL_ANGLE))) {
            auto P_par_distr = azimuthalAngle->getParameterDistributionForName(
                        pattern_phi.toStdString());
            if (P_par_distr)
                simulation->addParameterDistribution(*P_par_distr);
        }
    }
}

void TransformToDomain::setSimulationOptions(GISASSimulation* simulation,
                                             const SessionItem& item)
{
    Q_ASSERT(item.modelType() == Constants::SimulationOptionsType);

    if(auto optionItem = dynamic_cast<const SimulationOptionsItem*>(&item)) {
        simulation->getOptions().setNumberOfThreads(optionItem->getNumberOfThreads());
        if(optionItem->getComputationMethod() == Constants::SIMULATION_MONTECARLO) {
            simulation->getOptions().setMonteCarloIntegration(true,
                    optionItem->getNumberOfMonteCarloPoints());
        }
    }

}

void TransformToDomain::setTransformationInfo(IParticle* result, const SessionItem& item)
{
    setPositionInfo(result, item);
    setRotationInfo(result, item);
}

void TransformToDomain::setPositionInfo(IParticle* result, const SessionItem& item)
{
    SessionItem* positionItem = item.getItem(ParticleItem::P_POSITION);
    Q_ASSERT(positionItem);
    double pos_x = positionItem->getItemValue(VectorItem::P_X).toDouble();
    double pos_y = positionItem->getItemValue(VectorItem::P_Y).toDouble();
    double pos_z = positionItem->getItemValue(VectorItem::P_Z).toDouble();
    result->setPosition(pos_x, pos_y, pos_z);
}

void TransformToDomain::setRotationInfo(IParticle* result, const SessionItem& item)
{
    QVector<SessionItem*> children = item.childItems();
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->modelType() == Constants::TransformationType) {
            RotationItem* rot_item = dynamic_cast<RotationItem*>(
                children[i]->getGroupItem(TransformationItem::P_ROT));
            if (!rot_item) {
                throw GUIHelpers::Error("DomainObjectBuilder::setRotationInfo() "
                                        "-> Error! ParticleItem's child is"
                                        " not a rotation.");
            }
            std::unique_ptr<IRotation> P_rotation(rot_item->createRotation());
            if (P_rotation.get()) {
                result->setRotation(*P_rotation);
            }
            break;
        }
    }
}
