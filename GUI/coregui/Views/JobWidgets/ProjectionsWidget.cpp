// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsWidget.cpp
//! @brief     Implements class ProjectionsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/JobWidgets/ProjectionsWidget.h"
#include "GUI/coregui/Views/IntensityDataWidgets/ProjectionsPlot.h"
#include <QTabWidget>
#include <QVBoxLayout>

namespace
{
const int horizontal_projection_tab = 0;
const int vertical_projection_tab = 1;
} // namespace

ProjectionsWidget::ProjectionsWidget(QWidget* parent)
    : SessionItemWidget(parent), m_xProjection(new ProjectionsPlot("HorizontalLineMask")),
      m_yProjection(new ProjectionsPlot("VerticalLineMask")), m_tabWidget(new QTabWidget)
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    m_tabWidget->setTabPosition(QTabWidget::North);
    m_tabWidget->insertTab(HORIZONTAL, m_xProjection, "Horizontal");
    m_tabWidget->insertTab(VERTICAL, m_yProjection, "Vertical");

    layout->addWidget(m_tabWidget);
    setLayout(layout);

    setConnected(true);
}

void ProjectionsWidget::setItem(SessionItem* intensityItem)
{
    SessionItemWidget::setItem(intensityItem);
    m_xProjection->setItem(intensityItem);
    m_yProjection->setItem(intensityItem);
}

void ProjectionsWidget::onActivityModeChanged(MaskEditorFlags::Activity value)
{
    setConnected(false);

    if (value == MaskEditorFlags::HORIZONTAL_LINE_MODE)
        m_tabWidget->setCurrentIndex(horizontal_projection_tab);
    else if (value == MaskEditorFlags::VERTICAL_LINE_MODE)
        m_tabWidget->setCurrentIndex(vertical_projection_tab);

    setConnected(true);
}

void ProjectionsWidget::onMarginsChanged(double left, double right)
{
    m_xProjection->onMarginsChanged(left, right);
    m_yProjection->onMarginsChanged(left, right);
}

void ProjectionsWidget::onTabChanged(int tab_index)
{
    if (tab_index == horizontal_projection_tab)
        emit changeActivityRequest(MaskEditorFlags::HORIZONTAL_LINE_MODE);
    else if (tab_index == vertical_projection_tab)
        emit changeActivityRequest(MaskEditorFlags::VERTICAL_LINE_MODE);
}

void ProjectionsWidget::setConnected(bool isConnected)
{
    if (isConnected)
        connect(m_tabWidget, &QTabWidget::currentChanged, this, &ProjectionsWidget::onTabChanged);
    else
        disconnect(m_tabWidget, &QTabWidget::currentChanged, this,
                   &ProjectionsWidget::onTabChanged);
}
