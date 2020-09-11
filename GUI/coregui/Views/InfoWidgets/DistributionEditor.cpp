// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/DistributionEditor.cpp
//! @brief     Implements class DistributionEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InfoWidgets/DistributionEditor.h"
#include "GUI/coregui/Models/DistributionItems.h"
#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Views/InfoWidgets/DistributionWidget.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentFlatView.h"
#include <QBoxLayout>

namespace
{
int minimum_width = 250;
}

DistributionEditor::DistributionEditor(QWidget* parent)
    : SessionItemWidget(parent), m_propertyEditor(new ComponentFlatView), m_item(nullptr),
      m_plotwidget(new DistributionWidget), m_box(new QGroupBox)
{

    auto boxLayout = new QVBoxLayout;
    m_propertyEditor->setMaximumWidth(minimum_width);
    boxLayout->addWidget(m_propertyEditor);
    boxLayout->setContentsMargins(0, 0, 0, 0);
    m_box->setLayout(boxLayout);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(m_box);
    verticalLayout->addStretch(1);

    auto mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_plotwidget, 1);
    mainLayout->addSpacing(5);
    mainLayout->addLayout(verticalLayout);

    setLayout(mainLayout);
}

void DistributionEditor::subscribeToItem()
{
    m_propertyEditor->clearEditor();
    m_propertyEditor->setItem(currentItem());

    currentItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) { onPropertyChanged(name); }, this);

    m_plotwidget->setItem(distributionItem());
}

void DistributionEditor::onPropertyChanged(const QString& property_name)
{
    if (property_name == GroupItem::T_ITEMS)
        m_plotwidget->setItem(distributionItem());
}

GroupItem* DistributionEditor::groupItem()
{
    auto result = dynamic_cast<GroupItem*>(currentItem());
    ASSERT(result);
    return result;
}

DistributionItem* DistributionEditor::distributionItem()
{
    auto result = dynamic_cast<DistributionItem*>(groupItem()->currentItem());
    ASSERT(result);
    return result;
}

void DistributionEditor::setNameOfEditor(QString name)
{
    m_box->setTitle(name);
    m_plotwidget->setXAxisName(name);
}
