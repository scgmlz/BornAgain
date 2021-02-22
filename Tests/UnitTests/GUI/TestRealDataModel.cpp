#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/RealDataModel.h"
#include "Tests/GTestWrapper/google_test.h"
#include <QSignalSpy>

class TestRealDataModel : public ::testing::Test {
};

//! Checks that LinkInstrumentManager listens instrument model.

TEST_F(TestRealDataModel, test_realDataAddedRemoved)
{
    RealDataModel model;

    QSignalSpy spy(&model, SIGNAL(realDataAddedOrRemoved()));
    ASSERT_TRUE(spy.isValid());

    // populating model
    model.insertIntensityDataItem();

    // checking that a signal was emitted about the new item
    EXPECT_EQ(spy.count(), 1);

    // removing
    model.removeRow(0);
    EXPECT_EQ(spy.count(), 2);

    model.insertRealDataItem();
    EXPECT_EQ(spy.count(), 3);

    model.insertSpecularDataItem();
    EXPECT_EQ(spy.count(), 4);
}
