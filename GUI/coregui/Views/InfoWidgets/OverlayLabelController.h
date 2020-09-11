// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/OverlayLabelController.h
//! @brief     Defines class OverlayLabelController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_OVERLAYLABELCONTROLLER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_OVERLAYLABELCONTROLLER_H

#include "Wrap/WinDllMacros.h"
#include <QObject>
#include <QString>

class OverlayLabelWidget;
class QAbstractScrollArea;

//! The OverlayLabelController class controlls appearance of InfoLabelWidget (position, show/hide)
//! on top of some scroll area.

class BA_CORE_API_ OverlayLabelController : public QObject
{
    Q_OBJECT
public:
    OverlayLabelController(QObject* parent = 0);

    void setText(const QString& text);

    void setArea(QAbstractScrollArea* area);

    void setShown(bool shown);

protected:
    bool eventFilter(QObject* obj, QEvent* event);

private:
    void updateLabelGeometry();

    OverlayLabelWidget* m_label;
    QAbstractScrollArea* m_area;
    QString m_text;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_OVERLAYLABELCONTROLLER_H
