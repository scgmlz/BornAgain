// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/RealDataItem.cpp
//! @brief     Implements class RealDataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RealDataItem.h"
#include "GUIHelpers.h"
#include "ImportDataUtils.h"
#include "IntensityDataItem.h"
#include "InstrumentItems.h"
#include "JobItemFunctions.h"
#include "JobItemUtils.h"
#include "SessionModel.h"
#include "SpecularDataItem.h"

const QString RealDataItem::P_INSTRUMENT_ID = "Instrument Id";
const QString RealDataItem::P_INSTRUMENT_NAME = "Instrument";
const QString RealDataItem::T_INTENSITY_DATA = "Intensity data";

RealDataItem::RealDataItem()
    : SessionItem(Constants::RealDataType)
    , m_linkedInstrument(nullptr)
{
    setItemName(QStringLiteral("undefined"));

    // Registering this tag even without actual data item to avoid troubles in copying RealDataItem
    registerTag(T_INTENSITY_DATA, 1, 1,
                QStringList() << Constants::IntensityDataType << Constants::SpecularDataType);

    // TODO: allows to access underlying data item, should be removed. But it is not clear,
    // what happens if default tag is not present.
    setDefaultTag(T_INTENSITY_DATA);

    addProperty(P_INSTRUMENT_ID, QString());
    addProperty(P_INSTRUMENT_NAME, QString());

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_NAME && getItem(T_INTENSITY_DATA))
            updateIntensityDataFileName();
    });

    mapper()->setOnChildrenChange([this](SessionItem* item) {
        if (dynamic_cast<DataItem*>(item))
            updateIntensityDataFileName();
    });

    mapper()->setOnChildPropertyChange([this](SessionItem* item, const QString& name) {
        auto data_item = dynamic_cast<DataItem*>(item);
        if (!data_item || !m_linkedInstrument || name != DataItem::P_AXES_UNITS)
            return;

        mapper()->setActive(false);
        data_item->updateAxesUnits(m_linkedInstrument);
        mapper()->setActive(true);
    });
}

IntensityDataItem* RealDataItem::intensityDataItem()
{
    return const_cast<IntensityDataItem*>(
        static_cast<const RealDataItem*>(this)->intensityDataItem());
}

const IntensityDataItem* RealDataItem::intensityDataItem() const
{
    return dynamic_cast<const IntensityDataItem*>(dataItem());
}

DataItem* RealDataItem::dataItem()
{
    return const_cast<DataItem*>(static_cast<const RealDataItem*>(this)->dataItem());
}

const DataItem* RealDataItem::dataItem() const
{
    const DataItem* result = dynamic_cast<const DataItem*>(getItem(T_INTENSITY_DATA));
    if (!result)
        throw GUIHelpers::Error(
            "Error in RealDataItem::dataItem: underlying data item was not set.");
    return result;
}

//! Sets OutputData to underlying item. Creates it, if not exists.

void RealDataItem::setOutputData(OutputData<double>* data)
{
    assert(data && "Assertion failed in RealDataItem::setOutputData: passed data is nullptr");
    assert(data->getRank() < 3 && data->getRank() > 0);

    const QString& target_model_type
        = data->getRank() == 2 ? Constants::IntensityDataType
                               : data->getRank() == 1 ? Constants::SpecularDataType : "";
    auto data_item = getItem(T_INTENSITY_DATA);
    if (data_item && data_item->modelType() != target_model_type)
        throw GUIHelpers::Error("Error in RealDataItem::setOutputData: trying to set data "
                                "incompatible with underlying data item");
    if (!data_item) {
        this->model()->insertNewItem(target_model_type, this->index(), 0, T_INTENSITY_DATA);
        assert(getItem(T_INTENSITY_DATA)
               && "Assertion failed in RealDataItem::setOutputData: inserting data item failed.");
    }
    dataItem()->setOutputData(data);
}

void RealDataItem::linkToInstrument(const InstrumentItem *instrument, bool make_update)
{
    m_linkedInstrument = instrument;
    if(make_update)
        updateToInstrument();
}

std::vector<int> RealDataItem::shape() const
{
    auto data_item = dataItem();
    if (!data_item) {
        assert(data_item);
        return {};
    }
    return data_item->shape();
}

QString RealDataItem::underlyingDataModel()
{
    return dataItem()->modelType();
}

MaskContainerItem* RealDataItem::maskContainerItem()
{
    if (auto intensity_data = intensityDataItem())
        return intensity_data->maskContainerItem();
    return nullptr;
}

//! Updates the name of file to store intensity data.

void RealDataItem::updateIntensityDataFileName()
{
    if (DataItem* item = dataItem())
        item->setItemValue(DataItem::P_FILE_NAME, JobItemFunctions::realDataFileName(*this));
}

void RealDataItem::updateToInstrument()
{
    if (DataItem* item = dataItem())
        JobItemUtils::setIntensityItemAxesUnits(item, m_linkedInstrument);
}
