//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Models/InstrumentItems.cpp
//! @brief     Implements InstrumentItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Models/InstrumentItems.h"
#include "Core/Scan/UnitConverter1D.h"
#include "Device/Detector/IDetector2D.h"
#include "Device/Instrument/Instrument.h"
#include "GUI/coregui/Models/BackgroundItems.h"
#include "GUI/coregui/Models/BeamItems.h"
#include "GUI/coregui/Models/DataItem.h"
#include "GUI/coregui/Models/DetectorItems.h"
#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/ItemFileNameUtils.h"
#include "GUI/coregui/Models/JobItemUtils.h"
#include "GUI/coregui/Models/MaskItems.h"
#include "GUI/coregui/Models/PointwiseAxisItem.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/utils/GUIHelpers.h"

namespace {
const QString background_group_label = "Type";
const QStringList instrument_names{"GISASInstrument", "OffSpecularInstrument",
                                   "SpecularInstrument"};
void addAxisGroupProperty(SessionItem* parent, const QString& tag);
} // namespace

const QString InstrumentItem::P_IDENTIFIER = "Identifier";
const QString InstrumentItem::P_BEAM = "Beam";
const QString InstrumentItem::P_BACKGROUND = "Background";

QStringList InstrumentItem::translateList(const QStringList& list) const
{
    QStringList result;
    if (list.back().endsWith(P_BACKGROUND) && list.size() == 2) {
        result << list[0] << list[1];
    } else {
        result = SessionItem::translateList(list);
        if (instrument_names.contains(result.back())) {
            result.removeLast();
            result << "Instrument";
        }
    }
    return result;
}

QString InstrumentItem::id() const
{
    return getItemValue(P_IDENTIFIER).toString();
}

void InstrumentItem::setId(const QString& id)
{
    setItemValue(P_IDENTIFIER, id);
}

BeamItem* InstrumentItem::beamItem() const
{
    return item<BeamItem>(P_BEAM);
}

BackgroundItem* InstrumentItem::backgroundItem() const
{
    return &groupItem<BackgroundItem>(P_BACKGROUND);
}

GroupItem* InstrumentItem::backgroundGroup()
{
    return item<GroupItem>(P_BACKGROUND);
}

bool InstrumentItem::alignedWith(const RealDataItem* item) const
{
    return shape() == item->shape();
}

std::unique_ptr<Instrument> InstrumentItem::createInstrument() const
{
    std::unique_ptr<Instrument> result(new Instrument);

    auto beam = beamItem()->createBeam();
    result->setBeam(*beam);

    return result;
}

InstrumentItem::InstrumentItem(const QString& modelType) : SessionItem(modelType)
{
    setItemName(modelType);
    addProperty(P_IDENTIFIER, GUIHelpers::createUuid())->setVisible(false);
}

void InstrumentItem::initBackgroundGroup()
{
    auto item = addGroupProperty(P_BACKGROUND, "Background group");
    item->setDisplayName(background_group_label);
    item->setToolTip("Background type");
}

SpecularInstrumentItem::SpecularInstrumentItem() : InstrumentItem("SpecularInstrument")
{
    addProperty<SpecularBeamItem>(P_BEAM);

    initBackgroundGroup();
    item<SpecularBeamItem>(P_BEAM)->updateFileName(
        ItemFileNameUtils::instrumentDataFileName(*this));
}

SpecularBeamItem* SpecularInstrumentItem::beamItem() const
{
    return item<SpecularBeamItem>(P_BEAM);
}

SpecularInstrumentItem::~SpecularInstrumentItem() = default;

std::unique_ptr<Instrument> SpecularInstrumentItem::createInstrument() const
{
    return InstrumentItem::createInstrument();
}

std::vector<int> SpecularInstrumentItem::shape() const
{
    const auto axis_item = beamItem()->currentInclinationAxisItem();
    return {axis_item->binCount()};
}

void SpecularInstrumentItem::updateToRealData(const RealDataItem* item)
{
    if (shape().size() != item->shape().size())
        throw GUIHelpers::Error("Error in SpecularInstrumentItem::updateToRealData: The type "
                                "of instrument is incompatible with passed data shape.");

    const auto& data = item->nativeData()->getOutputData()->axis(0);
    beamItem()->updateToData(data, item->nativeDataUnits());
}

bool SpecularInstrumentItem::alignedWith(const RealDataItem* item) const
{
    const QString native_units = item->nativeDataUnits();
    if (native_units == "nbins") {
        return beamItem()->currentInclinationAxisItem()->modelType() == "BasicAxis"
               && shape() == item->shape();
    } else {
        auto axis_item = dynamic_cast<PointwiseAxisItem*>(beamItem()->currentInclinationAxisItem());
        if (!axis_item)
            return false;
        if (axis_item->getUnitsLabel() != native_units)
            return false;

        auto instrument_axis = axis_item->axis();
        if (!instrument_axis)
            return false;

        const auto& native_axis = item->nativeData()->getOutputData()->axis(0);
        return *instrument_axis == native_axis;
        ;
    }
}

std::unique_ptr<IUnitConverter> SpecularInstrumentItem::createUnitConverter() const
{
    const auto instrument = createInstrument();
    auto axis_item = beamItem()->currentInclinationAxisItem();
    if (auto pointwise_axis = dynamic_cast<PointwiseAxisItem*>(axis_item)) {
        if (!pointwise_axis->containsNonXMLData()) // workaround for loading project
            return nullptr;
        Axes::Units native_units = JobItemUtils::axesUnitsFromName(pointwise_axis->getUnitsLabel());
        return std::make_unique<UnitConverterConvSpec>(instrument->beam(), *pointwise_axis->axis(),
                                                       native_units);
    } else
        return std::make_unique<UnitConverterConvSpec>(
            instrument->beam(), *axis_item->createAxis(1.0), Axes::Units::DEGREES);
}

const QString Instrument2DItem::P_DETECTOR = "Detector";

Instrument2DItem::Instrument2DItem(const QString& modelType) : InstrumentItem(modelType)
{
    addProperty<GISASBeamItem>(P_BEAM);
    addGroupProperty(P_DETECTOR, "Detector group");
    initBackgroundGroup();

    setDefaultTag(P_DETECTOR);
}

Instrument2DItem::~Instrument2DItem() = default;

DetectorItem* Instrument2DItem::detectorItem() const
{
    return &groupItem<DetectorItem>(P_DETECTOR);
}

GroupItem* Instrument2DItem::detectorGroup()
{
    return item<GroupItem>(P_DETECTOR);
}

void Instrument2DItem::setDetectorGroup(const QString& modelType)
{
    setGroupProperty(P_DETECTOR, modelType);
}

void Instrument2DItem::clearMasks()
{
    detectorItem()->clearMasks();
}

void Instrument2DItem::importMasks(const MaskContainerItem* maskContainer)
{
    detectorItem()->importMasks(maskContainer);
}

std::unique_ptr<Instrument> Instrument2DItem::createInstrument() const
{
    auto result = InstrumentItem::createInstrument();

    auto detector = detectorItem()->createDetector();
    result->setDetector(*detector);

    return result;
}

GISASInstrumentItem::GISASInstrumentItem() : Instrument2DItem("GISASInstrument") {}

std::vector<int> GISASInstrumentItem::shape() const
{
    auto detector_item = detectorItem();
    return {detector_item->xSize(), detector_item->ySize()};
}

void GISASInstrumentItem::updateToRealData(const RealDataItem* item)
{
    if (!item)
        return;

    const auto data_shape = item->shape();
    if (shape().size() != data_shape.size())
        throw GUIHelpers::Error("Error in GISASInstrumentItem::updateToRealData: The type of "
                                "instrument is incompatible with passed data shape.");
    detectorItem()->setXSize(data_shape[0]);
    detectorItem()->setYSize(data_shape[1]);
}

const QString OffSpecularInstrumentItem::P_ALPHA_AXIS = "Alpha axis";

OffSpecularInstrumentItem::OffSpecularInstrumentItem() : Instrument2DItem("OffSpecularInstrument")
{
    addAxisGroupProperty(this, P_ALPHA_AXIS);
    auto inclination_item = getItem(P_ALPHA_AXIS)->getItem(BasicAxisItem::P_MIN_DEG);
    auto beam_item = beamItem();
    beam_item->setInclinationAngle(inclination_item->value().toDouble());
    beam_item->getItem(BeamItem::P_INCLINATION_ANGLE)->setEnabled(false);
    inclination_item->mapper()->setOnValueChange([beam_item, inclination_item]() {
        beam_item->setInclinationAngle(inclination_item->value().toDouble());
    });
}

std::vector<int> OffSpecularInstrumentItem::shape() const
{
    const int x_size = item<BasicAxisItem>(P_ALPHA_AXIS)->binCount();
    auto detector_item = detectorItem();
    return {x_size, detector_item->ySize()};
}

void OffSpecularInstrumentItem::updateToRealData(const RealDataItem* dataItem)
{
    if (!dataItem)
        return;

    const auto data_shape = dataItem->shape();
    if (shape().size() != data_shape.size())
        throw GUIHelpers::Error("Error in OffSpecularInstrumentItem::updateToRealData: The type of "
                                "instrument is incompatible with passed data shape.");

    item<BasicAxisItem>(P_ALPHA_AXIS)->setBinCount(data_shape[0]);
    detectorItem()->setYSize(data_shape[1]);
}

namespace {
void addAxisGroupProperty(SessionItem* parent, const QString& tag)
{
    auto axisItem = parent->addProperty<BasicAxisItem>(tag);
    axisItem->setToolTip("Incoming alpha range [deg]");
    axisItem->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    axisItem->getItem(BasicAxisItem::P_NBINS)->setToolTip("Number of points in scan");
    axisItem->getItem(BasicAxisItem::P_MIN_DEG)->setToolTip("Starting value [deg]");
    axisItem->getItem(BasicAxisItem::P_MAX_DEG)->setToolTip("Ending value [deg]");

    axisItem->setTitle("alpha_i");
    axisItem->setLowerBound(0.0);
    axisItem->setUpperBound(10.0);
}
} // namespace
