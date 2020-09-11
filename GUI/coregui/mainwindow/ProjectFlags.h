// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/ProjectFlags.h
//! @brief     Defines class ProjectFlags
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MAINWINDOW_PROJECTFLAGS_H
#define BORNAGAIN_GUI_COREGUI_MAINWINDOW_PROJECTFLAGS_H

#include "Wrap/WinDllMacros.h"
#include <QFlags>

class BA_CORE_API_ ProjectFlags
{
public:
    enum EDocumentStatus {
        STATUS_OK = 0x0001,
        STATUS_WARNING = 0x0002,
        STATUS_FAILED = 0x0004,
    };

    Q_DECLARE_FLAGS(DocumentStatus, EDocumentStatus)

    static void setFlag(ProjectFlags::DocumentStatus& flags, EDocumentStatus status)
    {
        flags |= status;
    }
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ProjectFlags::DocumentStatus)

#endif // BORNAGAIN_GUI_COREGUI_MAINWINDOW_PROJECTFLAGS_H
