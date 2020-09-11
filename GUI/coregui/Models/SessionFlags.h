// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionFlags.h
//! @brief     Defines class SessionFlags
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_SESSIONFLAGS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_SESSIONFLAGS_H

#include "Wrap/WinDllMacros.h"
#include <qnamespace.h>

//! Collection of flags for SessionModel and SessionItem.

class BA_CORE_API_ SessionFlags
{
public:
    // SessionModel columns
    enum EColumn { ITEM_NAME, ITEM_VALUE, MAX_COLUMNS };
    Q_DECLARE_FLAGS(ModelColumn, EColumn)

    // SessionItem data roles
    enum ERoles {
        ModelTypeRole = Qt::UserRole + 1,
        FlagRole,
        DisplayNameRole,
        LimitsRole,
        DecimalRole,
        DefaultTagRole,
        CustomEditorRole,
        EndSessionRoles
    };
    Q_DECLARE_FLAGS(ItemDataRole, ERoles)

    // SessionItem appearance
    enum EAppearance { VISIBLE = 0x001, ENABLED = 0x002, EDITABLE = 0x004 };
    Q_DECLARE_FLAGS(ItemAppearance, EAppearance)
};

Q_DECLARE_OPERATORS_FOR_FLAGS(SessionFlags::ModelColumn)
Q_DECLARE_OPERATORS_FOR_FLAGS(SessionFlags::ItemDataRole)
Q_DECLARE_OPERATORS_FOR_FLAGS(SessionFlags::ItemAppearance)

#endif // BORNAGAIN_GUI_COREGUI_MODELS_SESSIONFLAGS_H
