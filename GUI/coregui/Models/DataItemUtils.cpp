// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DataItemUtils.cpp
//! @brief     Implements namespace DataItemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/DataItemUtils.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/SpecularDataItem.h"
#include "GUI/coregui/utils/GUIHelpers.h"

namespace
{
template <class DataItemType> DataItemType* dataItem(SessionItem* parent)
{
    ASSERT(parent && "Assertion failed in DataItemUtils::dataItem: nullptr passed.");

    if (parent->modelType() == "JobItem")
        return dynamic_cast<DataItemType*>(parent->getItem(JobItem::T_OUTPUT));
    else if (auto real_data = dynamic_cast<RealDataItem*>(parent))
        return dynamic_cast<DataItemType*>(real_data->dataItem());
    else if (auto self = dynamic_cast<DataItemType*>(parent))
        return self;

    throw GUIHelpers::Error("Error in DataItemUtils::dataItem: unexpected item passed.");
}
} // namespace

IntensityDataItem* DataItemUtils::intensityDataItem(SessionItem* parent)
{
    return dataItem<IntensityDataItem>(parent);
}

SpecularDataItem* DataItemUtils::specularDataItem(SessionItem* parent)
{
    return dataItem<SpecularDataItem>(parent);
}
