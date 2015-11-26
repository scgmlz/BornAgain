// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/TransformToDomain.cpp
//! @brief     Implements class TransformToDomain
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TransformToDomain.h"
#include "MaterialUtils.h"
#include "GUIHelpers.h"
#include "FormFactorItems.h"
#include "InterferenceFunctionItems.h"
#include "ParticleItem.h"
#include "LayerItem.h"
#include "BeamItem.h"
#include "ComboProperty.h"
#include "DetectorItems.h"
#include "AxesItems.h"
#include "MultiLayerItem.h"
#include "LatticeTypeItems.h"
#include "FTDistributionItems.h"
#include "ParticleCoreShellItem.h"
#include "ParticleCoreShell.h"
#include "LayerRoughnessItems.h"
#include "VectorItem.h"
#include "MaterialUtils.h"
#include "MaterialProperty.h"
#include "AngleProperty.h"
#include "FixedBinAxis.h"
#include "ConstKBinAxis.h"
#include "ParticleLayoutItem.h"
#include "DistributionItem.h"
#include "Distributions.h"
#include "BeamWavelengthItem.h"
#include "BeamAngleItems.h"
#include "ResolutionFunctionItems.h"

#include <QDebug>

std::unique_ptr<IMaterial> TransformToDomain::createDomainMaterial(const ParameterizedItem &item)
{
    MaterialProperty material_property;
    if (item.modelType() == Constants::ParticleType) {
        material_property
            = item.getRegisteredProperty(ParticleItem::P_MATERIAL).value<MaterialProperty>();
    } else if (item.modelType() == Constants::LayerType) {
        material_property
            = item.getRegisteredProperty(LayerItem::P_MATERIAL).value<MaterialProperty>();
    }
    if (!material_property.isDefined())
        throw GUIHelpers::Error(
            "TransformToDomain::createDomainMaterial() -> Error. Unknown item to create material");

    return MaterialUtils::createDomainMaterial(material_property);
}

std::unique_ptr<MultiLayer> TransformToDomain::createMultiLayer(const ParameterizedItem &item)
{
    auto P_multilayer = GUIHelpers::make_unique<MultiLayer>();
    auto cross_corr_length
        = item.getRegisteredProperty(MultiLayerItem::P_CROSS_CORR_LENGTH).toDouble();
    if (cross_corr_length > 0)
        P_multilayer->setCrossCorrLength(cross_corr_length);
    return P_multilayer;
}

std::unique_ptr<Layer> TransformToDomain::createLayer(const ParameterizedItem &item)
{
    auto P_layer = GUIHelpers::make_unique<Layer>();
    auto thickness = item.getRegisteredProperty(LayerItem::P_THICKNESS).toDouble();
    P_layer->setThickness(thickness);
    auto P_material = createDomainMaterial(item);
    P_layer->setMaterial(*P_material);
    return P_layer;
}

std::unique_ptr<LayerRoughness>
TransformToDomain::createLayerRoughness(const ParameterizedItem &roughnessItem)
{
    if (roughnessItem.modelType() == Constants::LayerZeroRoughnessType) {
        return nullptr;
    } else if (roughnessItem.modelType() == Constants::LayerBasicRoughnessType) {
        return GUIHelpers::make_unique<LayerRoughness>(
            roughnessItem.getRegisteredProperty(LayerBasicRoughnessItem::P_SIGMA).toDouble(),
            roughnessItem.getRegisteredProperty(LayerBasicRoughnessItem::P_HURST).toDouble(),
            roughnessItem.getRegisteredProperty(LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH)
                .toDouble());
    } else {
        throw GUIHelpers::Error("TransformToDomain::createLayerROughness() -> Error.");
    }
}

std::unique_ptr<ParticleLayout>
TransformToDomain::createParticleLayout(const ParameterizedItem &item)
{
    auto P_layout = GUIHelpers::make_unique<ParticleLayout>();
    auto prop = item.getRegisteredProperty(ParticleLayoutItem::P_APPROX).value<ComboProperty>();
    QString approximation = prop.getValue();
    if (approximation == QString("Decoupling Approximation")) {
        P_layout->setApproximation(ILayout::DA);
    } else if (approximation == QString("Size Space Coupling Approximation")) {
        P_layout->setApproximation(ILayout::SSCA);
    }
    auto total_density
        = item.getRegisteredProperty(ParticleLayoutItem::P_TOTAL_DENSITY).value<double>();
    P_layout->setTotalParticleSurfaceDensity(total_density);
    return P_layout;
}

std::unique_ptr<Particle> TransformToDomain::createParticle(const ParameterizedItem &item,
                                                            double &abundance)
{
    auto P_material = createDomainMaterial(item);
    auto P_particle = GUIHelpers::make_unique<Particle>(*P_material);

    abundance = item.getRegisteredProperty(ParticleItem::P_ABUNDANCE).toDouble();

    auto ffItem = item.getSubItems()[ParticleItem::P_FORM_FACTOR];
    Q_ASSERT(ffItem);
    auto P_ff = createFormFactor(*ffItem);
    P_particle->setFormFactor(*P_ff);

    return P_particle;
}

std::unique_ptr<ParticleCoreShell>
TransformToDomain::createParticleCoreShell(const ParameterizedItem &item, const Particle &core,
                                           const Particle &shell, double &abundance)
{
    abundance = item.getRegisteredProperty(ParticleItem::P_ABUNDANCE).toDouble();
    auto P_coreshell = GUIHelpers::make_unique<ParticleCoreShell>(shell, core);
    return P_coreshell;
}

std::unique_ptr<ParticleComposition>
TransformToDomain::createParticleComposition(const ParameterizedItem &item, double &abundance)
{
    abundance = item.getRegisteredProperty(ParticleItem::P_ABUNDANCE).toDouble();
    auto P_composition = GUIHelpers::make_unique<ParticleComposition>();
    return P_composition;
}

std::unique_ptr<IFormFactor> TransformToDomain::createFormFactor(const ParameterizedItem &item)
{
    auto ffItem = dynamic_cast<const FormFactorItem *>(&item);
    Q_ASSERT(ffItem);
    return ffItem->createFormFactor();
}

std::unique_ptr<IDistribution1D>
TransformToDomain::createDistribution(const ParameterizedItem &item)
{
    auto distr_item = dynamic_cast<const DistributionItem *>(&item);
    Q_ASSERT(distr_item);
    return distr_item->createDistribution();
}

std::unique_ptr<IInterferenceFunction>
TransformToDomain::createInterferenceFunction(const ParameterizedItem &item)
{
    std::unique_ptr<IInterferenceFunction> P_result{};
    if (item.modelType() == Constants::InterferenceFunctionRadialParaCrystalType) {
        double peak_distance
            = item.getRegisteredProperty(InterferenceFunctionRadialParaCrystalItem::P_PEAK_DISTANCE)
                  .toDouble();
        double damping_length
            = item.getRegisteredProperty(
                       InterferenceFunctionRadialParaCrystalItem::P_DAMPING_LENGTH).toDouble();
        double domain_size
            = item.getRegisteredProperty(InterferenceFunctionRadialParaCrystalItem::P_DOMAIN_SIZE)
                  .toDouble();
        double kappa = item.getRegisteredProperty(
                                InterferenceFunctionRadialParaCrystalItem::P_KAPPA).toDouble();
        auto P_iff = GUIHelpers::make_unique<InterferenceFunctionRadialParaCrystal>(peak_distance,
                                                                                    damping_length);
        P_iff->setDomainSize(domain_size);
        P_iff->setKappa(kappa);
        auto pdfItem = item.getSubItems()[InterferenceFunctionRadialParaCrystalItem::P_PDF];
        Q_ASSERT(pdfItem);
        std::unique_ptr<IFTDistribution1D> P_pdf(
            dynamic_cast<FTDistribution1DItem *>(pdfItem)->createFTDistribution());
        Q_ASSERT(P_pdf);
        P_iff->setProbabilityDistribution(*P_pdf);
        P_result = std::move(P_iff);
    } else if (item.modelType() == Constants::InterferenceFunction2DParaCrystalType) {
        auto latticeItem
                = item.getSubItems()[InterferenceFunction2DParaCrystalItem::P_LATTICE_TYPE];
        Q_ASSERT(latticeItem);
        double length_1 {0.0}, length_2 {0.0}, alpha_lattice {0.0};
        if (latticeItem->modelType() == Constants::BasicLatticeType) {
            length_1 = latticeItem->getRegisteredProperty(BasicLatticeTypeItem::P_LATTICE_LENGTH1)
                           .toDouble();
            length_2 = latticeItem->getRegisteredProperty(BasicLatticeTypeItem::P_LATTICE_LENGTH2)
                           .toDouble();
            alpha_lattice = Units::deg2rad(
                latticeItem->getRegisteredProperty(BasicLatticeTypeItem::P_LATTICE_ANGLE)
                    .toDouble());
        } else if (latticeItem->modelType() == Constants::SquareLatticeType) {
            length_1 = latticeItem->getRegisteredProperty(SquareLatticeTypeItem::P_LATTICE_LENGTH)
                           .toDouble();
            length_2 = length_1;
            alpha_lattice = Units::PI / 2.0;
        } else if (latticeItem->modelType() == Constants::HexagonalLatticeType) {
            length_1 = latticeItem->getRegisteredProperty(
                                        HexagonalLatticeTypeItem::P_LATTICE_LENGTH).toDouble();
            length_2 = length_1;
            alpha_lattice = 2 * Units::PI / 3.0;
        } else {
            throw GUIHelpers::Error("TransformToDomain::createInterferenceFunction() -> Error");
        }

        auto P_iff = GUIHelpers::make_unique<InterferenceFunction2DParaCrystal>(
            length_1, length_2, alpha_lattice,
            Units::deg2rad(
                item.getRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_ROTATION_ANGLE)
                    .toDouble()),
            item.getRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_DAMPING_LENGTH)
                .toDouble());
        P_iff->setDomainSizes(
            item.getRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE1)
                .toDouble(),
            item.getRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE2)
                .toDouble());
        P_iff->setIntegrationOverXi(
            item.getRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION)
                .toBool());

        auto pdf1Item = item.getSubItems()[InterferenceFunction2DParaCrystalItem::P_PDF1];
        Q_ASSERT(pdf1Item);
        std::unique_ptr<IFTDistribution2D> P_pdf1(
            dynamic_cast<FTDistribution2DItem *>(pdf1Item)->createFTDistribution());
        Q_ASSERT(P_pdf1.get());

        auto pdf2Item = item.getSubItems()[InterferenceFunction2DParaCrystalItem::P_PDF2];
        Q_ASSERT(pdf2Item);
        std::unique_ptr<IFTDistribution2D> P_pdf2(
            dynamic_cast<FTDistribution2DItem *>(pdf2Item)->createFTDistribution());
        Q_ASSERT(P_pdf2.get());

        P_iff->setProbabilityDistributions(*P_pdf1, *P_pdf2);
        P_result = std::move(P_iff);
    } else if (item.modelType() == Constants::InterferenceFunction2DLatticeType) {
        auto latticeItem = item.getSubItems()[InterferenceFunction2DLatticeItem::P_LATTICE_TYPE];
        Q_ASSERT(latticeItem);

        double length_1 {0.0}, length_2 {0.0}, angle {0.0};
        if (latticeItem->modelType() == Constants::BasicLatticeType) {
            length_1 = latticeItem->getRegisteredProperty(BasicLatticeTypeItem::P_LATTICE_LENGTH1)
                           .toDouble();
            length_2 = latticeItem->getRegisteredProperty(BasicLatticeTypeItem::P_LATTICE_LENGTH2)
                           .toDouble();
            angle = Units::deg2rad(
                latticeItem->getRegisteredProperty(BasicLatticeTypeItem::P_LATTICE_ANGLE)
                    .toDouble());
        } else if (latticeItem->modelType() == Constants::SquareLatticeType) {
            length_1 = latticeItem->getRegisteredProperty(SquareLatticeTypeItem::P_LATTICE_LENGTH)
                           .toDouble();
            length_2 = length_1;
            angle = Units::PI / 2.0;
        } else if (latticeItem->modelType() == Constants::HexagonalLatticeType) {
            length_1 = latticeItem->getRegisteredProperty(
                                        HexagonalLatticeTypeItem::P_LATTICE_LENGTH).toDouble();
            length_2 = length_1;
            angle = 2 * Units::PI / 3.0;
        } else {
            throw GUIHelpers::Error("TransformToDomain::createInterferenceFunction() -> Error");
        }
        double xi = Units::deg2rad(
            item.getRegisteredProperty(InterferenceFunction2DLatticeItem::P_ROTATION_ANGLE)
                .toDouble());
        auto P_iff
            = GUIHelpers::make_unique<InterferenceFunction2DLattice>(length_1, length_2, angle, xi);
        auto pdfItem = item.getSubItems()[InterferenceFunction2DLatticeItem::P_PDF];
        Q_ASSERT(pdfItem);
        std::unique_ptr<IFTDistribution2D> P_pdf(
            dynamic_cast<FTDistribution2DItem *>(pdfItem)->createFTDistribution());
        Q_ASSERT(P_pdf);
        P_iff->setProbabilityDistribution(*P_pdf);
        P_result = std::move(P_iff);
    }
    return P_result;
}

std::unique_ptr<Instrument> TransformToDomain::createInstrument(const ParameterizedItem &item)
{
    Q_UNUSED(item);
    return GUIHelpers::make_unique<Instrument>();
}

std::unique_ptr<Beam> TransformToDomain::createBeam(const ParameterizedItem &item)
{
    auto P_beam = GUIHelpers::make_unique<Beam>();

    auto beamItem = dynamic_cast<const BeamItem *>(&item);
    P_beam->setIntensity(beamItem->getIntensity());
    double lambda = beamItem->getWavelength();
    double inclination_angle = Units::deg2rad(beamItem->getInclinationAngle());
    double azimuthal_angle = Units::deg2rad(beamItem->getAzimuthalAngle());
    P_beam->setCentralK(lambda, inclination_angle, azimuthal_angle);

    return P_beam;
}

void TransformToDomain::initInstrumentFromDetectorItem(const ParameterizedItem &item,
                                                       Instrument *instrument)
{
    auto subDetector = item.getSubItems()[DetectorItem::P_DETECTOR];
    Q_ASSERT(subDetector);

    if (subDetector->modelType() == Constants::SphericalDetectorType) {
        auto x_axis = dynamic_cast<BasicAxisItem *>(
            subDetector->getSubItems()[PhiAlphaDetectorItem::P_PHI_AXIS]);
        Q_ASSERT(x_axis);
        int n_x = x_axis->getRegisteredProperty(BasicAxisItem::P_NBINS).toInt();
        double x_min
            = Units::deg2rad(x_axis->getRegisteredProperty(BasicAxisItem::P_MIN).toDouble());
        double x_max
            = Units::deg2rad(x_axis->getRegisteredProperty(BasicAxisItem::P_MAX).toDouble());

        auto y_axis = dynamic_cast<BasicAxisItem *>(
            subDetector->getSubItems()[PhiAlphaDetectorItem::P_ALPHA_AXIS]);
        Q_ASSERT(y_axis);
        int n_y = y_axis->getRegisteredProperty(BasicAxisItem::P_NBINS).toInt();
        double y_min
            = Units::deg2rad(y_axis->getRegisteredProperty(BasicAxisItem::P_MIN).toDouble());
        double y_max
            = Units::deg2rad(y_axis->getRegisteredProperty(BasicAxisItem::P_MAX).toDouble());

        instrument->setDetectorParameters(n_x, x_min, x_max, n_y, y_min, y_max);

        // setting up resolution function
        auto resfuncItem = dynamic_cast<ResolutionFunctionItem *>(
            subDetector->getSubItems()[PhiAlphaDetectorItem::P_RESOLUTION_FUNCTION]);
        Q_ASSERT(resfuncItem);
        std::unique_ptr<IResolutionFunction2D> P_res_func(resfuncItem->createResolutionFunction());
        if (P_res_func)
            instrument->setDetectorResolutionFunction(*P_res_func);
    } else {
        throw GUIHelpers::Error(
            "TransformToDomain::initInstrumentWithDetectorItem() -> Error. Unknown model type "
            + subDetector->modelType());
    }
}

//! adds DistributionParameters to the Simulation
void TransformToDomain::addDistributionParametersToSimulation(const ParameterizedItem &beam_item,
                                                              GISASSimulation *simulation)
{
    if (beam_item.modelType() == Constants::BeamType) {
        if (auto beamWavelength
            = dynamic_cast<BeamWavelengthItem *>(beam_item.getSubItems()[BeamItem::P_WAVELENGTH])) {
            auto P_par_distr = beamWavelength->getParameterDistributionForName("*/Beam/wavelength");
            if (P_par_distr)
                simulation->addParameterDistribution(*P_par_distr);
        }
        if (auto inclinationAngle = dynamic_cast<BeamInclinationAngleItem *>(
                beam_item.getSubItems()[BeamItem::P_INCLINATION_ANGLE])) {
            auto P_par_distr = inclinationAngle->getParameterDistributionForName("*/Beam/alpha");
            if (P_par_distr)
                simulation->addParameterDistribution(*P_par_distr);
        }
        if (auto azimuthalAngle = dynamic_cast<BeamAzimuthalAngleItem *>(
                beam_item.getSubItems()[BeamItem::P_AZIMUTHAL_ANGLE])) {
            auto P_par_distr = azimuthalAngle->getParameterDistributionForName("*/Beam/phi");
            if (P_par_distr)
                simulation->addParameterDistribution(*P_par_distr);
        }
    }
}
