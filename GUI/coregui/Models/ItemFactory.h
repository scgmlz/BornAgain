// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ItemFactory.h
//! @brief     Defines class ItemFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_ITEMFACTORY_H
#define BORNAGAIN_GUI_COREGUI_MODELS_ITEMFACTORY_H

#include <QString>

class SessionItem;

namespace ItemFactory
{
//! create SessionItem of specific type and parent
SessionItem* CreateItem(const QString& model_name, SessionItem* parent = nullptr);

//! create empty SessionItem that serves as a root item
SessionItem* CreateEmptyItem();

//! retrieve list of all possible item types suitable for
QStringList ValidTopItemTypes();

}; // namespace ItemFactory

#endif // BORNAGAIN_GUI_COREGUI_MODELS_ITEMFACTORY_H
