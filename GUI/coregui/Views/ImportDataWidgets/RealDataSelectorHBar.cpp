// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataSelectorHBar.cpp
//! @brief     Defines class RealDataSelectorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/ImportDataWidgets/RealDataSelectorHBar.h"
#include "GUI/coregui/Views/ImportDataWidgets/RealDataSelectorActions.h"
#include <QMenu>
#include <QToolButton>

namespace
{
const int toolbar_icon_size = 24;
}

RealDataSelectorHBar::RealDataSelectorHBar(RealDataSelectorActions* actions, QWidget* parent)
    : QToolBar(parent), m_dropDownMenuButton(nullptr), m_actions(actions)
{
    setIconSize(QSize(toolbar_icon_size, toolbar_icon_size));
    setProperty("_q_custom_style_disabled", QVariant(true));

    auto empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    addWidget(empty);

    m_dropDownMenuButton = new QToolButton;
    m_dropDownMenuButton->setIcon(QIcon(":/images/toolbar24dark_hambar.svg"));
    m_dropDownMenuButton->setToolTip("More Actions...");
    connect(m_dropDownMenuButton, &QToolButton::clicked, this,
            &RealDataSelectorHBar::onDropDownMenuRequest);
    addWidget(m_dropDownMenuButton);
}

void RealDataSelectorHBar::onDropDownMenuRequest()
{
    QMenu menu;
    menu.setToolTipsVisible(true);
    auto action = menu.addAction("Import 1D data");
    action->setToolTip("Import 1D data");
    connect(action, &QAction::triggered, m_actions, &RealDataSelectorActions::onImport1dDataAction);

    action = menu.addAction("Import 2D data");
    action->setToolTip("Import 2D data");
    connect(action, &QAction::triggered, m_actions, &RealDataSelectorActions::onImport2dDataAction);

    action = menu.addAction("Rotate selected data");
    action->setToolTip("Rotate currently selected data");
    connect(action, &QAction::triggered, m_actions, &RealDataSelectorActions::onRotateDataRequest);

    action = menu.addAction("Remove selected data");
    action->setToolTip("Remove currently selected data");
    connect(action, &QAction::triggered, m_actions, &RealDataSelectorActions::onRemoveDataAction);

    menu.exec(mapToGlobal(m_dropDownMenuButton->pos() + QPoint(-210, 48)));
}
