//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Models/RealDataItem.cpp
//! @brief     Implements class RealDataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/ItemFileNameUtils.h"
#include "GUI/coregui/Models/JobItemUtils.h"
#include "GUI/coregui/Models/RealDataModel.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Models/SpecularDataItem.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "GUI/coregui/utils/ImportDataInfo.h"
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

const QString RealDataItem::P_INSTRUMENT_ID = "Instrument Id";
const QString RealDataItem::P_INSTRUMENT_NAME = "Instrument";
const QString RealDataItem::T_INTENSITY_DATA = "Intensity data";
const QString RealDataItem::T_NATIVE_DATA = "Native user data axis";
const QString RealDataItem::P_NATIVE_DATA_UNITS = "Native user data units";

namespace XMLTags {
const QString Version("Version");
const QString NativeFilename("NativeFileName");
const QString ImportSettings("ImportSettings");
const QString Value("Value");
} // namespace XMLTags

RealDataItem::RealDataItem() : SessionItem("RealData")
{
    setItemName("undefined");

    // Registering this tag even without actual data item to avoid troubles in copying RealDataItem
    registerTag(T_INTENSITY_DATA, 1, 1,
                QStringList() << "IntensityData"
                              << "SpecularData");
    setDefaultTag(T_INTENSITY_DATA);

    addProperty(P_INSTRUMENT_ID, QString());
    addProperty(P_INSTRUMENT_NAME, QString()); // #migration This is never used - remove after
                                               // checking whether this breaks loading old files

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
        if (!data_item || !linkedInstrument() || name != DataItem::P_AXES_UNITS)
            return;

        mapper()->setActive(false);
        data_item->updateAxesUnits(linkedInstrument());
        mapper()->setActive(true);
    });
}

QString RealDataItem::name() const
{
    return itemName();
}

void RealDataItem::setName(const QString& name)
{
    setItemName(name);
}

IntensityDataItem* RealDataItem::intensityDataItem()
{
    return dynamic_cast<IntensityDataItem*>(dataItem());
}

const IntensityDataItem* RealDataItem::intensityDataItem() const
{
    return dynamic_cast<const IntensityDataItem*>(dataItem());
}

SpecularDataItem* RealDataItem::specularDataItem()
{
    return dynamic_cast<SpecularDataItem*>(dataItem());
}

const SpecularDataItem* RealDataItem::specularDataItem() const
{
    return dynamic_cast<const SpecularDataItem*>(dataItem());
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

void RealDataItem::initNativeData()
{
    const size_t rank = isSpecularData() ? 1 : 2;
    initDataItem(rank, T_NATIVE_DATA);
}

QString RealDataItem::nativeDataUnits() const
{
    return getItemValue(P_NATIVE_DATA_UNITS).toString();
}

void RealDataItem::setNativeDataUnits(const QString& units)
{
    getItem(P_NATIVE_DATA_UNITS)->setValue(units);
}

bool RealDataItem::hasNativeData() const
{
    return (nativeData() != nullptr) && (nativeData()->getOutputData() != nullptr);
}

const OutputData<double>* RealDataItem::nativeOutputData() const
{
    return hasNativeData() ? nativeData()->getOutputData() : nullptr;
}

//! takes ownership of data

void RealDataItem::setNativeOutputData(OutputData<double>* data)
{
    nativeData()->setOutputData(data); // takes ownership of odata
}

//! Creates data item if not existing so far. Checks for rank compatibility if already existing. No
//! further initialization like clearing the data etc.

void RealDataItem::initDataItem(size_t rank, const QString& tag)
{
    ASSERT(rank <= 2 && rank > 0);

    auto data_item = getItem(tag);
    if (data_item != nullptr) {
        const bool rankMismatch = (rank == 1 && !data_item->is<SpecularDataItem>())
                                  || (rank == 2 && !data_item->is<IntensityDataItem>());

        if (rankMismatch)
            throw GUIHelpers::Error("Error in RealDataItem::initDataItem: trying to set data "
                                    "incompatible with underlying data item");
    } else {
        if (rank == 1)
            model()->insertItem<SpecularDataItem>(this, 0, tag);
        else
            model()->insertItem<IntensityDataItem>(this, 0, tag);

        ASSERT(getItem(tag)
               && "Assertion failed in RealDataItem::initDataItem: inserting data item failed.");
    }
}

//! Sets OutputData to underlying item. Creates it if not existing.

void RealDataItem::setOutputData(OutputData<double>* data)
{
    ASSERT(data && "Assertion failed in RealDataItem::setOutputData: passed data is nullptr");

    initDataItem(data->rank(), T_INTENSITY_DATA);

    dataItem()->setOutputData(data);
}

//! Sets imported data to underlying item. Creates it if not existing.
//! This is used for 1-D import (2-D only using setOutputData). BUT: This last
//! statement seems wrong - in the unit tests it is used for 2D import

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
    setNativeDataUnits(units_name);
    item<DataItem>(T_NATIVE_DATA)->setOutputData(output_data.release());
}

void RealDataItem::initAsSpecularItem()
{
    const size_t rank = 1;
    initDataItem(rank, T_INTENSITY_DATA);
}

void RealDataItem::initAsIntensityItem()
{
    const size_t rank = 2;
    initDataItem(rank, T_INTENSITY_DATA);
}

bool RealDataItem::holdsDimensionalData() const
{
    return nativeDataUnits() != "nbins";
}

QString RealDataItem::instrumentId() const
{
    return getItemValue(P_INSTRUMENT_ID).toString();
}

void RealDataItem::setInstrumentId(const QString& id)
{
    setItemValue(P_INSTRUMENT_ID, id);
}

void RealDataItem::clearInstrumentId()
{
    setItemValue(P_INSTRUMENT_ID, QString());
    // #baimport ++ should m_linkedInstrument be set to null?
}

InstrumentItem* RealDataItem::linkedInstrument() const
{
    return instrumentModel() != nullptr ? instrumentModel()->findInstrumentById(instrumentId())
                                        : nullptr;
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

bool RealDataItem::isIntensityData() const
{
    return intensityDataItem() != nullptr;
}

bool RealDataItem::isSpecularData() const
{
    return specularDataItem() != nullptr;
}

MaskContainerItem* RealDataItem::maskContainerItem()
{
    if (auto intensity_data = intensityDataItem())
        return intensity_data->maskContainerItem();
    return nullptr;
}

QByteArray RealDataItem::importSettings() const
{
    return m_importSettings;
}

void RealDataItem::setImportSettings(const QByteArray& a)
{
    m_importSettings = a;
}

void RealDataItem::setNativeFileName(const QString& filename)
{
    m_nativeFileName = filename;
}

QString RealDataItem::nativeFileName() const
{
    return m_nativeFileName;
}

void RealDataItem::writeNonSessionItemData(QXmlStreamWriter* writer) const
{
    writer->writeEmptyElement(XMLTags::Version);
    writer->writeAttribute(XMLTags::Value, "1");

    writer->writeEmptyElement(XMLTags::NativeFilename);
    writer->writeAttribute(XMLTags::Value, m_nativeFileName);

    writer->writeEmptyElement(XMLTags::ImportSettings);
    writer->writeAttribute(XMLTags::Value, m_importSettings.toBase64());
}

void RealDataItem::readNonSessionItemData(QXmlStreamReader* reader)
{
    m_nativeFileName.clear();
    m_importSettings.clear();

    // #baimport ++ check version
    // #baimport ++ check compatible versions
    while (reader->readNextStartElement()) {
        if (reader->name() == XMLTags::NativeFilename) {

            m_nativeFileName = reader->attributes().value(XMLTags::Value).toString();
        } else if (reader->name() == XMLTags::ImportSettings) {
            QStringRef valueAsBase64 = reader->attributes().value(XMLTags::Value);
            m_importSettings = QByteArray::fromBase64(
                valueAsBase64.toLatin1()); // #baimport add a unit test for this!
        }

        reader->skipCurrentElement();
    }
}

//! Updates the name of file to store intensity data.

void RealDataItem::updateNonXMLDataFileNames()
{
    if (DataItem* item = dataItem())
        item->setFileName(ItemFileNameUtils::realDataFileName(*this));
    if (DataItem* item = nativeData())
        item->setFileName(ItemFileNameUtils::nativeDataFileName(*this));
}

RealDataModel* RealDataItem::realDataModel() const
{
    return dynamic_cast<RealDataModel*>(model());
}

InstrumentModel* RealDataItem::instrumentModel() const
{
    return realDataModel() != nullptr ? realDataModel()->instrumentModel() : nullptr;
}

void RealDataItem::updateToInstrument(const InstrumentItem* instrument)
{
    DataItem* data_item = dataItem();
    if (!data_item)
        return;

    if (instrument) {
        JobItemUtils::setIntensityItemAxesUnits(data_item, instrument);
        return;
    }

    // unlinking => going back to native data
    if (isSpecularData()) {
        if (hasNativeData()) {
            std::unique_ptr<OutputData<double>> native_data(nativeData()->getOutputData()->clone());
            const QString units_label = nativeDataUnits();
            data_item->reset(ImportDataInfo(std::move(native_data), units_label));
        } else {
            specularDataItem()->setOutputData(nullptr);
        }
    } else {
        auto native_data_item = nativeData();
        auto data_source = native_data_item ? native_data_item : data_item;

        std::unique_ptr<OutputData<double>> native_data(data_source->getOutputData()->clone());
        const QString units_label = nativeDataUnits();
        data_item->reset(ImportDataInfo(std::move(native_data), units_label));
    }
}

void RealDataItem::updateToInstrument(const QString& id)
{
    updateToInstrument(instrumentModel()->findInstrumentById(id));
}
