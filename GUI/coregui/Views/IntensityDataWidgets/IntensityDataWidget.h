// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataWidget.h
//! @brief     Defines class IntensityDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_INTENSITYDATAWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_INTENSITYDATAWIDGET_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"
#include <memory>

class SessionItem;
class IntensityDataCanvas;
class IntensityDataPropertyWidget;
class IntensityDataItem;
class QAction;
class QContextMenuEvent;
class IntensityDataFFTPresenter;

//! A common widget to display color map (IntensityDataCanvas) and properties
//! (IntensityDataPropertyWidget) of intensity data item.

class BA_CORE_API_ IntensityDataWidget : public SessionItemWidget
{
    Q_OBJECT

public:
    IntensityDataWidget(QWidget* parent = 0);

    void setItem(SessionItem* jobItem);

    QList<QAction*> actionList();

private slots:
    void onContextMenuRequest(const QPoint& point);
    void onFFTAction();

private:
    IntensityDataItem* intensityDataItem();

    IntensityDataCanvas* m_intensityCanvas;
    IntensityDataPropertyWidget* m_propertyWidget;
    IntensityDataFFTPresenter* m_fftPresenter;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_INTENSITYDATAWIDGET_H
