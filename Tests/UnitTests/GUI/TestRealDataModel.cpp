#include "Base/Axis/PointwiseAxis.h"
#include "GUI/coregui/Models/DataItem.h"
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

TEST_F(TestRealDataModel, test_removeNativeData)
{
    RealDataModel model;

    auto item = model.insertSpecularDataItem();
    ASSERT_EQ(item->nativeData(), nullptr);

    item->initNativeData();
    ASSERT_NE(item->nativeData(), nullptr);
    ASSERT_FALSE(item->hasNativeData());
    ASSERT_EQ(item->nativeData()->getOutputData(), nullptr);

    // call remove while no output data set yet
    item->removeNativeData();
    ASSERT_NE(item->nativeData(), nullptr);
    ASSERT_FALSE(item->hasNativeData());
    ASSERT_EQ(item->nativeData()->getOutputData(), nullptr);

    // add data
    OutputData<double>* oData = new OutputData<double>();
    oData->addAxis(PointwiseAxis("qVector", std::vector<double>({1, 2})));
    oData->setRawDataVector(std::vector<double>({3, 4}));
    item->nativeData()->setOutputData(oData); // takes ownership of odata
    ASSERT_TRUE(item->hasNativeData());
    ASSERT_NE(item->nativeData()->getOutputData(), nullptr);

    // call remove with existing output data
    item->removeNativeData();
    ASSERT_NE(item->nativeData(), nullptr);
    ASSERT_FALSE(item->hasNativeData());
    ASSERT_EQ(item->nativeData()->getOutputData(), nullptr);
}
