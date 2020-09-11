// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ApplicationModels.cpp
//! @brief     Defines class holding all application models
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/ApplicationModels.h"
#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Scattering/ISample.h"
#include "Core/Simulation/OffSpecSimulation.h"
#include "Core/Simulation/StandardSimulations.h"
#include "Core/StandardSamples/SampleBuilderFactory.h"
#include "GUI/coregui/Models/DocumentModel.h"
#include "GUI/coregui/Models/GUIObjectBuilder.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Models/MaterialModel.h"
#include "GUI/coregui/Models/MaterialPropertyController.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/RealDataModel.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Views/ImportDataWidgets/ImportDataUtils.h"
#include "GUI/coregui/utils/MessageService.h"
#include <QtCore/QXmlStreamWriter>

ApplicationModels::ApplicationModels(QObject* parent)
    : QObject(parent), m_documentModel(nullptr), m_materialModel(nullptr),
      m_instrumentModel(nullptr), m_sampleModel(nullptr), m_realDataModel(nullptr),
      m_jobModel(nullptr), m_materialPropertyController(new MaterialPropertyController(this))
{
    createModels();
    // createTestSample();
    // createTestJob();
}

ApplicationModels::~ApplicationModels() {}

DocumentModel* ApplicationModels::documentModel()
{
    return m_documentModel;
}

MaterialModel* ApplicationModels::materialModel()
{
    return m_materialModel;
}

InstrumentModel* ApplicationModels::instrumentModel()
{
    return m_instrumentModel;
}

SampleModel* ApplicationModels::sampleModel()
{
    return m_sampleModel;
}

RealDataModel* ApplicationModels::realDataModel()
{
    return m_realDataModel;
}

JobModel* ApplicationModels::jobModel()
{
    return m_jobModel;
}

//! reset all models to initial state
void ApplicationModels::resetModels()
{
    m_documentModel->clear();
    m_documentModel->insertNewItem("SimulationOptions");

    m_materialModel->clear();
    m_materialModel->addRefractiveMaterial("Default", 1e-3, 1e-5);
    m_materialModel->addRefractiveMaterial("Air", 0.0, 0.0);
    m_materialModel->addRefractiveMaterial("Particle", 6e-4, 2e-8);
    m_materialModel->addRefractiveMaterial("Substrate", 6e-6, 2e-8);

    m_sampleModel->clear();

    m_realDataModel->clear();

    m_jobModel->clear();

    m_instrumentModel->clear();
    SessionItem* instrument = m_instrumentModel->insertNewItem("GISASInstrument");
    instrument->setItemName("GISAS");
}

//! creates and initializes models, order is important
void ApplicationModels::createModels()
{
    createDocumentModel();
    createMaterialModel();
    createSampleModel();
    createInstrumentModel();
    createRealDataModel();
    createJobModel();
    resetModels();

    m_materialPropertyController->setModels(materialModel(), sampleModel());
}

void ApplicationModels::createDocumentModel()
{
    delete m_documentModel;
    m_documentModel = new DocumentModel(this);
    connectModel(m_documentModel);
}

void ApplicationModels::createMaterialModel()
{
    delete m_materialModel;
    m_materialModel = new MaterialModel(this);
    connectModel(m_materialModel);
}

void ApplicationModels::createSampleModel()
{
    ASSERT(m_materialModel);
    delete m_sampleModel;
    m_sampleModel = new SampleModel(this);
    connectModel(m_sampleModel);
}

void ApplicationModels::createInstrumentModel()
{
    delete m_instrumentModel;
    m_instrumentModel = new InstrumentModel(this);
    connectModel(m_instrumentModel);
}

void ApplicationModels::createRealDataModel()
{
    delete m_realDataModel;
    m_realDataModel = new RealDataModel(this);
    connectModel(m_realDataModel);
}

void ApplicationModels::createJobModel()
{
    delete m_jobModel;
    m_jobModel = new JobModel(this);
    connectModel(m_jobModel);
}

void ApplicationModels::createTestSample()
{
    SampleBuilderFactory factory;
    const std::unique_ptr<MultiLayer> P_sample(factory.createSample("CylindersAndPrismsBuilder"));

    GUIObjectBuilder::populateSampleModel(m_sampleModel, m_materialModel, *P_sample);

    // to populate InstrumentView with predefined instrument
    const std::unique_ptr<OffSpecSimulation> simulation(StandardSimulations::MiniOffSpec());
    GUIObjectBuilder::populateInstrumentModel(m_instrumentModel, *simulation);
}

void ApplicationModels::createTestJob()
{
    SimulationOptionsItem* optionsItem = m_documentModel->simulationOptionsItem();

    JobItem* jobItem = m_jobModel->addJob(m_sampleModel->multiLayerItem(),
                                          m_instrumentModel->instrumentItem(), 0, optionsItem);
    m_jobModel->runJob(jobItem->index());
}

void ApplicationModels::createTestRealData()
{
    auto realDataItem = dynamic_cast<RealDataItem*>(m_realDataModel->insertNewItem("RealData"));
    realDataItem->setItemName("realdata");

    std::unique_ptr<OutputData<double>> data(
        IntensityDataIOFactory::readOutputData("/home/pospelov/untitled2.int"));

    realDataItem->setOutputData(ImportDataUtils::CreateSimplifiedOutputData(*data.get()).release());
}

//! Writes all model in file one by one

void ApplicationModels::writeTo(QXmlStreamWriter* writer)
{
    for (auto model : modelList())
        model->writeTo(writer);
}

void ApplicationModels::readFrom(QXmlStreamReader* reader, MessageService* messageService)
{
    for (auto model : modelList()) {
        if (model->getModelTag() == reader->name()) {
            model->readFrom(reader, messageService);
            break;
        }
    }

    m_materialPropertyController->onMaterialModelLoad();
}

//! Returns the list of all GUI models

QList<SessionModel*> ApplicationModels::modelList()
{
    QList<SessionModel*> result;
    result.append(m_documentModel);
    result.append(m_materialModel);
    result.append(m_instrumentModel);
    result.append(m_sampleModel);
    result.append(m_realDataModel);
    result.append(m_jobModel);
    return result;
}

QVector<SessionItem*> ApplicationModels::nonXMLData() const
{
    ASSERT(m_realDataModel && m_jobModel && m_instrumentModel);
    return QVector<SessionItem*>() << m_realDataModel->nonXMLData() << m_jobModel->nonXMLData()
                                   << m_instrumentModel->nonXMLData();
}

void ApplicationModels::disconnectModel(SessionModel* model)
{
    if (model) {
        disconnect(model, &SessionModel::dataChanged, this, &ApplicationModels::modelChanged);
        disconnect(model, &SessionModel::rowsRemoved, this, &ApplicationModels::modelChanged);
        disconnect(model, &SessionModel::rowsInserted, this, &ApplicationModels::modelChanged);
    }
}

void ApplicationModels::connectModel(SessionModel* model)
{
    if (model) {
        connect(model, &SessionModel::dataChanged, this, &ApplicationModels::modelChanged,
                Qt::UniqueConnection);
        connect(model, &SessionModel::rowsRemoved, this, &ApplicationModels::modelChanged,
                Qt::UniqueConnection);
        connect(model, &SessionModel::rowsInserted, this, &ApplicationModels::modelChanged,
                Qt::UniqueConnection);
    }
}
