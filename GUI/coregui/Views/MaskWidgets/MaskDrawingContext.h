// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskDrawingContext.h
//! @brief     Defines class MaskDrawingContext
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKDRAWINGCONTEXT_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKDRAWINGCONTEXT_H

#include "GUI/coregui/Views/MaskWidgets/MaskEditorFlags.h"
#include "Wrap/WinDllMacros.h"

//! Helper class for MaskGraphicsScene to hold drawing conditions

class BA_CORE_API_ MaskDrawingContext
{
public:
    MaskDrawingContext();

    MaskEditorFlags::Activity getActivityType() const;
    void setActivityType(MaskEditorFlags::Activity value);
    void setMaskValue(MaskEditorFlags::MaskValue value);

    bool isSelectionMode() const;
    bool isInZoomMode() const;
    bool isRectangleShapeMode() const;
    bool isRectangleMode() const;
    bool isEllipseMode() const;
    bool isPolygonMode() const;
    bool isLineMode() const;
    bool isVerticalLineMode() const;
    bool isHorizontalLineMode() const;
    bool isMaskAllMode() const;
    bool isROIMode() const;

    bool isDrawingInProgress() const;
    void setDrawingInProgress(bool value);

    bool getMaskValue() const;

    bool isActivityRequiresDrawingCancel(MaskEditorFlags::Activity proposed_new_activity);

    QString activityToModelType() const;
    int activityToRow() const;

private:
    MaskEditorFlags::Activity m_current_activity;
    MaskEditorFlags::MaskValue m_mask_value;
    bool m_drawing_in_progress;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKDRAWINGCONTEXT_H
