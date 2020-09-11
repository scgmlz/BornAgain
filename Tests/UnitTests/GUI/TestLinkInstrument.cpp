#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/JobItemUtils.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/RealDataModel.h"
#include "GUI/coregui/Models/RectangularDetectorItem.h"
#include "GUI/coregui/Views/ImportDataWidgets/LinkInstrumentManager.h"
#include "Tests/GTestWrapper/google_test.h"
#include "Tests/UnitTests/GUI/Utils.h"
#include <QSignalSpy>
#include <QTest>

class TestLinkInstrument : public ::testing::Test
{
};

//! Checks that LinkInstrumentManager listens instrument model.

TEST_F(TestLinkInstrument, test_linkInstrumentManager)
{
    InstrumentModel instrumentModel;
    RealDataModel realDataModel;
    LinkInstrumentManager manager;
    manager.setModels(&instrumentModel, &realDataModel);

    // initial state of LinkInstrumentManager
    EXPECT_EQ(manager.instrumentNames(), QStringList() << "Undefined");
    QSignalSpy spy(&manager, SIGNAL(instrumentMapUpdated()));

    // populating instrument model
    GISASInstrumentItem* instrument =
        dynamic_cast<GISASInstrumentItem*>(instrumentModel.insertNewItem("GISASInstrument"));
    QString identifier = instrument->getItemValue(InstrumentItem::P_IDENTIFIER).toString();

    // checking that LinkInstrumentManager was notified about new instrument
    EXPECT_EQ(spy.count(), 1);
    EXPECT_EQ(manager.instrumentNames(), QStringList() << "Undefined" << instrument->itemName());

    EXPECT_EQ(manager.getInstrument(identifier), instrument);
    EXPECT_EQ(manager.instrumentComboIndex(identifier), 1);

    // removing instrument
    instrumentModel.removeRow(0);
    EXPECT_EQ(spy.count(), 2);
    EXPECT_EQ(manager.instrumentNames(), QStringList() << "Undefined");
    QVERIFY(manager.getInstrument(identifier) == nullptr);
    EXPECT_EQ(manager.instrumentComboIndex(identifier), -1);
}

TEST_F(TestLinkInstrument, test_canLinkToInstrument)
{
    InstrumentModel instrumentModel;
    RealDataModel realDataModel;
    LinkInstrumentManager manager;
    manager.setModels(&instrumentModel, &realDataModel);

    // populating instrument model
    GISASInstrumentItem* instrument =
        dynamic_cast<GISASInstrumentItem*>(instrumentModel.insertNewItem("GISASInstrument"));
    QString identifier = instrument->getItemValue(InstrumentItem::P_IDENTIFIER).toString();

    // populating real data model, setting intensity data
    RealDataItem* realData = GuiUnittestUtils::createRealData("RealData", realDataModel);
    JobItemUtils::createDefaultDetectorMap(realData->dataItem(), instrument);

    QVERIFY(manager.canLinkDataToInstrument(realData, identifier));

    // making link
    realData->setItemValue(RealDataItem::P_INSTRUMENT_ID, identifier);
    EXPECT_EQ(manager.linkedItems(instrument), QList<RealDataItem*>() << realData);

    // changing detector type and checking that link remain
    instrument->setDetectorGroup("RectangularDetector");
    EXPECT_EQ(manager.linkedItems(instrument), QList<RealDataItem*>() << realData);

    // changing detector binning and checking that link is destroyed
    DetectorItem* detectorItem = instrument->detectorItem();
    auto& x_axis = detectorItem->item<BasicAxisItem>(RectangularDetectorItem::P_X_AXIS);
    x_axis.setItemValue(BasicAxisItem::P_NBINS, 10);

    EXPECT_EQ(manager.linkedItems(instrument), QList<RealDataItem*>());
    EXPECT_EQ(realData->getItemValue(RealDataItem::P_INSTRUMENT_ID).toString(), QString());
}
