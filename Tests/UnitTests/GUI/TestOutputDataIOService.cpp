#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "Core/Intensity/OutputData.h"
#include "GUI/coregui/Models/ApplicationModels.h"
#include "GUI/coregui/Models/DataItem.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobItemUtils.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Models/JobModelFunctions.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/RealDataModel.h"
#include "GUI/coregui/mainwindow/OutputDataIOHistory.h"
#include "GUI/coregui/mainwindow/OutputDataIOService.h"
#include "GUI/coregui/mainwindow/ProjectUtils.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "GUI/coregui/utils/ImportDataInfo.h"
#include "Tests/GTestWrapper/google_test.h"
#include "Tests/UnitTests/GUI/Utils.h"
#include <QTest>
#include <memory>

class TestOutputDataIOService : public ::testing::Test
{
protected:
    TestOutputDataIOService();
    OutputData<double> m_data;
};

TestOutputDataIOService::TestOutputDataIOService()
{
    FixedBinAxis axis0("x", 10, 0.0, 1.0);
    FixedBinAxis axis1("y", 10, -1.0, 1.0);
    m_data.addAxis(axis0);
    m_data.addAxis(axis1);
}

//! Test methods for retrieving nonXML data.

TEST_F(TestOutputDataIOService, test_nonXMLData)
{
    ApplicationModels models;

    // initial state
    auto dataItems = models.nonXMLData();
    EXPECT_EQ(dataItems.size(), 0);

    // adding RealDataItem
    RealDataItem* realData =
        dynamic_cast<RealDataItem*>(models.realDataModel()->insertNewItem("RealData"));
    EXPECT_EQ(models.realDataModel()->nonXMLData().size(), 0);
    realData->setOutputData(GuiUnittestUtils::createData().release());
    EXPECT_EQ(models.realDataModel()->nonXMLData().size(), 1);

    // adding JobItem
    SessionItem* jobItem = models.jobModel()->insertNewItem("JobItem");
    SessionItem* dataItem =
        models.jobModel()->insertNewItem("IntensityData", jobItem->index(), -1, JobItem::T_OUTPUT);
    EXPECT_EQ(models.jobModel()->nonXMLData().size(), 1);

    // adding RealDataItem to jobItem
    RealDataItem* realData2 = dynamic_cast<RealDataItem*>(
        models.jobModel()->insertNewItem("RealData", jobItem->index(), -1, JobItem::T_REALDATA));
    EXPECT_EQ(models.jobModel()->nonXMLData().size(), 1);
    realData2->setOutputData(
        GuiUnittestUtils::createData(0.0, GuiUnittestUtils::DIM::D1).release());
    EXPECT_EQ(models.jobModel()->nonXMLData().size(), 2);

    // checking data items of OutputDataIOService
    OutputDataIOService service(&models);
    EXPECT_EQ(service.nonXMLItems().size(), 3);

    // checking data items of ApplicationModels
    dataItems = models.nonXMLData();
    EXPECT_EQ(dataItems.size(), 3);
    EXPECT_EQ(dataItems.indexOf(realData->dataItem()), 0);
    EXPECT_EQ(dataItems.indexOf(dataItem), 1);
    EXPECT_EQ(dataItems.indexOf(realData2->dataItem()), 2);

    // Replacing the data inside RealDataItem with the data of the same dimensions
    realData->setOutputData(GuiUnittestUtils::createData(2.0).release());
    EXPECT_EQ(models.realDataModel()->nonXMLData().size(), 1);

    // Replacing the data inside RealDataItem with the data of different dimensions
    auto data = GuiUnittestUtils::createData(3.0, GuiUnittestUtils::DIM::D1);
    EXPECT_THROW(dynamic_cast<RealDataItem*>(realData)->setOutputData(data.get()),
                 GUIHelpers::Error);
    EXPECT_EQ(models.realDataModel()->nonXMLData().size(), 1);
}

//! Tests OutputDataSaveInfo class intended for storing info about the last save.

TEST_F(TestOutputDataIOService, test_OutputDataSaveInfo)
{
    SessionModel model("TempModel");
    DataItem* item = dynamic_cast<DataItem*>(model.insertNewItem("IntensityData"));

    item->setLastModified(QDateTime::currentDateTime());

    const int nap_time(10);
    QTest::qSleep(nap_time);

    OutputDataSaveInfo info = OutputDataSaveInfo::createSaved(item);
    EXPECT_TRUE(info.wasModifiedSinceLastSave() == false);

    QTest::qSleep(nap_time);
    item->setLastModified(QDateTime::currentDateTime());
    EXPECT_TRUE(info.wasModifiedSinceLastSave() == true);
}

//! Tests OutputDataDirHistory class intended for storing save history of several
//! IntensityDataItems in a directory.

TEST_F(TestOutputDataIOService, test_OutputDataDirHistory)
{
    SessionModel model("TempModel");
    DataItem* item1 = dynamic_cast<DataItem*>(model.insertNewItem("IntensityData"));

    DataItem* item2 = dynamic_cast<DataItem*>(model.insertNewItem("IntensityData"));
    item1->setOutputData(m_data.clone());
    item1->setLastModified(QDateTime::currentDateTime());
    item2->setLastModified(QDateTime::currentDateTime());

    // empty history
    OutputDataDirHistory history;
    EXPECT_TRUE(history.contains(item1) == false);
    // non-existing item is treated as modified
    EXPECT_TRUE(history.wasModifiedSinceLastSave(item1) == true);

    // Saving item in a history
    history.markAsSaved(item1);
    history.markAsSaved(item2);

    EXPECT_TRUE(history.contains(item1) == true);
    // Empty DataItems are not added to history:
    EXPECT_TRUE(history.contains(item2) == false);
    EXPECT_TRUE(history.wasModifiedSinceLastSave(item1) == false);

    // Attempt to save same item second time
    EXPECT_THROW(history.markAsSaved(item1), GUIHelpers::Error);

    // Modifying item
    QTest::qSleep(10);
    item1->setLastModified(QDateTime::currentDateTime());

    EXPECT_TRUE(history.wasModifiedSinceLastSave(item1) == true);
}

//! Tests OutputDataIOHistory class (save info for several independent directories).

TEST_F(TestOutputDataIOService, test_OutputDataIOHistory)
{
    SessionModel model("TempModel");
    DataItem* item1 = dynamic_cast<DataItem*>(model.insertNewItem("IntensityData"));

    DataItem* item2 = dynamic_cast<DataItem*>(model.insertNewItem("IntensityData"));
    item1->setOutputData(m_data.clone());
    item2->setOutputData(m_data.clone());

    item1->setLastModified(QDateTime::currentDateTime());
    item2->setLastModified(QDateTime::currentDateTime());

    OutputDataDirHistory dirHistory1;
    dirHistory1.markAsSaved(item1);
    dirHistory1.markAsSaved(item2);

    OutputDataDirHistory dirHistory2;
    dirHistory2.markAsSaved(item1);

    // Modifying item
    QTest::qSleep(10);
    item1->setLastModified(QDateTime::currentDateTime());

    // Creating two histories
    OutputDataIOHistory history;
    history.setHistory("dir1", dirHistory1);
    history.setHistory("dir2", dirHistory2);

    EXPECT_TRUE(history.wasModifiedSinceLastSave("dir1", item1) == true);
    EXPECT_TRUE(history.wasModifiedSinceLastSave("dir2", item1) == true);

    EXPECT_TRUE(history.wasModifiedSinceLastSave("dir1", item2) == false);
    EXPECT_TRUE(history.wasModifiedSinceLastSave("dir2", item2)
                == true); // since item2 doesn't exist

    // asking info for some non-existing directory
    EXPECT_THROW(history.wasModifiedSinceLastSave("dir3", item1), GUIHelpers::Error);
}

//! Testing saving abilities of OutputDataIOService class.

TEST_F(TestOutputDataIOService, test_OutputDataIOService)
{
    const QString projectDir("test_OutputDataIOService");
    GuiUnittestUtils::create_dir(projectDir);

    const double value1(1.0), value2(2.0), value3(3.0);

    ApplicationModels models;
    RealDataItem* realData1 =
        GuiUnittestUtils::createRealData("data1", *models.realDataModel(), value1);
    RealDataItem* realData2 =
        GuiUnittestUtils::createRealData("data2", *models.realDataModel(), value2);

    // Saving first time
    OutputDataIOService service(&models);
    service.save(projectDir);
    QTest::qSleep(10);

    // Checking existance of data on disk
    QString fname1 = "./" + projectDir + "/realdata_data1_0.int.gz";
    QString fname2 = "./" + projectDir + "/realdata_data2_0.int.gz";
    EXPECT_TRUE(ProjectUtils::exists(fname1));
    EXPECT_TRUE(ProjectUtils::exists(fname2));

    // Reading data from disk, checking it is the same
    std::unique_ptr<OutputData<double>> dataOnDisk1(
        IntensityDataIOFactory::readOutputData(fname1.toStdString()));
    std::unique_ptr<OutputData<double>> dataOnDisk2(
        IntensityDataIOFactory::readOutputData(fname2.toStdString()));
    EXPECT_TRUE(GuiUnittestUtils::isTheSame(*dataOnDisk1, *realData1->dataItem()->getOutputData()));
    EXPECT_TRUE(GuiUnittestUtils::isTheSame(*dataOnDisk2, *realData2->dataItem()->getOutputData()));

    // Modifying data and saving the project.
    realData2->setOutputData(GuiUnittestUtils::createData(value3).release());
    service.save(projectDir);
    QTest::qSleep(10);

    EXPECT_TRUE(GuiUnittestUtils::isTheSame(*dataOnDisk1, *realData1->dataItem()->getOutputData()));
    EXPECT_TRUE(GuiUnittestUtils::isTheSame(*dataOnDisk2, *realData2->dataItem()->getOutputData())
                == false);
    // checking that data on disk has changed
    dataOnDisk2.reset(IntensityDataIOFactory::readOutputData(fname2.toStdString()));
    EXPECT_TRUE(GuiUnittestUtils::isTheSame(*dataOnDisk2, *realData2->dataItem()->getOutputData()));

    // Renaming RealData and check that file on disk changed the name
    realData2->setItemName("data2new");
    service.save(projectDir);
    QTest::qSleep(10);

    QString fname2new = "./" + projectDir + "/realdata_data2new_0.int.gz";
    EXPECT_TRUE(ProjectUtils::exists(fname2new));
    EXPECT_TRUE(GuiUnittestUtils::isTheSame(fname2new, *realData2->dataItem()->getOutputData()));

    // Check that file with old name was removed.
    EXPECT_TRUE(ProjectUtils::exists(fname2) == false);
}

TEST_F(TestOutputDataIOService, test_RealDataItemWithNativeData)
{
    ApplicationModels models;

    // initial state
    auto dataItems = models.nonXMLData();
    EXPECT_EQ(dataItems.size(), 0);

    // adding RealDataItem
    RealDataItem* realData =
        dynamic_cast<RealDataItem*>(models.realDataModel()->insertNewItem("RealData"));
    EXPECT_EQ(models.realDataModel()->nonXMLData().size(), 0);

    ImportDataInfo import_data(std::unique_ptr<OutputData<double>>(m_data.clone()), "nbins");
    realData->setImportData(std::move(import_data));

    EXPECT_EQ(models.realDataModel()->nonXMLData().size(), 2);
    realData->setItemValue(RealDataItem::P_NAME, "RealData");

    // adding JobItem
    JobItem* jobItem = dynamic_cast<JobItem*>(models.jobModel()->insertNewItem("JobItem"));
    jobItem->setIdentifier(GUIHelpers::createUuid());
    models.jobModel()->insertNewItem("IntensityData", jobItem->index(), -1, JobItem::T_OUTPUT);
    EXPECT_EQ(models.jobModel()->nonXMLData().size(), 1);

    // copying RealDataItem to JobItem
    JobModelFunctions::copyRealDataItem(jobItem, realData);
    EXPECT_EQ(models.jobModel()->nonXMLData().size(), 3);

    // checking data items of OutputDataIOService
    OutputDataIOService service(&models);
    EXPECT_EQ(service.nonXMLItems().size(), 5);

    const QString projectDir("test_NativeData");
    GuiUnittestUtils::create_dir(projectDir);

    // Saving
    service.save(projectDir);
    QTest::qSleep(10);

    // Checking existance of data on disk
    auto data1 = realData->dataItem();
    auto data2 = realData->nativeData();
    auto data3 = jobItem->realDataItem()->dataItem();
    auto data4 = jobItem->realDataItem()->nativeData();

    QString fname1 = "./" + projectDir + "/" + data1->fileName();
    QString fname2 = "./" + projectDir + "/" + data2->fileName();
    QString fname3 = "./" + projectDir + "/" + data3->fileName();
    QString fname4 = "./" + projectDir + "/" + data4->fileName();

    EXPECT_TRUE(ProjectUtils::exists(fname1));
    EXPECT_TRUE(ProjectUtils::exists(fname2));
    EXPECT_TRUE(ProjectUtils::exists(fname3));
    EXPECT_TRUE(ProjectUtils::exists(fname4));

    auto readData = [](const QString& filename) {
        return std::unique_ptr<OutputData<double>>(
            IntensityDataIOFactory::readOutputData(filename.toStdString()));
    };

    // Reading data from disk, checking it is the same
    auto dataOnDisk1 = readData(fname1);
    auto dataOnDisk2 = readData(fname2);
    auto dataOnDisk3 = readData(fname3);
    auto dataOnDisk4 = readData(fname4);
    EXPECT_TRUE(GuiUnittestUtils::isTheSame(*dataOnDisk1, *data1->getOutputData()));
    EXPECT_TRUE(GuiUnittestUtils::isTheSame(*dataOnDisk2, *data2->getOutputData()));
    EXPECT_TRUE(GuiUnittestUtils::isTheSame(*dataOnDisk3, *data3->getOutputData()));
    EXPECT_TRUE(GuiUnittestUtils::isTheSame(*dataOnDisk4, *data4->getOutputData()));
}
