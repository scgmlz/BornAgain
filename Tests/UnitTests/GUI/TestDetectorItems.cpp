#include "Core/Basics/Units.h"
#include "Core/Detector/ConvolutionDetectorResolution.h"
#include "Core/Detector/IDetector2D.h"
#include "Core/Detector/ResolutionFunction2DGaussian.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/DetectorItems.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/RectangularDetectorItem.h"
#include "Tests/GTestWrapper/google_test.h"

class TestDetectorItems : public ::testing::Test
{
};

TEST_F(TestDetectorItems, test_detectorAlignment)
{
    InstrumentModel model;
    SessionItem* detector = model.insertNewItem("RectangularDetector");

    ComboProperty alignment =
        detector->getItemValue(RectangularDetectorItem::P_ALIGNMENT).value<ComboProperty>();
    // generic has some more items visible
    alignment.setValue("Generic");
    detector->setItemValue(RectangularDetectorItem::P_ALIGNMENT,
                           QVariant::fromValue<ComboProperty>(alignment));
    EXPECT_TRUE(detector->getItem(RectangularDetectorItem::P_NORMAL)->isVisible());

    // should be disabled if we switch
    alignment.setValue("Perpendicular to reflected beam");
    detector->setItemValue(RectangularDetectorItem::P_ALIGNMENT,
                           QVariant::fromValue<ComboProperty>(alignment));
    EXPECT_FALSE(detector->getItem(RectangularDetectorItem::P_NORMAL)->isVisible());
}

TEST_F(TestDetectorItems, test_resolutionFunction)
{
    InstrumentModel model;
    GISASInstrumentItem* instrument =
        dynamic_cast<GISASInstrumentItem*>(model.insertNewItem("GISASInstrument"));

    DetectorItem* detectorItem = instrument->detectorItem();

    detectorItem->setGroupProperty(DetectorItem::P_RESOLUTION_FUNCTION,
                                   "ResolutionFunction2DGaussian");

    auto detector = detectorItem->createDetector();
    auto convol =
        dynamic_cast<const ConvolutionDetectorResolution*>(detector->detectorResolution());
    auto gaussian =
        dynamic_cast<const ResolutionFunction2DGaussian*>(convol->getResolutionFunction2D());

    EXPECT_EQ(Units::rad2deg(gaussian->getSigmaX()), 0.02);
}
