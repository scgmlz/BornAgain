// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentViewToolBar.cpp
//! @brief     Implements class InstrumentViewToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InstrumentWidgets/InstrumentViewToolBar.h"
#include "GUI/coregui/Views/InstrumentWidgets/InstrumentViewActions.h"
#include <QMenu>
#include <QToolButton>

InstrumentViewToolBar::InstrumentViewToolBar(InstrumentViewActions* actions, QWidget* parent)
    : StyledToolBar(parent), m_addInstrumentButton(new QToolButton),
      m_removeInstrumentButton(new QToolButton), m_cloneInstrumentButton(new QToolButton),
      m_addInstrumentMenu(actions->instrumentMenu())
{
    m_addInstrumentButton->setText("Add");
    m_addInstrumentButton->setIcon(QIcon(":/images/shape-square-plus.svg"));
    m_addInstrumentButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_addInstrumentButton->setToolTip("Add new instrument");
    m_addInstrumentButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_addInstrumentButton->setPopupMode(QToolButton::MenuButtonPopup);
    m_addInstrumentButton->setMenu(m_addInstrumentMenu);
    addWidget(m_addInstrumentButton);

    m_removeInstrumentButton->setText("Remove");
    m_removeInstrumentButton->setIcon(QIcon(":/images/delete.svg"));
    m_removeInstrumentButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_removeInstrumentButton->setToolTip("Remove currently selected instrument");
    addWidget(m_removeInstrumentButton);

    m_cloneInstrumentButton->setText("Clone");
    m_cloneInstrumentButton->setIcon(QIcon(":/images/content-copy.svg"));
    m_cloneInstrumentButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_cloneInstrumentButton->setToolTip("Clone currently selected instrument");
    addWidget(m_cloneInstrumentButton);

    connect(m_addInstrumentButton, &QToolButton::clicked, this,
            &InstrumentViewToolBar::onAddInstrument);
    connect(m_removeInstrumentButton, &QToolButton::clicked, actions,
            &InstrumentViewActions::onRemoveInstrument);
    connect(m_cloneInstrumentButton, &QToolButton::clicked, actions,
            &InstrumentViewActions::onCloneInstrument);
}

void InstrumentViewToolBar::onAddInstrument()
{
    m_addInstrumentMenu->defaultAction()->triggered();
}
