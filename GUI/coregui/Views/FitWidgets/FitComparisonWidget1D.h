// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitComparisonWidget1D.h
//! @brief     Defines class FitComparisonWidget1D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITCOMPARISONWIDGET1D_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITCOMPARISONWIDGET1D_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"

class Data1DViewItem;
class FitComparison1DViewController;
class FitFlowWidget;
class IntensityDataPropertyWidget;
class JobItem;
class Plot1DCanvas;
class PlotStatusLabel;
class QAction;

//! The FitComparisonWidget class plots realdata, simulated data and relative difference map
//! during the course of the fit.

class BA_CORE_API_ FitComparisonWidget1D : public SessionItemWidget
{
    Q_OBJECT
public:
    explicit FitComparisonWidget1D(QWidget* parent = nullptr);
    ~FitComparisonWidget1D() override;

    virtual QList<QAction*> actionList() override;

private slots:
    void onResetViewAction();

protected:
    void subscribeToItem() override;
    void unsubscribeFromItem() override;

private:
    JobItem* jobItem();
    Data1DViewItem* viewItem();

    Plot1DCanvas* m_data_plot;
    Plot1DCanvas* m_diff_plot;
    FitFlowWidget* m_fitFlowWidget;
    PlotStatusLabel* m_statusLabel;
    IntensityDataPropertyWidget* m_propertyWidget;

    QAction* m_resetViewAction;
    FitComparison1DViewController* m_comparisonController;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITCOMPARISONWIDGET1D_H
