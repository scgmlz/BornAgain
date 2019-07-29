// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentUtils.cpp
//! @brief     Implements ComponentUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ComponentUtils.h"
#include "item_constants.h"
#include "SessionItem.h"

namespace {
QList<const SessionItem*> groupItems(const SessionItem& item);
}

QStringList ComponentUtils::propertyRelatedTypes()
{
    QStringList result = QStringList() << Constants::PropertyType << Constants::GroupItemType
                                       << Constants::VectorType << Constants::BasicAxisType
                                       << Constants::AmplitudeAxisType
                                       << Constants::MaterialRefractiveDataType;
    return result;
}

QList<const SessionItem*> ComponentUtils::componentItems(const SessionItem& item)
{
    static QStringList propertyRelated = ComponentUtils::propertyRelatedTypes();

    QList<const SessionItem*> result;

    if (item.modelType() == Constants::PropertyType) {
        result.push_back(&item);

    } else if (item.modelType() == Constants::GroupItemType) {
        result.push_back(&item);
        result += groupItems(item);

    } else {

        for (auto child : item.children()) {
            if (!child->isVisible())
                continue;

            if (propertyRelated.contains(child->modelType()))
                result.append(child);

            if (child->modelType() == Constants::GroupItemType)
                result += groupItems(*child);
        }
    }

    return result;
}

namespace {
QList<const SessionItem*> groupItems(const SessionItem& item)
{
    Q_ASSERT(item.modelType() == Constants::GroupItemType);

    QList<const SessionItem*> result;
    for (auto grandchild : item.children()) {
        if (grandchild->isVisible())
            result+= ComponentUtils::componentItems(*grandchild);
    }

    return result;
}
}
