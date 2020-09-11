// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/TransformationItem.cpp
//! @brief     Implements class TransformationItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/TransformationItem.h"

const QString TransformationItem::P_ROT = "Rotation type";

TransformationItem::TransformationItem() : SessionGraphicsItem("Rotation")
{
    setToolTip("Rotation applied to particles");
    addGroupProperty(P_ROT, "Rotation group");
}
