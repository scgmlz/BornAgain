// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ApplicationModels.h
//! @brief     Defines class holding all application models
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_APPLICATIONMODELS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_APPLICATIONMODELS_H

#include "Wrap/WinDllMacros.h"
#include <QObject>

class SessionModel;
class SessionItem;
class DocumentModel;
class MaterialModel;
class InstrumentModel;
class RealDataModel;
class SampleModel;
class JobModel;
class MaterialPropertyController;
class MessageService;

class BA_CORE_API_ ApplicationModels : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationModels(QObject* parent = nullptr);
    ~ApplicationModels();

    DocumentModel* documentModel();
    MaterialModel* materialModel();
    InstrumentModel* instrumentModel();
    SampleModel* sampleModel();
    RealDataModel* realDataModel();
    JobModel* jobModel();

    void resetModels();

    void createTestSample();
    void createTestJob();
    void createTestRealData();

    void writeTo(class QXmlStreamWriter* writer);
    void readFrom(class QXmlStreamReader* reader, MessageService* messageService);

    QList<SessionModel*> modelList();

    QVector<SessionItem*> nonXMLData() const;

signals:
    void modelChanged();

private:
    void createModels();
    void createDocumentModel();
    void createMaterialModel();
    void createInstrumentModel();
    void createSampleModel();
    void createRealDataModel();
    void createJobModel();

    void disconnectModel(SessionModel* model);
    void connectModel(SessionModel* model);

    DocumentModel* m_documentModel;
    MaterialModel* m_materialModel;
    InstrumentModel* m_instrumentModel;
    SampleModel* m_sampleModel;
    RealDataModel* m_realDataModel;
    JobModel* m_jobModel;
    MaterialPropertyController* m_materialPropertyController;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_APPLICATIONMODELS_H
