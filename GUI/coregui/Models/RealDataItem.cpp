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

#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/ItemFileNameUtils.h"
#include "GUI/coregui/Models/JobItemUtils.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Models/SpecularDataItem.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "GUI/coregui/utils/ImportDataInfo.h"

const QString RealDataItem::P_INSTRUMENT_ID = "Instrument Id";
const QString RealDataItem::P_INSTRUMENT_NAME = "Instrument";
const QString RealDataItem::T_INTENSITY_DATA = "Intensity data";
const QString RealDataItem::T_NATIVE_DATA = "Native user data axis";
const QString RealDataItem::P_NATIVE_DATA_UNITS = "Native user data units";

RealDataItem::RealDataItem() : SessionItem("RealData"), m_linkedInstrument(nullptr)
{
    setItemName("undefined");

    // Registering this tag even without actual data item to avoid troubles in copying RealDataItem
    registerTag(T_INTENSITY_DATA, 1, 1,
                QStringList() << "IntensityData"
                              << "SpecularData");
    setDefaultTag(T_INTENSITY_DATA);

    addProperty(P_INSTRUMENT_ID, QString());
    addProperty(P_INSTRUMENT_NAME, QString());

    registerTag(T_NATIVE_DATA, 1, 1,
                QStringList() << "IntensityData"
                              << "SpecularData");
    addProperty(P_NATIVE_DATA_UNITS, "nbins")->setVisible(false);

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_NAME)
            updateNonXMLDataFileNames();
    });

    mapper()->setOnChildrenChange([this](SessionItem* item) {
        if (dynamic_cast<DataItem*>(item))
            updateNonXMLDataFileNames();
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
    return dynamic_cast<const DataItem*>(getItem(T_INTENSITY_DATA));
}

DataItem* RealDataItem::nativeData()
{
    return const_cast<DataItem*>(static_cast<const RealDataItem*>(this)->nativeData());
}

const DataItem* RealDataItem::nativeData() const
{
    return dynamic_cast<const DataItem*>(getItem(T_NATIVE_DATA));
}

//! Sets OutputData to underlying item. Creates it, if not exists.

void RealDataItem::setOutputData(OutputData<double>* data)
{
    ASSERT(data && "Assertion failed in RealDataItem::setOutputData: passed data is nullptr");
    ASSERT(data->getRank() < 3 && data->getRank() > 0);

    const QString& target_model_type =
        data->getRank() == 2 ? "IntensityData" : data->getRank() == 1 ? "SpecularData" : "";
    auto data_item = getItem(T_INTENSITY_DATA);
    if (data_item && data_item->modelType() != target_model_type)
        throw GUIHelpers::Error("Error in RealDataItem::setOutputData: trying to set data "
                                "incompatible with underlying data item");
    if (!data_item) {
        this->model()->insertNewItem(target_model_type, this->index(), 0, T_INTENSITY_DATA);
        ASSERT(getItem(T_INTENSITY_DATA)
               && "Assertion failed in RealDataItem::setOutputData: inserting data item failed.");
    }
    dataItem()->setOutputData(data);
}

void RealDataItem::initDataItem(size_t data_rank, const QString& tag)
{
    ASSERT(data_rank <= 2 && data_rank > 0);
    const QString& target_model_type = data_rank == 2 ? "IntensityData" : "SpecularData";
    auto data_item = getItem(tag);
    if (data_item && data_item->modelType() != target_model_type)
        throw GUIHelpers::Error("Error in RealDataItem::initDataItem: trying to set data "
                                "incompatible with underlying data item");
    if (!data_item)
        this->model()->insertNewItem(target_model_type, this->index(), 0, tag);
}

void RealDataItem::setImportData(ImportDataInfo data)
{
    if (!data)
        return;

    const size_t data_rank = data.dataRank();
    initDataItem(data_rank, T_INTENSITY_DATA);
    initDataItem(data_rank, T_NATIVE_DATA);

    QString units_name = data.unitsLabel();
    auto output_data = data.intensityData();

    dataItem()->reset(std::move(data));
    getItem(P_NATIVE_DATA_UNITS)->setValue(units_name);
    item<DataItem>(T_NATIVE_DATA).setOutputData(output_data.release());
}

bool RealDataItem::holdsDimensionalData() const
{
    return getItemValue(P_NATIVE_DATA_UNITS).toString() != "nbins";
}

void RealDataItem::linkToInstrument(const InstrumentItem* instrument, bool make_update)
{
    m_linkedInstrument = instrument;
    if (make_update)
        updateToInstrument();
}

std::vector<int> RealDataItem::shape() const
{
    auto data_item = dataItem();
    if (!data_item) {
        ASSERT(data_item);
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

void RealDataItem::updateNonXMLDataFileNames()
{
    if (DataItem* item = dataItem())
        item->setItemValue(DataItem::P_FILE_NAME, ItemFileNameUtils::realDataFileName(*this));
    if (DataItem* item = nativeData())
        item->setItemValue(DataItem::P_FILE_NAME, ItemFileNameUtils::nativeDataFileName(*this));
}

void RealDataItem::updateToInstrument()
{
    DataItem* data_item = dataItem();
    if (!data_item)
        return;

    if (m_linkedInstrument) {
        JobItemUtils::setIntensityItemAxesUnits(data_item, m_linkedInstrument);
        return;
    }

    auto native_data_item = nativeData();
    auto data_source = native_data_item ? native_data_item : data_item;

    std::unique_ptr<OutputData<double>> native_data(data_source->getOutputData()->clone());
    const QString units_label = getItemValue(P_NATIVE_DATA_UNITS).toString();
    data_item->reset(ImportDataInfo(std::move(native_data), units_label));
}
