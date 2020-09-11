#include "GUI/coregui/Models/ApplicationModels.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/JobItemUtils.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/RealDataModel.h"
#include "GUI/coregui/mainwindow/AutosaveController.h"
#include "GUI/coregui/mainwindow/ProjectUtils.h"
#include "GUI/coregui/mainwindow/SaveService.h"
#include "GUI/coregui/mainwindow/projectdocument.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "Tests/GTestWrapper/google_test.h"
#include "Tests/UnitTests/GUI/Utils.h"
#include <QSignalSpy>

class TestSaveService : public ::testing::Test
{
protected:
    // helper method to modify something in a model
    void modify_models(ApplicationModels* models)
    {
        auto instrument = models->instrumentModel()->instrumentItem();
        instrument->setItemValue(InstrumentItem::P_IDENTIFIER, GUIHelpers::createUuid());
    }
    const int m_save_wait = 10000;
};

//! Testing AutosaveController. It watches ProjectDocument and sends autosaveRequest() when
//! number of document changes has been accumulated.

TEST_F(TestSaveService, test_autoSaveController)
{
    const QString projectDir("test_autoSaveController");
    GuiUnittestUtils::create_dir(projectDir);

    const QString projectFileName(projectDir + "/document.pro");

    const int autosave_time(100);

    ApplicationModels models;
    std::unique_ptr<ProjectDocument> document(new ProjectDocument);
    document->setApplicationModels(&models);
    document->save(projectFileName);

    // setting up autosave
    AutosaveController autosave;
    autosave.setAutosaveTime(autosave_time);
    autosave.setDocument(document.get());

    // checking proposed autosave directory
    EXPECT_EQ(autosave.autosaveDir(), QString(projectDir + "/autosave"));
    EXPECT_EQ(autosave.autosaveName(), QString(projectDir + "/autosave/document.pro"));

    QSignalSpy spyAutosave(&autosave, SIGNAL(autosaveRequest()));

    // modify document once and check that autosave directory was created
    modify_models(&models);
    EXPECT_TRUE(document->isModified());
    EXPECT_TRUE(spyAutosave.wait(m_save_wait));
    EXPECT_EQ(spyAutosave.count(), 1);
    EXPECT_TRUE(ProjectUtils::exists(autosave.autosaveDir()));

    // saving document and checking that autosave is not triggered
    document->save(projectFileName);
    EXPECT_FALSE(document->isModified());
    EXPECT_EQ(spyAutosave.count(), 1);

    // modify several times and check than autosave was triggered only once
    for (size_t i = 0; i < 10; ++i)
        modify_models(&models);

    EXPECT_TRUE(spyAutosave.wait(m_save_wait));
    EXPECT_EQ(spyAutosave.count(), 2);

    // remove autosave dir
    autosave.removeAutosaveDir();
    EXPECT_FALSE(ProjectUtils::exists(autosave.autosaveDir()));
}

//! AutosaveController shouldn't trigger autosaveRequest() if document has no name.

TEST_F(TestSaveService, test_autoSaveControllerNewDocument)
{
    ApplicationModels models;
    std::unique_ptr<ProjectDocument> document(new ProjectDocument);
    document->setApplicationModels(&models);

    const int autosave_time(100);

    AutosaveController autosave;
    autosave.setAutosaveTime(autosave_time);
    autosave.setDocument(document.get());

    QSignalSpy spyAutosave(&autosave, SIGNAL(autosaveRequest()));

    modify_models(&models);
    EXPECT_FALSE(spyAutosave.wait(autosave_time * 2));
    EXPECT_EQ(spyAutosave.count(), 0);
}

//! Testing SaveService on simple documents (no heavy data).
//! SaveService should be able to save project file and send documentSaved() signal.

TEST_F(TestSaveService, test_saveService)
{
    const QString projectDir("test_saveService");
    GuiUnittestUtils::create_dir(projectDir);
    const QString projectFileName(projectDir + "/document.pro");

    ApplicationModels models;
    std::unique_ptr<ProjectDocument> document(new ProjectDocument);
    document->setApplicationModels(&models);
    modify_models(&models);

    EXPECT_FALSE(ProjectUtils::exists(projectFileName));

    SaveService service;
    QSignalSpy spySaveService(&service, SIGNAL(projectSaved()));

    service.setDocument(document.get());
    service.save(projectFileName);

    EXPECT_EQ(spySaveService.count(), 1);
    EXPECT_TRUE(ProjectUtils::exists(projectFileName));

    // after save, document should be in non-modified state, project file name should be updated
    EXPECT_EQ(document->projectFileName(), projectFileName);
    EXPECT_FALSE(document->isModified());
}

//! Testing SaveService on documents having nonXML data.
//! SaveService should be able to save project file (in main thread) and project nonXML
//! in second thread.

TEST_F(TestSaveService, test_saveServiceWithData)
{
    const QString projectDir("test_saveServiceWithData");
    GuiUnittestUtils::create_dir(projectDir);
    const QString projectFileName(projectDir + "/document.pro");

    ApplicationModels models;
    RealDataItem* realData = GuiUnittestUtils::createRealData("RealData", *models.realDataModel());
    ASSERT(realData);
    DataItem* intensityItem = realData->dataItem();
    JobItemUtils::createDefaultDetectorMap(intensityItem,
                                           models.instrumentModel()->instrumentItem());
    intensityItem->setItemValue(DataItem::P_FILE_NAME, "realdata.int.gz");

    std::unique_ptr<ProjectDocument> document(new ProjectDocument);
    document->setApplicationModels(&models);

    EXPECT_FALSE(ProjectUtils::exists(projectFileName));

    SaveService service;
    QSignalSpy spySaveService(&service, SIGNAL(projectSaved()));

    service.setDocument(document.get());
    service.save(projectFileName);

    spySaveService.wait(m_save_wait); // waiting saving in a thread is complete

    EXPECT_EQ(spySaveService.count(), 1);
    EXPECT_TRUE(ProjectUtils::exists(projectFileName));
    EXPECT_TRUE(ProjectUtils::exists(projectDir + "/realdata.int.gz"));
    EXPECT_FALSE(document->isModified());
}

//! Testing SaveService when autosave is enabled.

TEST_F(TestSaveService, test_autosaveEnabled)
{
    const QString projectDir("test_autosaveEnabled");
    GuiUnittestUtils::create_dir(projectDir);
    const QString projectFileName(projectDir + "/document.pro");

    ApplicationModels models;
    RealDataItem* realData = GuiUnittestUtils::createRealData("RealData", *models.realDataModel());
    DataItem* intensityItem = realData->dataItem();
    JobItemUtils::createDefaultDetectorMap(intensityItem,
                                           models.instrumentModel()->instrumentItem());
    intensityItem->setItemValue(DataItem::P_FILE_NAME, "realdata.int.gz");

    std::unique_ptr<ProjectDocument> document(new ProjectDocument(projectFileName));
    document->setApplicationModels(&models);

    EXPECT_FALSE(document->isModified());

    SaveService service;
    service.setAutosaveEnabled(true);
    const int autosave_time(200);
    service.setAutosaveTime(autosave_time);
    service.setDocument(document.get());

    QSignalSpy spySaveService(&service, SIGNAL(projectSaved()));
    service.save(projectFileName);

    spySaveService.wait(m_save_wait); // waiting saving in a thread is complete
    EXPECT_EQ(spySaveService.count(), 1);
    EXPECT_FALSE(document->isModified());
    EXPECT_TRUE(ProjectUtils::exists(projectDir + "/document.pro"));
    EXPECT_TRUE(ProjectUtils::exists(projectDir + "/realdata.int.gz"));
    spySaveService.clear();

    // modify several times and check SaveService signals
    for (size_t i = 0; i < 10; ++i)
        modify_models(&models);

    EXPECT_TRUE(document->isModified());

    spySaveService.wait(m_save_wait); // waiting saving in a thread is complete
    EXPECT_EQ(spySaveService.count(), 1);

    EXPECT_TRUE(ProjectUtils::exists(projectDir + "/autosave/document.pro"));
    EXPECT_TRUE(ProjectUtils::exists(projectDir + "/autosave/realdata.int.gz"));

    // after autosave the project has to be still in modified state
    EXPECT_TRUE(document->isModified());
    // after autosave, project file name should remain the same
    EXPECT_EQ(document->projectFileName(), projectFileName);
}
