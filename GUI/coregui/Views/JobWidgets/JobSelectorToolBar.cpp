// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobSelectorToolBar.cpp
//! @brief     Implements class JobSelectorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/JobWidgets/JobSelectorToolBar.h"
#include "GUI/coregui/Views/JobWidgets/JobSelectorActions.h"
#include <QToolButton>

JobSelectorToolBar::JobSelectorToolBar(JobSelectorActions* actions, QWidget* parent)
    : StyledToolBar(parent), m_runJobButton(new QToolButton), m_removeJobButton(new QToolButton)
{
    setMinimumSize(minimumHeight(), minimumHeight());

    m_runJobButton->setText("Run");
    m_runJobButton->setIcon(QIcon(":/images/play.svg"));
    m_runJobButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_runJobButton->setToolTip("Run currently selected job");
    addWidget(m_runJobButton);

    m_removeJobButton->setText("Remove");
    m_removeJobButton->setIcon(QIcon(":/images/delete.svg"));
    m_removeJobButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_removeJobButton->setToolTip("Remove currently selected job.");
    addWidget(m_removeJobButton);

    connect(m_runJobButton, &QToolButton::clicked, actions, &JobSelectorActions::onRunJob);
    connect(m_removeJobButton, &QToolButton::clicked, actions, &JobSelectorActions::onRemoveJob);
}
