// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DomainObjectBuilder.cpp
//! @brief     Implements DomainObjectBuilder namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/DomainObjectBuilder.h"
#include "Core/Basics/Units.h"
#include "Core/Detector/IDetector2D.h"
#include "Core/Intensity/SimpleUnitConverters.h"
#include "Core/Intensity/UnitConverter1D.h"
#include "Core/Simulation/UnitConverterUtils.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/BeamItems.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/DepthProbeInstrumentItem.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InterferenceFunctionItems.h"
#include "GUI/coregui/Models/LayerItem.h"
#include "GUI/coregui/Models/ParticleDistributionItem.h"
#include "GUI/coregui/Models/ParticleLayoutItem.h"
#include "GUI/coregui/Models/SpecularBeamInclinationItem.h"
#include "GUI/coregui/Models/TransformToDomain.h"
#include "GUI/coregui/utils/GUIHelpers.h"

std::unique_ptr<MultiLayer> DomainObjectBuilder::buildMultiLayer(const SessionItem& multilayer_item)
{
    auto P_multilayer = TransformToDomain::createMultiLayer(multilayer_item);
    QVector<SessionItem*> children = multilayer_item.children();
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->modelType() == "Layer") {
            auto P_layer = buildLayer(*children[i]);
            auto roughnessItem = children[i]->getGroupItem(LayerItem::P_ROUGHNESS);
            ASSERT(roughnessItem);
            auto P_roughness = TransformToDomain::createLayerRoughness(*roughnessItem);
            if (P_layer) {
                if (P_roughness) {
                    P_multilayer->addLayerWithTopRoughness(*P_layer, *P_roughness);
                } else {
                    P_multilayer->addLayer(*P_layer);
                }
            }
        }
    }
    return P_multilayer;
}

std::unique_ptr<Layer> DomainObjectBuilder::buildLayer(const SessionItem& item)
{
    auto P_layer = TransformToDomain::createLayer(item);
    QVector<SessionItem*> children = item.children();
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->modelType() == "ParticleLayout") {
            auto P_layout = buildParticleLayout(*children[i]);
            if (P_layout) {
                P_layer->addLayout(*P_layout);
            }
        }
    }
    return P_layer;
}

std::unique_ptr<ParticleLayout> DomainObjectBuilder::buildParticleLayout(const SessionItem& item)
{
    auto P_layout = TransformToDomain::createParticleLayout(item);
    QVector<SessionItem*> children = item.getItems();
    for (int i = 0; i < children.size(); ++i) {
        auto P_particle = TransformToDomain::createIParticle(*children[i]);
        if (P_particle) {
            P_layout->addParticle(*P_particle);
            continue;
        }
        if (children[i]->modelType() == "ParticleDistribution") {
            auto prop = children[i]
                            ->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                            .value<ComboProperty>();
            QString par_name = prop.getValue();
            if (par_name == ParticleDistributionItem::NO_SELECTION) {
                auto grandchildren = children[i]->getItems();
                if (grandchildren.size() == 0) {
                    continue;
                }
                if (grandchildren.size() > 1) {
                    throw GUIHelpers::Error("DomainObjectBuilder::buildParticleLayout()"
                                            " -> Error! Too many particles defined"
                                            " in ParticleDistribution");
                }
                auto P_particle = TransformToDomain::createIParticle(*grandchildren[0]);
                if (P_particle) {
                    P_layout->addParticle(*P_particle);
                }
            } else {
                auto P_part_distr = TransformToDomain::createParticleDistribution(*children[i]);
                if (P_part_distr) {
                    P_layout->addParticle(*P_part_distr);
                }
            }
        } else {
            throw GUIHelpers::Error("DomainObjectBuilder::buildParticleLayout()"
                                    " -> Error! Not implemented");
        }
    }
    QVector<SessionItem*> interferences = item.getItems(ParticleLayoutItem::T_INTERFERENCE);
    for (int i = 0; i < interferences.size(); i++) {
        auto P_interference = buildInterferenceFunction(*interferences[i]);
        if (P_interference) {
            P_layout->setInterferenceFunction(*P_interference);
        }
    }
    return P_layout;
}

std::unique_ptr<IInterferenceFunction>
DomainObjectBuilder::buildInterferenceFunction(const SessionItem& item)
{
    auto iffItem = dynamic_cast<const InterferenceFunctionItem*>(&item);
    ASSERT(iffItem);
    return iffItem->createInterferenceFunction();
}

std::unique_ptr<Instrument>
DomainObjectBuilder::buildInstrument(const InstrumentItem& instrumentItem)
{
    return instrumentItem.createInstrument();
}

std::unique_ptr<IUnitConverter>
DomainObjectBuilder::createUnitConverter(const InstrumentItem* instrumentItem)
{
    if (auto specular_instrument = dynamic_cast<const SpecularInstrumentItem*>(instrumentItem))
        return specular_instrument->createUnitConverter();
    else if (auto depth_instrument = dynamic_cast<const DepthProbeInstrumentItem*>(instrumentItem))
        return depth_instrument->createUnitConverter();

    const auto instrument = instrumentItem->createInstrument();
    instrument->initDetector();

    if (instrumentItem->modelType() == "GISASInstrument")
        return UnitConverterUtils::createConverterForGISAS(*instrument);

    if (instrumentItem->modelType() == "OffSpecInstrument") {
        auto axis_item = dynamic_cast<BasicAxisItem*>(
            instrumentItem->getItem(OffSpecInstrumentItem::P_ALPHA_AXIS));
        const auto detector2d = dynamic_cast<const IDetector2D*>(instrument->getDetector());
        return std::make_unique<OffSpecularConverter>(*detector2d, instrument->getBeam(),
                                                      *axis_item->createAxis(Units::degree));
    }

    throw GUIHelpers::Error(
        "Error in DomainObjectBuilder::createUnitConverter: unknown instrument type.");
}
