// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/InfoPanel.h
//! @brief     Defines class InfoPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_INFOPANEL_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_INFOPANEL_H

#include "Wrap/WinDllMacros.h"
#include <QFrame>

class QStackedWidget;
class InfoPanelToolBar;
class QResizeEvent;

//! Frame for widgets with tool bar on top and collapse/expand button functionality.
//! Intended for QDockWindow, to be able to quickly minimize/maximize its appearance.

//! Used in JobMessagePanel.

class BA_CORE_API_ InfoPanel : public QFrame
{
    Q_OBJECT
public:
    explicit InfoPanel(QWidget* parent);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

signals:
    void widgetHeightRequest(int);
    void widgetCloseRequest();

protected slots:
    void onExpandButtonClicked();
    void onCloseButtonClicked();
    void setContentVisible(bool editor_status, bool dock_notify = false);

protected:
    bool isContentVisible();
    void resizeEvent(QResizeEvent* event);

    InfoPanelToolBar* m_toolBar;
    QStackedWidget* m_stackedWidget;
    int m_cached_height;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_COMMONWIDGETS_INFOPANEL_H
