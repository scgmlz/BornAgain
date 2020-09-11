// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DataProperties.cpp
//! @brief     Implements class DataPresentationProperties and its descendants
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/DataProperties.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/DataItem.h"
#include "GUI/coregui/Models/ModelPath.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/utils/GUIHelpers.h"

namespace
{
// set of simple colors for representation of 1D graphs
const std::vector<std::pair<QString, Qt::GlobalColor>> color_queue = {
    {"Black", Qt::GlobalColor::black},   {"Blue", Qt::GlobalColor::blue},
    {"Red", Qt::GlobalColor::darkRed},   {"Cyan", Qt::GlobalColor::darkCyan},
    {"Gray", Qt::GlobalColor::darkGray}, {"Magenta", Qt::GlobalColor::darkMagenta}};

struct ColorNameComparator {
    ColorNameComparator(const QString& value_to_comp) : m_value_to_comp(value_to_comp) {}
    bool operator()(const std::pair<QString, Qt::GlobalColor>& value) const
    {
        return value.first == m_value_to_comp;
    }

    const QString m_value_to_comp;
};

ComboProperty defaultColorCombo();
} // namespace

const QString DataProperties::P_DATALINK = "data link";

DataProperties::DataProperties(const QString& model_type) : SessionItem(model_type)
{
    addProperty(P_DATALINK, "");
}

void DataProperties::setDataItem(DataItem* item)
{
    const QString& path = ModelPath::getPathFromIndex(item->index());
    setItemValue(P_DATALINK, path);
}

DataItem* DataProperties::dataItem()
{
    SessionModel* hosting_model = this->model();
    const QString& path = getItemValue(P_DATALINK).toString();
    auto item_index = ModelPath::getIndexFromPath(hosting_model, path);
    if (!item_index.isValid()) {
        std::stringstream os;
        os << "Error in DataProperties::dataItem: index produced by path";
        os << path.toStdString() << " is invalid" << std::endl;
        throw GUIHelpers::Error(QString::fromStdString(os.str()));
    }
    auto item = hosting_model->itemForIndex(item_index);
    return dynamic_cast<DataItem*>(item);
}

const QString Data1DProperties::P_COLOR = "Color";

Data1DProperties::Data1DProperties() : DataProperties("DataItem1DProperties")
{
    addProperty(P_COLOR, defaultColorCombo().variant());
}

QColor Data1DProperties::color()
{
    const QString& color_name = getItemValue(P_COLOR).value<ComboProperty>().getValue();
    auto iter =
        std::find_if(color_queue.begin(), color_queue.end(), ColorNameComparator(color_name));
    if (iter == color_queue.end())
        throw GUIHelpers::Error("Error in Data1DPresentationProperties::color: unknown color name");
    return QColor(iter->second);
}

const QString& Data1DProperties::nextColorName(Data1DProperties* properties)
{
    if (!properties)
        return color_queue.front().first;
    const auto& current_color = properties->getItemValue(P_COLOR).value<ComboProperty>().getValue();
    auto iter =
        std::find_if(color_queue.begin(), color_queue.end(), ColorNameComparator(current_color));
    if (iter == color_queue.end() || *iter == color_queue.back())
        return color_queue.front().first;
    return (++iter)->first;
}

void Data1DProperties::setColorProperty(const QString& color_name)
{
    auto color_combo = defaultColorCombo();
    color_combo.setValue(color_name);
    setItemValue(P_COLOR, color_combo.variant());
}

namespace
{
ComboProperty defaultColorCombo()
{
    ComboProperty result;
    for (auto& color : color_queue)
        result << color.first;
    result.setValue(color_queue.front().first);
    return result;
}
} // namespace
