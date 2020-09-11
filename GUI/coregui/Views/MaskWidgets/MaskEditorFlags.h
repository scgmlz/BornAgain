// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskEditorFlags.h
//! @brief     Defines class MaskEditorFlags
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKEDITORFLAGS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKEDITORFLAGS_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

//! Help class to define various flags for MaskEditor operation

class BA_CORE_API_ MaskEditorFlags
{
public:
    enum EActivityType {
        SELECTION_MODE,
        PAN_ZOOM_MODE,
        RECTANGLE_MODE,
        POLYGON_MODE,
        VERTICAL_LINE_MODE,
        HORIZONTAL_LINE_MODE,
        ELLIPSE_MODE,
        ROI_MODE,
        MASKALL_MODE,
        PREVIOUS_MODE
    };
    Q_DECLARE_FLAGS(Activity, EActivityType)

    enum EMoveType { BRING_TO_FRONT, SEND_TO_BACK };
    Q_DECLARE_FLAGS(Stacking, EMoveType)

    enum EMaskValue { MASK_OFF, MASK_ON };
    Q_DECLARE_FLAGS(MaskValue, EMaskValue)

    enum EPresentationType { MASK_EDITOR, MASK_PRESENTER };
    Q_DECLARE_FLAGS(PresentationType, EPresentationType)
};

Q_DECLARE_OPERATORS_FOR_FLAGS(MaskEditorFlags::Activity)
Q_DECLARE_OPERATORS_FOR_FLAGS(MaskEditorFlags::Stacking)
Q_DECLARE_OPERATORS_FOR_FLAGS(MaskEditorFlags::MaskValue)
Q_DECLARE_OPERATORS_FOR_FLAGS(MaskEditorFlags::PresentationType)

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKEDITORFLAGS_H
