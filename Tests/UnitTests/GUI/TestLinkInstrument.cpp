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

class TestLinkInstrument : public ::testing::Test {
};

TEST_F(TestLinkInstrument, test_canLinkToInstrument)
{
    InstrumentModel instrumentModel;
    RealDataModel realDataModel;
    LinkInstrumentManager manager;
    manager.setModels(&instrumentModel, &realDataModel);

    // populating instrument model
    auto instrument = instrumentModel.insertItem<GISASInstrumentItem>();
    const QString identifier = instrument->id();

    // populating real data model, setting intensity data
    RealDataItem* realData = GuiUnittestUtils::createRealData("RealData", realDataModel);
    JobItemUtils::createDefaultDetectorMap(realData->dataItem(), instrument);

    QVERIFY(manager.canLinkDataToInstrument(realData, identifier));

    // making link
    realData->setInstrumentId(identifier);
    EXPECT_EQ(manager.linkedRealDataItems(instrument), QList<RealDataItem*>() << realData);

    // changing detector type and checking that link remain
    instrument->setDetectorGroup("RectangularDetector");
    EXPECT_EQ(manager.linkedRealDataItems(instrument), QList<RealDataItem*>() << realData);

    // changing detector binning and checking that link is destroyed
    DetectorItem* detectorItem = instrument->detectorItem();
    auto x_axis = detectorItem->item<BasicAxisItem>(RectangularDetectorItem::P_X_AXIS);
    x_axis->setItemValue(BasicAxisItem::P_NBINS, 10);

    EXPECT_EQ(manager.linkedRealDataItems(instrument), QList<RealDataItem*>());
    EXPECT_EQ(realData->instrumentId(), QString());
}
