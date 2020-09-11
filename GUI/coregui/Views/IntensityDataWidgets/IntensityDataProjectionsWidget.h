// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataProjectionsWidget.h
//! @brief     Defines class IntensityDataProjectionsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_INTENSITYDATAPROJECTIONSWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_INTENSITYDATAPROJECTIONSWIDGET_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"

class ProjectionsEditor;
class IntensityDataItem;
class ProjectionContainerItem;

//! Main widget to embed projections editor for IntensityDataItem.
//! Part of RealDataPresenter and JobResultsPresenter.

class BA_CORE_API_ IntensityDataProjectionsWidget : public SessionItemWidget
{
    Q_OBJECT

public:
    IntensityDataProjectionsWidget(QWidget* parent = 0);

    QList<QAction*> actionList();

protected:
    void subscribeToItem();
    void unsubscribeFromItem();

private:
    IntensityDataItem* intensityDataItem();
    ProjectionContainerItem* projectionContainer(IntensityDataItem* intensityItem);

    ProjectionsEditor* m_projectionsEditor;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_INTENSITYDATAPROJECTIONSWIDGET_H
