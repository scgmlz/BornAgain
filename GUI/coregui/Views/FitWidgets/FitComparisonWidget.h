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

#ifndef FITCOMPARISONWIDGET_H
#define FITCOMPARISONWIDGET_H

#include "SessionItemWidget.h"
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
class FitComparisonController;

//! The FitComparisonWidget class plots realdata, simulated data and relative difference map
//! during the course of the fit.

class BA_CORE_API_ FitComparisonWidget : public SessionItemWidget
{
    Q_OBJECT

public:
    explicit FitComparisonWidget(QWidget* parent = 0);
    ~FitComparisonWidget();

    virtual QList<QAction*> actionList();

private slots:
    void onResetViewAction();

protected:
    void subscribeToItem();
    void unsubscribeFromItem();

private:
    void calculateRelativeDifference();
    void unsubscribeFromChildren();

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
    FitComparisonController* m_comparisonController;
};

#endif // FITCOMPARISONWIDGET_H
