#include "GUI/coregui/Models/DataItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "Tests/GTestWrapper/google_test.h"
#include <QTest>

class TestDataItems : public ::testing::Test
{
public:
    void testItemClock(QString type);
};

void TestDataItems::testItemClock(QString model_type)
{
    SessionModel model("TempModel");
    DataItem* item = dynamic_cast<DataItem*>(model.insertNewItem(model_type));

    QDateTime time = QDateTime::currentDateTime();
    item->setLastModified(time);
    EXPECT_EQ(time, item->lastModified());

    const int nap_time(20);
    QTest::qSleep(nap_time);

    // changing item (file name)
    item->setItemValue(DataItem::P_FILE_NAME, "name.txt");
    QDateTime time2 = item->lastModified();
    EXPECT_TRUE(time.msecsTo(time2) > nap_time / 2);

    QTest::qSleep(nap_time);

    // changing item (OutputData)
    item->emitDataChanged();
    QDateTime time3 = item->lastModified();
    EXPECT_TRUE(time2.msecsTo(time3) > nap_time / 2);
}

TEST_F(TestDataItems, testSpecularItemClock)
{
    testItemClock("SpecularData");
}

TEST_F(TestDataItems, testIntensityItemClock)
{
    testItemClock("IntensityData");
}
