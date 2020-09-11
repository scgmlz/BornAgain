// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SampleModel.cpp
//! @brief     Implements class SampleModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Models/MultiLayerItem.h"

SampleModel::SampleModel(QObject* parent) : SessionModel(SessionXML::SampleModelTag, parent)
{
    setObjectName(SessionXML::SampleModelTag);
}

SampleModel* SampleModel::createCopy(SessionItem* parent)
{
    SampleModel* result = new SampleModel();
    result->initFrom(this, parent);
    return result;
}

MultiLayerItem* SampleModel::multiLayerItem()
{
    return topItem<MultiLayerItem>();
}
