// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/AdjustingScrollArea.h
//! @brief     Defines class AdjustingScrollArea
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_ADJUSTINGSCROLLAREA_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_ADJUSTINGSCROLLAREA_H

#include "Wrap/WinDllMacros.h"
#include <QScrollArea>

//! Modification of standard scroll area, which makes widget with dynamic layout ocuupy whole
//! available space.

class BA_CORE_API_ AdjustingScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    AdjustingScrollArea(QWidget* parent = 0);
    void setWidget(QWidget* w);

    QSize sizeHint() const;

private:
    bool eventFilter(QObject* obj, QEvent* ev);
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_ADJUSTINGSCROLLAREA_H
