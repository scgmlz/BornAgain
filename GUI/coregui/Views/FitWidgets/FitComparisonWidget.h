// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitComparisonWidget.h
//! @brief     Defines class FitComparisonWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITCOMPARISONWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITCOMPARISONWIDGET_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"
#include <QMap>

class JobItem;
class IntensityDataItem;
class ColorMapCanvas;
class SessionModel;
class FitFlowWidget;
class PlotStatusLabel;
class QAction;
class IntensityDataPropertyWidget;
class PropertyRepeater;
class FitComparisonController2D;

//! The FitComparisonWidget class plots realdata, simulated data and relative difference map
//! during the course of the fit.

class BA_CORE_API_ FitComparisonWidget : public SessionItemWidget
{
    Q_OBJECT

public:
    explicit FitComparisonWidget(QWidget* parent = nullptr);
    ~FitComparisonWidget() override;

    virtual QList<QAction*> actionList() override;

private slots:
    void onResetViewAction();

protected:
    void subscribeToItem() override;
    void unsubscribeFromItem() override;

private:
    JobItem* jobItem();
    IntensityDataItem* realDataItem();
    IntensityDataItem* simulatedDataItem();
    IntensityDataItem* diffItem();

    ColorMapCanvas* m_realDataPlot;
    ColorMapCanvas* m_simulatedDataPlot;
    ColorMapCanvas* m_relativeDiffPlot;
    FitFlowWidget* m_fitFlowWidget;
    PlotStatusLabel* m_statusLabel;
    IntensityDataPropertyWidget* m_propertyWidget;

    QAction* m_resetViewAction;
    FitComparisonController2D* m_comparisonController;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITCOMPARISONWIDGET_H
