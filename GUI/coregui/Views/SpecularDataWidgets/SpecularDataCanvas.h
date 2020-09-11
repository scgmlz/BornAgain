// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/SpecularDataCanvas.h
//! @brief     Defines class SpecularDataCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SPECULARDATAWIDGETS_SPECULARDATACANVAS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SPECULARDATAWIDGETS_SPECULARDATACANVAS_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"
#include "Wrap/WinDllMacros.h"
#include <QWidget>

class SpecularDataItem;
class SpecularPlotCanvas;

class BA_CORE_API_ SpecularDataCanvas : public SessionItemWidget
{
    Q_OBJECT
public:
    explicit SpecularDataCanvas(QWidget* parent = nullptr);

    void setItem(SessionItem* intensityItem) override;

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    QList<QAction*> actionList() override;

public slots:
    void onResetViewAction();
    void onSavePlotAction();
    void onMousePress(QMouseEvent* event);

private:
    SpecularDataItem* specularDataItem();
    void initActions();

    SpecularPlotCanvas* m_plot_canvas;
    QAction* m_reset_view_action;
    QAction* m_save_plot_action;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SPECULARDATAWIDGETS_SPECULARDATACANVAS_H
