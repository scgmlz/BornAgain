// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/SpecularDataWidget.cpp
//! @brief     Implements class SpecularDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SpecularDataWidgets/SpecularDataWidget.h"
#include "GUI/coregui/Models/DataItemUtils.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/SpecularDataItem.h"
#include "GUI/coregui/Views/IntensityDataWidgets/IntensityDataPropertyWidget.h"
#include "GUI/coregui/Views/SpecularDataWidgets/SpecularDataCanvas.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QBoxLayout>
#include <QMenu>

SpecularDataWidget::SpecularDataWidget(QWidget* parent)
    : SessionItemWidget(parent), m_intensity_canvas(new SpecularDataCanvas),
      m_property_widget(new IntensityDataPropertyWidget)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto hlayout = new QHBoxLayout;
    hlayout->setMargin(0);
    hlayout->setSpacing(0);
    hlayout->addWidget(m_intensity_canvas);
    hlayout->addWidget(m_property_widget);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addLayout(hlayout);

    setLayout(mainLayout);

    connect(m_intensity_canvas, &SpecularDataCanvas::customContextMenuRequested, this,
            &SpecularDataWidget::onContextMenuRequest);

    m_property_widget->setVisible(false);
}

void SpecularDataWidget::setItem(SessionItem* jobItem)
{
    SessionItemWidget::setItem(jobItem);
    m_intensity_canvas->setItem(specularDataItem());
    m_property_widget->setItem(specularDataItem());
}

QList<QAction*> SpecularDataWidget::actionList()
{
    return m_intensity_canvas->actionList() + m_property_widget->actionList();
}

void SpecularDataWidget::onContextMenuRequest(const QPoint& point)
{
    QMenu menu;
    for (auto action : actionList())
        menu.addAction(action);
    menu.exec(point);
}

SpecularDataItem* SpecularDataWidget::specularDataItem()
{
    return DataItemUtils::specularDataItem(currentItem());
}
