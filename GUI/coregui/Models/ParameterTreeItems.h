// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParameterTreeItems.h
//! @brief     Defines classes for ParameterTreeItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_PARAMETERTREEITEMS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_PARAMETERTREEITEMS_H

#include "GUI/coregui/Models/SessionItem.h"

//! ParameterTreeItems is a collection of items necessary to form a tuning tree for
//! real time widget.

//! The ParameterLabelItem class represents a label (string without value, like 'Layer',
//! 'MultiLayer') in a parameter tuning tree.

class BA_CORE_API_ ParameterLabelItem : public SessionItem
{
public:
    ParameterLabelItem();
};

//! The ParameterItem class represent a tuning value in a parameter tuning tree.

class BA_CORE_API_ ParameterItem : public SessionItem
{
public:
    static const QString P_LINK;
    static const QString P_BACKUP;
    static const QString P_DOMAIN;
    ParameterItem();

    void propagateValueToLink(double newValue);
    SessionItem* linkedItem();

    void restoreFromBackup();
};

//! The ParameterContainerItem is a top item to hold all ParameterItem, represents an entry
//! point to parameter tuning tree. Part of JobItem.

class BA_CORE_API_ ParameterContainerItem : public SessionItem
{
public:
    ParameterContainerItem();
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_PARAMETERTREEITEMS_H
