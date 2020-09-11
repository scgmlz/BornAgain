// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/Other/SaveLoadProject.cpp
//! @brief     Implements SaveLoadProject test.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/GUI/Other/SaveLoadProject.h"
#include "BATesting.h"
#include "Core/Basics/Assert.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/StandardSamples/SampleBuilderFactory.h"
#include "Core/Tools/FileSystemUtils.h"
#include "GUI/coregui/Models/ApplicationModels.h"
#include "GUI/coregui/Models/DetectorItems.h"
#include "GUI/coregui/Models/DocumentModel.h"
#include "GUI/coregui/Models/GUIObjectBuilder.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Models/SimulationOptionsItem.h"
#include "GUI/coregui/mainwindow/ProjectUtils.h"
#include "GUI/coregui/mainwindow/projectdocument.h"
#include "GUI/coregui/utils/MessageService.h"
#include <QCoreApplication>
#include <QElapsedTimer>
#include <QXmlStreamWriter>

namespace
{
const QString sample_name = "ParticleCompositionBuilder";
const QString project_name = "untitled.pro";
const int failure = 1;
const int success = 0;

QString path(const QString& projectName)
{
    return QString::fromStdString(
        FileSystemUtils::jointPath(BATesting::GUIOutputDir(), projectName.toStdString()));
}
} // namespace

GUISaveLoadProject::GUISaveLoadProject() : m_models(new ApplicationModels) {}

GUISaveLoadProject::~GUISaveLoadProject() = default;

bool GUISaveLoadProject::runTest()
{
    int nerr(0);

    QString projectName1(path("test_GUISaveLoadProject_1"));
    QString projectName2(path("test_GUISaveLoadProject_2"));

    // running simulation to fill models with fresh data
    nerr += run_job();

    // saving project
    nerr += save_project(projectName1);

    // loading project back to models
    nerr += load_project(projectName1);

    // saving under different name what we've just loaded
    nerr += save_project(projectName2);

    // analyze difference
    nerr += check_difference(projectName1, projectName2);

    return nerr == 0 ? true : false;
}

int GUISaveLoadProject::run_job()
{
    resetModels();

    std::cout << "GUISaveLoadProject::run_job()" << std::endl;

    SimulationOptionsItem* optionsItem = m_models->documentModel()->simulationOptionsItem();

    SampleBuilderFactory factory;
    const std::unique_ptr<MultiLayer> sample(factory.createSample(sample_name.toStdString()));

    GUIObjectBuilder::populateSampleModel(m_models->sampleModel(), m_models->materialModel(),
                                          *sample);

    auto instrument2DItem =
        dynamic_cast<Instrument2DItem*>(m_models->instrumentModel()->instrumentItem());
    ASSERT(instrument2DItem);
    instrument2DItem->detectorItem()->setXSize(50);
    instrument2DItem->detectorItem()->setYSize(50);

    auto jobItem =
        m_models->jobModel()->addJob(m_models->sampleModel()->multiLayerItem(),
                                     m_models->instrumentModel()->instrumentItem(), 0, optionsItem);

    m_models->jobModel()->runJob(jobItem->index());

    while (m_models->jobModel()->hasUnfinishedJobs()) {
        QElapsedTimer timer;
        timer.start();
        while (timer.elapsed() < 10)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
    }

    std::cout << "... job finished." << std::endl;
    return jobItem->isCompleted() ? 0 : 1;
}

//! Saves models to project directory and as xml string for later analysis.

int GUISaveLoadProject::save_project(const QString& projectName)
{
    int nerr(0);
    nerr += save_project_dir(projectName);
    nerr += save_xml(projectName);
    return nerr;
}

//! Saves project in directory.

int GUISaveLoadProject::save_project_dir(const QString& projectName)
{
    std::cout << "GUISaveLoadProject::save_project() -> Saving to " << projectName.toStdString()
              << std::endl;

    if (ProjectUtils::exists(projectName))
        ProjectUtils::removeRecursively(projectName);

    FileSystemUtils::createDirectories(projectName.toStdString());

    ProjectDocument document;
    document.setApplicationModels(m_models.get());
    document.save(projectName + "/" + project_name);

    std::cout << "... saved." << std::endl;

    return success;
}

//! Sets all model xml content to the map for later analysis.

int GUISaveLoadProject::save_xml(const QString& projectName)
{
    for (auto model : m_models->modelList())
        m_results[projectName].push_back(dataXML(model));

    return success;
}

int GUISaveLoadProject::load_project(const QString& projectName)
{
    resetModels();

    std::cout << "GUISaveLoadProject::load_project() -> Loading from " << projectName.toStdString()
              << std::endl;

    MessageService logger;
    ProjectDocument document;
    document.setApplicationModels(m_models.get());
    document.setLogger(&logger);
    document.load(projectName + "/" + project_name);

    std::cout << "... loaded." << std::endl;
    return success;
}

int GUISaveLoadProject::check_difference(const QString& projectName1, const QString& projectName2)
{
    std::cout << "GUISaveLoadProject::check_difference -> Checking difference of \n"
              << projectName1.toStdString() << "' - initially saved project \n"
              << projectName2.toStdString() << "' - loaded and then saved. \n";

    auto project1 = m_results[projectName1];
    auto project2 = m_results[projectName2];

    if (project1.size() != project2.size()) {
        std::cout << "Number of models in project differs. Failed. \n";
        return failure;
    }

    int err(0);
    for (int i = 0; i < project1.size(); ++i) {
        DataXML model_data1 = project1[i];
        DataXML model_data2 = project2[i];

        if (model_data1.m_model_tag != model_data2.m_model_tag) {
            std::cout << "Error, different tags. " << model_data1.m_model_tag.toStdString()
                      << model_data2.m_model_tag.toStdString() << "\n";
            err++;
        }

        if (model_data1.m_model_xml != model_data2.m_model_xml) {
            std::cout << "Error, different xml in model '" << model_data1.m_model_tag.toStdString()
                      << "'\n";
            err++;
        }
    }

    return err > 0 ? failure : success;
}

//! Returns DataXML from the model.

GUISaveLoadProject::DataXML GUISaveLoadProject::dataXML(SessionModel* model)
{
    DataXML result;

    result.m_model_tag = model->getModelTag();
    QXmlStreamWriter writer(&result.m_model_xml);
    model->writeTo(&writer);

    return result;
}

void GUISaveLoadProject::resetModels()
{
    m_models.reset(); // first have to delete original model
    m_models.reset(new ApplicationModels);
}
