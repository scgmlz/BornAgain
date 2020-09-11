// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitFlowWidget.h
//! @brief     Defines class FitFlowWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITFLOWWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITFLOWWIDGET_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"

class HistogramPlot;
class FitSuiteItem;

//! The FitFlowWidget class is intended for showing chi2 .vs interation count dependency.
//! The main goal is to fill vacant place in FitComparisonWidget.

class BA_CORE_API_ FitFlowWidget : public SessionItemWidget
{
    Q_OBJECT
public:
    explicit FitFlowWidget(QWidget* parent = nullptr);

protected:
    void subscribeToItem();
    void unsubscribeFromItem();

private:
    FitSuiteItem* fitSuiteItem();

    HistogramPlot* m_histPlot;
    QVector<double> m_x;
    QVector<double> m_y;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITFLOWWIDGET_H
