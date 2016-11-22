// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUITest.cpp
//! @brief     Implements class GUITest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GUITest.h"
#include "DocumentModel.h"
#include "DomainSimulationBuilder.h"
#include "GISASSimulation.h"
#include "GUIObjectBuilder.h"
#include "InstrumentModel.h"
#include "IntensityDataFunctions.h"
#include "MaterialModel.h"
#include "MaterialSvc.h"
#include "SampleModel.h"

GUITest::GUITest(const std::string &name, const std::string &description,
                 GISASSimulation *reference_simulation, double threshold)
    : IReferencedTest(name, description, threshold)
    , m_reference_simulation(reference_simulation)
    , m_domain_simulation(nullptr)
{}

GUITest::~GUITest()
{
    delete m_reference_simulation;
    delete m_domain_simulation;
}

bool GUITest::runTest()
{
    if (!m_reference_simulation)
        throw Exceptions::NullPointerException(
            "GUITest::runTest() -> Error. Uninitialized simulation object.");

    m_reference_simulation->runSimulation();

    createDomainSimulation();
    m_domain_simulation->runSimulation();

    const std::unique_ptr<OutputData<double> > P_domain_data(
                m_domain_simulation->getDetectorIntensity());
    const std::unique_ptr<OutputData<double> > P_reference_data(
        m_reference_simulation->getDetectorIntensity());
    return compareIntensityMaps(*P_domain_data, *P_reference_data);
}

//! returns new simulation from
void GUITest::createDomainSimulation()
{
    assert(m_reference_simulation->getSample());

    // initializing necessary GUI
    const std::unique_ptr<DocumentModel> documentModel(new DocumentModel());
    const std::unique_ptr<SampleModel> sampleModel(new SampleModel());
    const std::unique_ptr<InstrumentModel> instrumentModel(new InstrumentModel());
    const std::unique_ptr<MaterialModel> materialModel(new MaterialModel());
    const std::unique_ptr<MaterialSvc> materialSvc(new MaterialSvc(materialModel.get()));

    // populating GUI models from domain
    GUIObjectBuilder guiBuilder;
    guiBuilder.populateSampleModel(sampleModel.get(), *m_reference_simulation);
    guiBuilder.populateInstrumentModel(instrumentModel.get(), *m_reference_simulation);
    guiBuilder.populateDocumentModel(documentModel.get(), *m_reference_simulation);

    m_domain_simulation = DomainSimulationBuilder::getSimulation(sampleModel->multiLayerItem(),
            instrumentModel->instrumentItem(), documentModel->getSimulationOptionsItem());
}
