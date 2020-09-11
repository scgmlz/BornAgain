// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitFlowWidget.cpp
//! @brief     Implement class FitFlowWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/FitWidgets/FitFlowWidget.h"
#include "GUI/coregui/Models/FitSuiteItem.h"
#include "GUI/coregui/Views/FitWidgets/HistogramPlot.h"
#include <QVBoxLayout>

FitFlowWidget::FitFlowWidget(QWidget* parent)
    : SessionItemWidget(parent), m_histPlot(new HistogramPlot)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_histPlot);

    setStyleSheet("background-color:white;");
    setLayout(layout);
}

void FitFlowWidget::subscribeToItem()
{
    fitSuiteItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) {
            if (name == FitSuiteItem::P_ITERATION_COUNT) {
                int iter = fitSuiteItem()->getItemValue(FitSuiteItem::P_ITERATION_COUNT).toInt();
                double chi = fitSuiteItem()->getItemValue(FitSuiteItem::P_CHI2).toDouble();
                if (iter == 1)
                    m_histPlot->clearData();
                m_histPlot->addData(static_cast<double>(iter), chi);
            }
        },
        this);
}

void FitFlowWidget::unsubscribeFromItem()
{
    m_histPlot->clearData();
    m_x.clear();
    m_y.clear();
}

FitSuiteItem* FitFlowWidget::fitSuiteItem()
{
    return dynamic_cast<FitSuiteItem*>(currentItem());
}
