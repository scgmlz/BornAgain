//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GUIObjectBuilder.cpp
//! @brief     Implements GUIObjectBuilder namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Models/GUIObjectBuilder.h"
#include "Base/Const/Units.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Core/Simulation/OffSpecularSimulation.h"
#include "Core/Simulation/SpecularSimulation.h"
#include "GUI/coregui/Models/DocumentModel.h"
#include "GUI/coregui/Models/GUIDomainSampleVisitor.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Models/SimulationOptionsItem.h"
#include "GUI/coregui/Models/TransformFromDomain.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "Sample/Multilayer/MultiLayer.h"

namespace {
GISASInstrumentItem* createGISASInstrumentItem(InstrumentModel* model,
                                               const GISASSimulation& simulation,
                                               const QString& name);

OffSpecularInstrumentItem* createOffSpecularInstrumentItem(InstrumentModel* model,
                                                           const OffSpecularSimulation& simulation,
                                                           const QString& name);

SpecularInstrumentItem* createSpecularInstrumentItem(InstrumentModel* model,
                                                     const SpecularSimulation& simulation,
                                                     const QString& name);
} // namespace

SessionItem* GUIObjectBuilder::populateSampleModelFromSim(SampleModel* sampleModel,
                                                          MaterialModel* materialModel,
                                                          const ISimulation& simulation) {
    std::unique_ptr<ISimulation> sim(simulation.clone());
    sim->prepareSimulation();
    SessionItem* item = populateSampleModel(sampleModel, materialModel, *sim->sample());
    return item;
}

SessionItem* GUIObjectBuilder::populateSampleModel(SampleModel* sampleModel,
                                                   MaterialModel* materialModel,
                                                   const MultiLayer& sample,
                                                   const QString& sample_name) {
    GUIDomainSampleVisitor visitor;
    return visitor.populateSampleModel(sampleModel, materialModel, sample, sample_name);
}

SessionItem* GUIObjectBuilder::populateInstrumentModel(InstrumentModel* p_instrument_model,
                                                       const ISimulation& simulation,
                                                       const QString& instrument_name) {
    ASSERT(p_instrument_model);

    QString name = instrument_name.isEmpty()
                       ? QString::fromStdString(simulation.instrument().getName())
                       : instrument_name;

    if (auto gisasSimulation = dynamic_cast<const GISASSimulation*>(&simulation)) {
        return createGISASInstrumentItem(p_instrument_model, *gisasSimulation, name);
    } else if (auto offSpecSimulation = dynamic_cast<const OffSpecularSimulation*>(&simulation)) {
        return createOffSpecularInstrumentItem(p_instrument_model, *offSpecSimulation, name);
    } else if (auto spec_simulation = dynamic_cast<const SpecularSimulation*>(&simulation)) {
        return createSpecularInstrumentItem(p_instrument_model, *spec_simulation, name);
    }

    throw GUIHelpers::Error("GUIObjectBuilder::populateInstrumentModel() -> Error. ISimulation is "
                            "not yet supported");
}

SessionItem* GUIObjectBuilder::populateDocumentModel(DocumentModel* p_document_model,
                                                     const ISimulation& simulation) {
    SimulationOptionsItem* p_options_item =
        dynamic_cast<SimulationOptionsItem*>(p_document_model->insertNewItem("SimulationOptions"));
    ASSERT(p_options_item);
    if (simulation.getOptions().isIntegrate()) {
        p_options_item->setComputationMethod("Monte-Carlo Integration");
        p_options_item->setNumberOfMonteCarloPoints(
            static_cast<int>(simulation.getOptions().getMcPoints()));
    }
    if (simulation.getOptions().useAvgMaterials()) {
        p_options_item->setFresnelMaterialMethod("Average Layer Material");
    }
    if (simulation.getOptions().includeSpecular()) {
        p_options_item->setIncludeSpecularPeak("Yes");
    }
    return p_options_item;
}

namespace {
GISASInstrumentItem* createGISASInstrumentItem(InstrumentModel* model,
                                               const GISASSimulation& simulation,
                                               const QString& name) {
    auto result = dynamic_cast<GISASInstrumentItem*>(model->insertNewItem("GISASInstrument"));

    result->setItemName(name);
    TransformFromDomain::setGISASBeamItem(result->beamItem(), simulation);
    TransformFromDomain::setDetector(result, simulation);
    TransformFromDomain::setBackground(result, simulation);

    return result;
}

OffSpecularInstrumentItem* createOffSpecularInstrumentItem(InstrumentModel* model,
                                                           const OffSpecularSimulation& simulation,
                                                           const QString& name) {
    auto result =
        dynamic_cast<OffSpecularInstrumentItem*>(model->insertNewItem("OffSpecularInstrument"));

    result->setItemName(name);
    TransformFromDomain::setOffSpecularBeamItem(result->beamItem(), simulation);
    TransformFromDomain::setDetector(result, simulation);
    TransformFromDomain::setBackground(result, simulation);

    auto axisItem = result->getItem(OffSpecularInstrumentItem::P_ALPHA_AXIS);
    TransformFromDomain::setAxisItem(axisItem, *simulation.beamAxis(), 1. / Units::deg);

    return result;
}

SpecularInstrumentItem* createSpecularInstrumentItem(InstrumentModel* model,
                                                     const SpecularSimulation& simulation,
                                                     const QString& name) {
    auto result = dynamic_cast<SpecularInstrumentItem*>(model->insertNewItem("SpecularInstrument"));

    result->setItemName(name);
    TransformFromDomain::setSpecularBeamItem(result->beamItem(), simulation);
    TransformFromDomain::setBackground(result, simulation);

    return result;
}
} // namespace
