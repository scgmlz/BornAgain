// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataSelectorToolBar.cpp
//! @brief     Implements class RealDataSelectorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RealDataSelectorToolBar.h"
#include "RealDataSelectorActions.h"
#include <QToolButton>

RealDataSelectorToolBar::RealDataSelectorToolBar(RealDataSelectorActions* actions, QWidget* parent)
    : StyledToolBar(parent)
    , m_import2dDataButton(new QToolButton)
    , m_import1dDataButton(new QToolButton)
    , m_removeDataButton(new QToolButton)
{
    setMinimumSize(minimumHeight(), minimumHeight());

    m_import2dDataButton->setText(QStringLiteral("Import 2D"));
    m_import2dDataButton->setIcon(QIcon(":/images/toolbar16light_newitem.svg"));
    m_import2dDataButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_import2dDataButton->setToolTip("Automatic import of 2D data formats.");
    addWidget(m_import2dDataButton);

    m_import1dDataButton->setText(QStringLiteral("Import 1D"));
    m_import1dDataButton->setIcon(QIcon(":/images/toolbar16light_newitem.svg"));
    m_import1dDataButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_import1dDataButton->setToolTip("Import columnwise ascii files.");
    addWidget(m_import1dDataButton);

    m_removeDataButton->setText("Remove");
    m_removeDataButton->setIcon(QIcon(":/images/toolbar16light_recycle.svg"));
    m_removeDataButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_removeDataButton->setToolTip("Remove selected data.");
    addWidget(m_removeDataButton);

    connect(m_import2dDataButton, &QToolButton::clicked, actions,
            &RealDataSelectorActions::onImport2dDataAction);
    connect(m_import1dDataButton, &QToolButton::clicked, actions,
            &RealDataSelectorActions::onImport1dDataAction);
    connect(m_removeDataButton, &QToolButton::clicked, actions,
            &RealDataSelectorActions::onRemoveDataAction);
}
