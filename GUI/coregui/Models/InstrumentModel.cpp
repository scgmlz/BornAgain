//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Models/InstrumentModel.cpp
//! @brief     Implements class InstrumentModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/SpecularBeamInclinationItem.h"

InstrumentModel::InstrumentModel(QObject* parent)
    : SessionModel(SessionXML::InstrumentModelTag, parent)
{
    setObjectName(SessionXML::InstrumentModelTag);
}

InstrumentModel::~InstrumentModel() = default;

InstrumentModel* InstrumentModel::createCopy(SessionItem* parent)
{
    InstrumentModel* result = new InstrumentModel();
    result->initFrom(this, parent);
    return result;
}

QVector<SessionItem*> InstrumentModel::nonXMLItems() const
{
    QVector<SessionItem*> result;

    for (auto instrument_item : topItems<SpecularInstrumentItem>()) {
        auto axis_group = instrument_item->beamItem()
                              ->getItem(BeamItem::P_INCLINATION_ANGLE)
                              ->getItem(SpecularBeamInclinationItem::P_ALPHA_AXIS);

        if (auto pointwise_axis = axis_group->getChildOfType("PointwiseAxis"))
            result.push_back(pointwise_axis);
    }

    return result;
}

QVector<InstrumentItem*> InstrumentModel::instrumentItems() const
{
    return topItems<InstrumentItem>();
}

InstrumentItem* InstrumentModel::findInstrumentById(const QString& instrumentId) const
{
    for (auto instrument : instrumentItems())
        if (instrument->id() == instrumentId)
            return instrument;

    return nullptr;
}
