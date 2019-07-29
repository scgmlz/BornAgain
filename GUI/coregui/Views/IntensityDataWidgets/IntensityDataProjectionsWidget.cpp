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

#include "IntensityDataProjectionsWidget.h"
#include "IntensityDataItem.h"
#include "ProjectionItems.h"
#include "SessionModel.h"
#include "JobItem.h"
#include "ProjectionsEditor.h"
#include "DataItemUtils.h"
#include <QVBoxLayout>

IntensityDataProjectionsWidget::IntensityDataProjectionsWidget(QWidget* parent)
    : SessionItemWidget(parent)
    , m_projectionsEditor(new ProjectionsEditor)
{
    QVBoxLayout *vlayout = new QVBoxLayout(this);
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

    m_projectionsEditor->setContext(intensityDataItem()->model(),
                                    container->index(), intensityDataItem());
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
    Q_ASSERT(intensityItem);

    auto containerItem = intensityItem->getItem(IntensityDataItem::T_PROJECTIONS);
    if (!containerItem)
        containerItem = intensityItem->model()->insertNewItem(Constants::ProjectionContainerType,
                                                              intensityItem->index(), -1,
                                                              IntensityDataItem::T_PROJECTIONS);

    return dynamic_cast<ProjectionContainerItem*>(containerItem);
}


