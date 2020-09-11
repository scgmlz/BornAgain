// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/SpecularDataWidget.h
//! @brief     Defines class SpecularDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SPECULARDATAWIDGETS_SPECULARDATAWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SPECULARDATAWIDGETS_SPECULARDATAWIDGET_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"

class SpecularDataCanvas;
class SpecularDataItem;
class IntensityDataPropertyWidget;

class SpecularDataWidget : public SessionItemWidget
{
    Q_OBJECT

public:
    SpecularDataWidget(QWidget* parent = nullptr);

    void setItem(SessionItem* jobItem);

    QList<QAction*> actionList();

private slots:
    void onContextMenuRequest(const QPoint& point);

private:
    SpecularDataItem* specularDataItem();

    SpecularDataCanvas* m_intensity_canvas;
    IntensityDataPropertyWidget* m_property_widget;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SPECULARDATAWIDGETS_SPECULARDATAWIDGET_H
