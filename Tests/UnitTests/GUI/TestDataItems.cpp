#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Models/SpecularDataItem.h"
#include "Tests/GTestWrapper/google_test.h"
#include <QTest>

class TestDataItems : public ::testing::Test {
public:
    template <typename T> void testItemClock()
    {
        SessionModel model("TempModel");
        auto item = model.insertItem<T>();

        QDateTime time = QDateTime::currentDateTime();
        item->setLastModified(time);
        EXPECT_EQ(time, item->lastModified());

        const int nap_time(20);
        QTest::qSleep(nap_time);

        // changing item (file name)
        item->setFileName("name.txt");
        QDateTime time2 = item->lastModified();
        EXPECT_TRUE(time.msecsTo(time2) > nap_time / 2);

        QTest::qSleep(nap_time);

        // changing item (OutputData)
        item->emitDataChanged();
        QDateTime time3 = item->lastModified();
        EXPECT_TRUE(time2.msecsTo(time3) > nap_time / 2);
    }
};

TEST_F(TestDataItems, testSpecularItemClock)
{
    testItemClock<SpecularDataItem>();
}

TEST_F(TestDataItems, testIntensityItemClock)
{
    testItemClock<IntensityDataItem>();
}
