// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/EnvironmentEditor.cpp
//! @brief     Implements class EnvironmentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InstrumentWidgets/EnvironmentEditor.h"
#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Views/CommonWidgets/ColumnResizer.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentEditor.h"
#include "GUI/coregui/utils/LayoutUtils.h"
#include <QGridLayout>
#include <QSpacerItem>

namespace
{
const QString background_title("Background");
}

EnvironmentEditor::EnvironmentEditor(ColumnResizer* columnResizer, QWidget* parent)
    : SessionItemWidget(parent), m_columnResizer(columnResizer),
      m_backgroundEditor(new ComponentEditor(ComponentEditor::GroupWidget, background_title)),
      m_gridLayout(new QGridLayout)
{
    m_gridLayout->addWidget(m_backgroundEditor, 0, 0);
    m_gridLayout->addWidget(LayoutUtils::placeHolder(), 0, 1);
    m_gridLayout->addWidget(LayoutUtils::placeHolder(), 0, 2);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(m_gridLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);

    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 0);
    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 1);
    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 2);
}

void EnvironmentEditor::subscribeToItem()
{
    m_backgroundEditor->setItem(instrumentItem()->backgroundGroup());
}

void EnvironmentEditor::unsubscribeFromItem()
{
    m_backgroundEditor->clearEditor();
}

InstrumentItem* EnvironmentEditor::instrumentItem()
{
    auto result = dynamic_cast<InstrumentItem*>(currentItem());
    ASSERT(result);
    return result;
}
