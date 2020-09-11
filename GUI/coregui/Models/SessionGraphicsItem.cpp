// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionGraphicsItem.cpp
//! @brief     Implements class SessionGraphicsItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/SessionGraphicsItem.h"

const QString SessionGraphicsItem::P_XPOS = "xpos";
const QString SessionGraphicsItem::P_YPOS = "ypos";

SessionGraphicsItem::SessionGraphicsItem(const QString& model_type) : SessionItem(model_type)
{
    addProperty(P_XPOS, qreal(0.0))->setVisible(false);
    addProperty(P_YPOS, qreal(0.0))->setVisible(false);
}
