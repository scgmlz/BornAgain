// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/InstrumentItems.cpp
//! @brief     Implements InstrumentItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/InstrumentItems.h"
#include "Core/Detector/IDetector2D.h"
#include "Core/Instrument/Instrument.h"
#include "Core/Intensity/UnitConverter1D.h"
#include "GUI/coregui/Models/AxesItems.h"
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

namespace
{
const QString background_group_label = "Type";
const QStringList instrument_names{"GISASInstrument", "OffSpecInstrument", "SpecularInstrument"};
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

BeamItem* InstrumentItem::beamItem() const
{
    return &item<BeamItem>(P_BEAM);
}

BackgroundItem* InstrumentItem::backgroundItem() const
{
    return &groupItem<BackgroundItem>(P_BACKGROUND);
}

GroupItem* InstrumentItem::backgroundGroup()
{
    return &item<GroupItem>(P_BACKGROUND);
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

void InstrumentItem::initBeamGroup(const QString& beam_model)
{
    addGroupProperty(P_BEAM, beam_model);
}

void InstrumentItem::initBackgroundGroup()
{
    auto item = addGroupProperty(P_BACKGROUND, "Background group");
    item->setDisplayName(background_group_label);
    item->setToolTip("Background type");
}

SpecularInstrumentItem::SpecularInstrumentItem() : InstrumentItem("SpecularInstrument")
{
    initBeamGroup("SpecularBeam");
    initBackgroundGroup();
    item<SpecularBeamItem>(P_BEAM).updateFileName(ItemFileNameUtils::instrumentDataFileName(*this));
}

SpecularBeamItem* SpecularInstrumentItem::beamItem() const
{
    return &item<SpecularBeamItem>(P_BEAM);
}

SpecularInstrumentItem::~SpecularInstrumentItem() = default;

std::unique_ptr<Instrument> SpecularInstrumentItem::createInstrument() const
{
    return InstrumentItem::createInstrument();
}

std::vector<int> SpecularInstrumentItem::shape() const
{
    const auto axis_item = beamItem()->currentInclinationAxisItem();
    return {axis_item->getItemValue(BasicAxisItem::P_NBINS).toInt()};
}

void SpecularInstrumentItem::updateToRealData(const RealDataItem* item)
{
    if (shape().size() != item->shape().size())
        throw GUIHelpers::Error("Error in SpecularInstrumentItem::updateToRealData: The type "
                                "of instrument is incompatible with passed data shape.");

    QString units = item->getItemValue(RealDataItem::P_NATIVE_DATA_UNITS).toString();
    const auto& data = item->nativeData()->getOutputData()->getAxis(0);
    beamItem()->updateToData(data, units);
}

bool SpecularInstrumentItem::alignedWith(const RealDataItem* item) const
{
    const QString native_units = item->getItemValue(RealDataItem::P_NATIVE_DATA_UNITS).toString();
    if (native_units == "nbins") {
        return beamItem()->currentInclinationAxisItem()->modelType() == "BasicAxis"
               && shape() == item->shape();
    } else {
        auto axis_item = dynamic_cast<PointwiseAxisItem*>(beamItem()->currentInclinationAxisItem());
        if (!axis_item)
            return false;
        if (axis_item->getUnitsLabel() != native_units)
            return false;

        auto instrument_axis = axis_item->getAxis();
        if (!instrument_axis)
            return false;

        const auto& native_axis = item->nativeData()->getOutputData()->getAxis(0);
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
        AxesUnits native_units = JobItemUtils::axesUnitsFromName(pointwise_axis->getUnitsLabel());
        return std::make_unique<UnitConverterConvSpec>(instrument->getBeam(),
                                                       *pointwise_axis->getAxis(), native_units);
    } else
        return std::make_unique<UnitConverterConvSpec>(
            instrument->getBeam(), *axis_item->createAxis(1.0), AxesUnits::DEGREES);
}

const QString Instrument2DItem::P_DETECTOR = "Detector";

Instrument2DItem::Instrument2DItem(const QString& modelType) : InstrumentItem(modelType)
{
    initBeamGroup("GISASBeam");
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
    return &item<GroupItem>(P_DETECTOR);
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

const QString OffSpecInstrumentItem::P_ALPHA_AXIS = "Alpha axis";

OffSpecInstrumentItem::OffSpecInstrumentItem() : Instrument2DItem("OffSpecInstrument")
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

std::vector<int> OffSpecInstrumentItem::shape() const
{
    const int x_size = getItem(P_ALPHA_AXIS)->getItemValue(BasicAxisItem::P_NBINS).toInt();
    auto detector_item = detectorItem();
    return {x_size, detector_item->ySize()};
}

void OffSpecInstrumentItem::updateToRealData(const RealDataItem* item)
{
    if (!item)
        return;

    const auto data_shape = item->shape();
    if (shape().size() != data_shape.size())
        throw GUIHelpers::Error("Error in OffSpecInstrumentItem::updateToRealData: The type of "
                                "instrument is incompatible with passed data shape.");
    getItem(OffSpecInstrumentItem::P_ALPHA_AXIS)
        ->setItemValue(BasicAxisItem::P_NBINS, data_shape[0]);
    detectorItem()->setYSize(data_shape[1]);
}

namespace
{
void addAxisGroupProperty(SessionItem* parent, const QString& tag)
{
    auto item = parent->addGroupProperty(tag, "BasicAxis");
    item->setToolTip("Incoming alpha range [deg]");
    item->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    item->getItem(BasicAxisItem::P_NBINS)->setToolTip("Number of points in scan");
    item->getItem(BasicAxisItem::P_MIN_DEG)->setToolTip("Starting value [deg]");
    item->getItem(BasicAxisItem::P_MAX_DEG)->setToolTip("Ending value [deg]");

    item->setItemValue(BasicAxisItem::P_TITLE, "alpha_i");
    item->setItemValue(BasicAxisItem::P_MIN_DEG, 0.0);
    item->setItemValue(BasicAxisItem::P_MAX_DEG, 10.0);
}
} // namespace
