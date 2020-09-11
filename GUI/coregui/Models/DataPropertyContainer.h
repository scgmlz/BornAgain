// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DataPropertyContainer.h
//! @brief     Defines class DataPropertyContainer
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_DATAPROPERTYCONTAINER_H
#define BORNAGAIN_GUI_COREGUI_MODELS_DATAPROPERTYCONTAINER_H

#include "GUI/coregui/Models/SessionItem.h"

class DataItem;
class DataProperties;
class Data1DProperties;
template <class T> class OutputData;

class BA_CORE_API_ DataPropertyContainer : public SessionItem
{
    static const QString T_CHILDREN;

public:
    DataPropertyContainer();
    ~DataPropertyContainer() override = default;

    void addItem(DataItem* data_item);
    QVector<Data1DProperties*> propertyItems();
    Data1DProperties* propertyItem(size_t i) const;

    DataItem* basicDataItem();

protected:
    std::vector<DataItem*> dataItems();
    DataItem* dataItem(size_t i) const;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_DATAPROPERTYCONTAINER_H
