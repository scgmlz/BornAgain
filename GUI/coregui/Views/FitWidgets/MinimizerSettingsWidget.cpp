// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/MinimizerSettingsWidget.cpp
//! @brief     Implements class MinimizerSettingsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/FitWidgets/MinimizerSettingsWidget.h"
#include "GUI/coregui/Models/FitSuiteItem.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/MinimizerItem.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentEditor.h"
#include <QPushButton>
#include <QVBoxLayout>

MinimizerSettingsWidget::MinimizerSettingsWidget(QWidget* parent)
    : QWidget(parent), m_currentItem(nullptr), m_componentEditor(new ComponentEditor)
{
    setWindowTitle(QLatin1String("Minimizer Settings"));

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_componentEditor);

    setLayout(layout);
}

QSize MinimizerSettingsWidget::minimumSizeHint() const
{
    return QSize(25, 25);
}

void MinimizerSettingsWidget::setItem(JobItem* jobItem)
{
    ASSERT(jobItem);
    setItem(jobItem->fitSuiteItem()->minimizerContainerItem());
}

void MinimizerSettingsWidget::setItem(MinimizerContainerItem* minimizerItem)
{
    ASSERT(minimizerItem);
    m_currentItem = minimizerItem;
    m_componentEditor->setItem(minimizerItem);
}
