// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DataItem.cpp
//! @brief     Implements class IntensityDataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/DataItem.h"
#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "GUI/coregui/utils/ImportDataInfo.h"

const QString DataItem::P_FILE_NAME = "FileName";
const QString DataItem::P_AXES_UNITS = "Axes Units";

void DataItem::setOutputData(OutputData<double>* data)
{
    std::unique_lock<std::mutex> lock(m_update_data_mutex);
    m_data.reset(data);
}

void DataItem::setRawDataVector(std::vector<double> data)
{
    if (m_data->getAllocatedSize() != data.size())
        throw GUIHelpers::Error("DataItem::setRawDataVector() -> Error. "
                                "Different data size.");
    std::unique_lock<std::mutex> lock(m_update_data_mutex);
    m_data->setRawDataVector(std::move(data));
    emitDataChanged();
}

QString DataItem::fileName() const
{
    return getItemValue(DataItem::P_FILE_NAME).toString();
}

QDateTime DataItem::lastModified() const
{
    return m_last_modified;
}

bool DataItem::containsNonXMLData() const
{
    return static_cast<bool>(m_data);
}

bool DataItem::load(const QString& projectDir)
{
    QString filename = fileName(projectDir);
    auto data = IntensityDataIOFactory::readOutputData(filename.toStdString());
    if (!data)
        return false;
    setOutputData(data);
    return true;
}

bool DataItem::save(const QString& projectDir)
{
    if (!containsNonXMLData())
        return false;

    std::unique_lock<std::mutex> lock(m_update_data_mutex);
    std::unique_ptr<OutputData<double>> clone(getOutputData()->clone());
    lock.unlock();
    IntensityDataIOFactory::writeOutputData(*clone, fileName(projectDir).toStdString());
    return true;
}

void DataItem::setLastModified(const QDateTime& dtime)
{
    m_last_modified = dtime;
}

QString DataItem::selectedAxesUnits() const
{
    ComboProperty combo = getItemValue(DataItem::P_AXES_UNITS).value<ComboProperty>();
    return combo.getValue();
}

DataItem::DataItem(const QString& modelType) : SessionItem(modelType)
{
    // name of the file used to serialize given IntensityDataItem
    addProperty(P_FILE_NAME, "undefined")->setVisible(false);

    ComboProperty units = ComboProperty() << "nbins";
    addProperty(P_AXES_UNITS, units.variant());

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_FILE_NAME)
            setLastModified(QDateTime::currentDateTime());
    });

    mapper()->setOnValueChange([this]() {
        // OutputData was modified
        setLastModified(QDateTime::currentDateTime());
    });
}
