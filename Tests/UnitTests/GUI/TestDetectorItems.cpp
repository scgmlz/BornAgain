#include "google_test.h"
#include "FlatDetectorItem.h"
#include "InstrumentModel.h"
#include "ComboProperty.h"
#include "InstrumentItems.h"
#include "DetectorItems.h"
#include "ConvolutionDetectorResolution.h"
#include "ResolutionFunction2DGaussian.h"
#include "IDetector2D.h"
#include "Units.h"

class TestDetectorItems :  public ::testing::Test
{
public:
    ~TestDetectorItems();
};

TestDetectorItems::~TestDetectorItems() = default;

TEST_F(TestDetectorItems, test_detectorAlignment)
{
    InstrumentModel model;
    SessionItem* detector = model.insertNewItem(Constants::FlatDetectorType);

    ComboProperty alignment
        = detector->getItemValue(FlatDetectorItem::P_ALIGNMENT).value<ComboProperty>();
    // generic has some more items visible
    alignment.setValue(Constants::ALIGNMENT_GENERIC);
    detector->setItemValue(FlatDetectorItem::P_ALIGNMENT,
                           QVariant::fromValue<ComboProperty>(alignment));
    EXPECT_TRUE(detector->getItem(FlatDetectorItem::P_NORMAL)->isVisible());

    // should be disabled if we switch
    alignment.setValue(Constants::ALIGNMENT_TO_REFLECTED_BEAM);
    detector->setItemValue(FlatDetectorItem::P_ALIGNMENT,
                           QVariant::fromValue<ComboProperty>(alignment));
    EXPECT_FALSE(detector->getItem(FlatDetectorItem::P_NORMAL)->isVisible());
}

TEST_F(TestDetectorItems, test_resolutionFunction)
{
    InstrumentModel model;
    GISASInstrumentItem* instrument
        = dynamic_cast<GISASInstrumentItem*>(model.insertNewItem(Constants::GISASInstrumentType));

    DetectorItem* detectorItem = instrument->detectorItem();

    detectorItem->setGroupProperty(DetectorItem::P_RESOLUTION_FUNCTION,
                                   Constants::ResolutionFunction2DGaussianType);

    auto detector = detectorItem->createDetector();
    auto convol
        = dynamic_cast<const ConvolutionDetectorResolution*>(detector->detectorResolution());
    auto gaussian
        = dynamic_cast<const ResolutionFunction2DGaussian*>(convol->getResolutionFunction2D());

    EXPECT_EQ(Units::rad2deg(gaussian->getSigmaX()), 0.02);
}
