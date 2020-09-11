#include "GUI/coregui/Models/ApplicationModels.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/JobItemUtils.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/RealDataModel.h"
#include "GUI/coregui/mainwindow/ProjectUtils.h"
#include "GUI/coregui/mainwindow/projectdocument.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "Tests/GTestWrapper/google_test.h"
#include "Tests/UnitTests/GUI/Utils.h"
#include <QFileInfo>
#include <QSignalSpy>

class TestProjectDocument : public ::testing::Test
{
protected:
    //! helper method to modify something in a model
    void modify_models(ApplicationModels* models)
    {
        auto instrument = models->instrumentModel()->instrumentItem();
        instrument->setItemValue(InstrumentItem::P_IDENTIFIER, GUIHelpers::createUuid());
    }
};

TEST_F(TestProjectDocument, test_documentFlags)
{
    ProjectFlags::DocumentStatus flags;
    EXPECT_FALSE(flags.testFlag(ProjectFlags::STATUS_OK));
    EXPECT_FALSE(flags.testFlag(ProjectFlags::STATUS_WARNING));
    EXPECT_FALSE(flags.testFlag(ProjectFlags::STATUS_FAILED));

    ProjectFlags::setFlag(flags, ProjectFlags::STATUS_WARNING);
    EXPECT_FALSE(flags.testFlag(ProjectFlags::STATUS_OK));
    EXPECT_TRUE(flags.testFlag(ProjectFlags::STATUS_WARNING));
    EXPECT_FALSE(flags.testFlag(ProjectFlags::STATUS_FAILED));

    // flags.setFlag(ProjectFlags::STATUS_OK); // only in Qt5.7
    ProjectFlags::setFlag(flags, ProjectFlags::STATUS_OK);
    EXPECT_TRUE(flags.testFlag(ProjectFlags::STATUS_OK));
    EXPECT_TRUE(flags.testFlag(ProjectFlags::STATUS_WARNING));
    EXPECT_FALSE(flags.testFlag(ProjectFlags::STATUS_FAILED));

    ProjectFlags::DocumentStatus flags2(ProjectFlags::STATUS_WARNING | ProjectFlags::STATUS_FAILED);
    EXPECT_FALSE(flags2.testFlag(ProjectFlags::STATUS_OK));
    EXPECT_TRUE(flags2.testFlag(ProjectFlags::STATUS_WARNING));
    EXPECT_TRUE(flags2.testFlag(ProjectFlags::STATUS_FAILED));

    ProjectDocument document;
    EXPECT_TRUE(document.documentStatus() == ProjectFlags::STATUS_OK);
    EXPECT_TRUE(document.isReady());
    EXPECT_FALSE(document.hasWarnings());
    EXPECT_FALSE(document.hasErrors());
}

TEST_F(TestProjectDocument, test_projectDocument)
{
    const QString projectDir("test_projectDocument");
    GuiUnittestUtils::create_dir(projectDir);
    const QString projectFileName(projectDir + "/document.pro");

    ApplicationModels models;
    ProjectDocument document;
    document.setApplicationModels(&models);

    // Checking initial document status
    EXPECT_TRUE(document.isModified() == false);
    EXPECT_TRUE(document.hasValidNameAndPath() == false);
    EXPECT_EQ(document.projectDir(), QString());
    EXPECT_EQ(document.projectName(), QString());
    EXPECT_EQ(document.projectFileName(), QString());

    // Checking document name and isModified status after project save
    document.save(projectFileName);
    EXPECT_TRUE(document.hasValidNameAndPath());
    EXPECT_EQ(document.projectDir(), projectDir);
    EXPECT_EQ(document.projectName(), "document");
    EXPECT_EQ(document.projectFileName(), projectFileName);
    EXPECT_FALSE(document.isModified());

    QSignalSpy spyDocument(&document, SIGNAL(modified()));
    EXPECT_EQ(spyDocument.count(), 0);

    // Changing document and checking its status
    modify_models(&models);
    EXPECT_TRUE(document.isModified());
    EXPECT_EQ(spyDocument.count(), 1);

    // Saving document
    document.save(projectFileName);
    EXPECT_FALSE(document.isModified());
    EXPECT_EQ(spyDocument.count(), 2); // save triggers 'modified' signal

    QFileInfo info(projectFileName);
    EXPECT_TRUE(info.exists());
}

TEST_F(TestProjectDocument, test_projectDocumentWithData)
{
    const QString projectDir("test_projectDocumentWithData");
    GuiUnittestUtils::create_dir(projectDir);

    ApplicationModels models;
    RealDataItem* realData = GuiUnittestUtils::createRealData("RealData", *models.realDataModel());
    ASSERT(realData);
    DataItem* intensityItem = realData->dataItem();
    JobItemUtils::createDefaultDetectorMap(intensityItem,
                                           models.instrumentModel()->instrumentItem());
    intensityItem->setItemValue(DataItem::P_FILE_NAME, "realdata.int.gz");

    ProjectDocument document;
    document.setApplicationModels(&models);
    document.save(projectDir + "/untitled.pro");

    QFileInfo info(projectDir + "/untitled.pro");
    EXPECT_TRUE(info.exists());

    info.setFile(projectDir + "/realdata.int.gz");
    EXPECT_TRUE(info.exists());
}
