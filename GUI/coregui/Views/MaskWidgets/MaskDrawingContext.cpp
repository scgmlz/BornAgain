// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskDrawingContext.cpp
//! @brief     Implements class MaskDrawingContext
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/MaskWidgets/MaskDrawingContext.h"

MaskDrawingContext::MaskDrawingContext()
    : m_current_activity(MaskEditorFlags::PAN_ZOOM_MODE), m_mask_value(MaskEditorFlags::MASK_ON),
      m_drawing_in_progress(false)
{
}

MaskEditorFlags::Activity MaskDrawingContext::getActivityType() const
{
    return m_current_activity;
}

void MaskDrawingContext::setActivityType(MaskEditorFlags::Activity value)
{
    m_current_activity = value;
}

void MaskDrawingContext::setMaskValue(MaskEditorFlags::MaskValue value)
{
    m_mask_value = value;
}

bool MaskDrawingContext::isSelectionMode() const
{
    return m_current_activity == MaskEditorFlags::SELECTION_MODE;
}

bool MaskDrawingContext::isInZoomMode() const
{
    return m_current_activity == MaskEditorFlags::PAN_ZOOM_MODE;
}

bool MaskDrawingContext::isRectangleShapeMode() const
{
    return (m_current_activity == MaskEditorFlags::RECTANGLE_MODE)
           || (m_current_activity == MaskEditorFlags::ELLIPSE_MODE)
           || (m_current_activity == MaskEditorFlags::ROI_MODE);
}

bool MaskDrawingContext::isRectangleMode() const
{
    return m_current_activity == MaskEditorFlags::RECTANGLE_MODE;
}

bool MaskDrawingContext::isEllipseMode() const
{
    return m_current_activity == MaskEditorFlags::ELLIPSE_MODE;
}

bool MaskDrawingContext::isPolygonMode() const
{
    return m_current_activity == MaskEditorFlags::POLYGON_MODE;
}

bool MaskDrawingContext::isLineMode() const
{
    return isVerticalLineMode() || isHorizontalLineMode();
}

bool MaskDrawingContext::isVerticalLineMode() const
{
    return m_current_activity == MaskEditorFlags::VERTICAL_LINE_MODE;
}

bool MaskDrawingContext::isHorizontalLineMode() const
{
    return m_current_activity == MaskEditorFlags::HORIZONTAL_LINE_MODE;
}

bool MaskDrawingContext::isMaskAllMode() const
{
    return m_current_activity == MaskEditorFlags::MASKALL_MODE;
}

bool MaskDrawingContext::isROIMode() const
{
    return m_current_activity == MaskEditorFlags::ROI_MODE;
}

bool MaskDrawingContext::isDrawingInProgress() const
{
    return m_drawing_in_progress;
}

void MaskDrawingContext::setDrawingInProgress(bool value)
{
    m_drawing_in_progress = value;
}

bool MaskDrawingContext::getMaskValue() const
{
    return bool(m_mask_value);
}

//! return true, if proposed activity requires the cancel of drawing
//! i.e. there is an ungoing polygon drawing, but user wants to start other drawing
bool MaskDrawingContext::isActivityRequiresDrawingCancel(
    MaskEditorFlags::Activity proposed_new_activity)
{
    if (isDrawingInProgress() && isPolygonMode()
        && proposed_new_activity >= MaskEditorFlags::PAN_ZOOM_MODE)
        return true;
    return false;
}

//! Returns model type corresponding to current activity.

QString MaskDrawingContext::activityToModelType() const
{
    if (isRectangleMode())
        return "RectangleMask";
    if (isEllipseMode())
        return "EllipseMask";
    if (isROIMode())
        return "RegionOfInterest";
    return "";
}

//! Returns model row corresponding to given activity. All shapes, except ROI, will be added
//! on top of each other. ROI shape will be added at the bottom.

int MaskDrawingContext::activityToRow() const
{
    if (isROIMode())
        return -1;
    return 0;
}
