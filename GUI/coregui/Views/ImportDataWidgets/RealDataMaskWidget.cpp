// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataMaskWidget.cpp
//! @brief     Implements class RealDataMaskWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/ImportDataWidgets/RealDataMaskWidget.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/MaskItems.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Views/MaskWidgets/MaskEditor.h"
#include <QAction>
#include <QBoxLayout>

RealDataMaskWidget::RealDataMaskWidget(QWidget* parent)
    : SessionItemWidget(parent), m_maskEditor(new MaskEditor)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout* hlayout = new QHBoxLayout;
    hlayout->setMargin(0);
    hlayout->setSpacing(0);

    hlayout->addWidget(m_maskEditor);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addLayout(hlayout);
    setLayout(mainLayout);
}

QList<QAction*> RealDataMaskWidget::actionList()
{
    return m_maskEditor->topToolBarActions();
}

void RealDataMaskWidget::subscribeToItem()
{
    auto intensityItem = intensityDataItem();
    auto container = maskContainer(intensityItem);
    m_maskEditor->setMaskContext(intensityItem->model(), container->index(), intensityItem);
    m_maskEditor->update();
}

void RealDataMaskWidget::unsubscribeFromItem()
{
    m_maskEditor->resetContext();
}

IntensityDataItem* RealDataMaskWidget::intensityDataItem()
{
    IntensityDataItem* result = dynamic_cast<RealDataItem*>(currentItem())->intensityDataItem();
    ASSERT(result);
    return result;
}

MaskContainerItem* RealDataMaskWidget::maskContainer(IntensityDataItem* intensityData)
{
    auto containerItem = intensityData->getItem(IntensityDataItem::T_MASKS);
    if (!containerItem)
        containerItem =
            intensityData->model()->insertNewItem("MaskContainer", intensityData->index());

    MaskContainerItem* result = dynamic_cast<MaskContainerItem*>(containerItem);
    return result;
}
