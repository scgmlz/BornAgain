//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Models/ApplicationModels.cpp
//! @brief     Defines class holding all application models
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Models/ApplicationModels.h"
#include "Core/Simulation/OffSpecularSimulation.h"
#include "Core/Simulation/StandardSimulations.h"
#include "Device/Histo/IntensityDataIOFactory.h"
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
#include "GUI/coregui/Models/SimulationOptionsItem.h"
#include "GUI/coregui/Views/ImportDataWidgets/ImportDataUtils.h"
#include "GUI/coregui/utils/MessageService.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/StandardSamples/SampleBuilderFactory.h"
#include <QtCore/QXmlStreamWriter>

ApplicationModels::ApplicationModels(QObject* parent)
    : QObject(parent)
    , m_documentModel(nullptr)
    , m_materialModel(nullptr)
    , m_instrumentModel(nullptr)
    , m_sampleModel(nullptr)
    , m_realDataModel(nullptr)
    , m_jobModel(nullptr)
    , m_materialPropertyController(new MaterialPropertyController(this))
{
    //! creates and initializes models, order is important
    m_documentModel = new DocumentModel(this);
    m_materialModel = new MaterialModel(this);
    m_sampleModel = new SampleModel(this);
    m_instrumentModel = new InstrumentModel(this);
    m_realDataModel = new RealDataModel(this);
    m_jobModel = new JobModel(this);

    m_realDataModel->setInstrumentModel(m_instrumentModel);

    connectModel(m_documentModel);
    connectModel(m_materialModel);
    connectModel(m_sampleModel);
    connectModel(m_instrumentModel);
    connectModel(m_realDataModel);
    connectModel(m_jobModel);

    resetModels();

    m_materialPropertyController->setModels(materialModel(), sampleModel());
}

ApplicationModels::~ApplicationModels() = default;

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
    m_documentModel->insertItem<SimulationOptionsItem>();

    m_materialModel->clear();
    m_materialModel->addRefractiveMaterial("Default", 1e-3, 1e-5);
    m_materialModel->addRefractiveMaterial("Vacuum", 0.0, 0.0);
    m_materialModel->addRefractiveMaterial("Particle", 6e-4, 2e-8);
    m_materialModel->addRefractiveMaterial("Substrate", 6e-6, 2e-8);

    m_sampleModel->clear();

    m_realDataModel->clear();

    m_jobModel->clear();

    m_instrumentModel->clear();
    auto instrument = m_instrumentModel->insertItem<GISASInstrumentItem>();
    instrument->setItemName("GISAS");
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

QVector<SessionItem*> ApplicationModels::nonXMLItems() const
{
    ASSERT(m_realDataModel && m_jobModel && m_instrumentModel);
    return QVector<SessionItem*>() << m_realDataModel->nonXMLItems() << m_jobModel->nonXMLItems()
                                   << m_instrumentModel->nonXMLItems();
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
