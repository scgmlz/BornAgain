// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DataPropertyContainer.cpp
//! @brief     Implements class DataPropertyContainer
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/DataPropertyContainer.h"
#include "GUI/coregui/Models/DataItem.h"
#include "GUI/coregui/Models/DataProperties.h"
#include "GUI/coregui/utils/GUIHelpers.h"

const QString DataPropertyContainer::T_CHILDREN = "data links";

DataPropertyContainer::DataPropertyContainer() : SessionItem("DataPropertyContainer")
{
    registerTag(T_CHILDREN, 0, -1, QStringList() << "DataItem1DProperties");
    setDefaultTag(T_CHILDREN);
}

QVector<Data1DProperties*> DataPropertyContainer::propertyItems()
{
    QVector<Data1DProperties*> result;
    auto source = getItems();
    std::transform(source.begin(), source.end(), std::back_inserter(result),
                   [](SessionItem* item) { return dynamic_cast<Data1DProperties*>(item); });
    return result;
}

Data1DProperties* DataPropertyContainer::propertyItem(size_t i) const
{
    auto children = getItems();
    if (children.empty())
        return nullptr;
    auto property_item = dynamic_cast<Data1DProperties*>(children[static_cast<int>(i)]);
    ASSERT(property_item);
    return property_item;
}

DataItem* DataPropertyContainer::basicDataItem()
{
    auto basic_property_item = propertyItem(0);
    if (!basic_property_item)
        return nullptr;
    return basic_property_item->dataItem();
}

void DataPropertyContainer::addItem(DataItem* data_item)
{
    if (this->model() != data_item->model())
        throw GUIHelpers::Error(
            "Error in DataPropertyContainer::addItem: hosting models are different");

    auto property_items = propertyItems();
    Data1DProperties* previous_item = nullptr;
    if (!propertyItems().empty())
        previous_item = dynamic_cast<Data1DProperties*>(propertyItems().back());

    auto property_item = new Data1DProperties();
    insertItem(-1, property_item);
    property_item->setDataItem(data_item);
    property_item->setColorProperty(Data1DProperties::nextColorName(previous_item));
}

std::vector<DataItem*> DataPropertyContainer::dataItems()
{
    std::vector<DataItem*> result;
    auto items = propertyItems();
    std::transform(items.begin(), items.end(), std::back_inserter(result),
                   [](Data1DProperties* item) {
                       auto data_item = item->dataItem();
                       ASSERT(data_item);
                       return data_item;
                   });
    return result;
}

DataItem* DataPropertyContainer::dataItem(size_t i) const
{
    return propertyItem(i)->dataItem();
}
