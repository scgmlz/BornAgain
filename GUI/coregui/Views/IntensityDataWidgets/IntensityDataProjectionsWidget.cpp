// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataProjectionsWidget.cpp
//! @brief     Defines class IntensityDataProjectionsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/IntensityDataWidgets/IntensityDataProjectionsWidget.h"
#include "GUI/coregui/Models/DataItemUtils.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/ProjectionItems.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Views/JobWidgets/ProjectionsEditor.h"
#include <QVBoxLayout>

IntensityDataProjectionsWidget::IntensityDataProjectionsWidget(QWidget* parent)
    : SessionItemWidget(parent), m_projectionsEditor(new ProjectionsEditor)
{
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_projectionsEditor);

    setLayout(vlayout);
}

QList<QAction*> IntensityDataProjectionsWidget::actionList()
{
    return m_projectionsEditor->topToolBarActions();
}

void IntensityDataProjectionsWidget::subscribeToItem()
{
    auto container = projectionContainer(intensityDataItem());

    m_projectionsEditor->setContext(intensityDataItem()->model(), container->index(),
                                    intensityDataItem());
}

void IntensityDataProjectionsWidget::unsubscribeFromItem()
{
    m_projectionsEditor->resetContext();
}

IntensityDataItem* IntensityDataProjectionsWidget::intensityDataItem()
{
    return DataItemUtils::intensityDataItem(currentItem());
}

ProjectionContainerItem*
IntensityDataProjectionsWidget::projectionContainer(IntensityDataItem* intensityItem)
{
    ASSERT(intensityItem);

    auto containerItem = intensityItem->getItem(IntensityDataItem::T_PROJECTIONS);
    if (!containerItem)
        containerItem = intensityItem->model()->insertNewItem(
            "ProjectionContainer", intensityItem->index(), -1, IntensityDataItem::T_PROJECTIONS);

    return dynamic_cast<ProjectionContainerItem*>(containerItem);
}
