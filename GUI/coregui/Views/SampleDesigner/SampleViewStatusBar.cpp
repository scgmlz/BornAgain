// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleViewStatusBar.cpp
//! @brief     Implements class SampleViewActivityStatusBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SampleViewStatusBar.h"
#include "mainwindow.h"
#include <QHBoxLayout>
#include <QStatusBar>
#include <QToolButton>

SampleViewStatusBar::SampleViewStatusBar(MainWindow* mainWindow)
    : QWidget(mainWindow), m_dockMenuButton(nullptr)
    , m_mainWindow(mainWindow)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto layout = new QHBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);

    m_dockMenuButton = new QToolButton;
    m_dockMenuButton->setIcon(QIcon(":/images/statusbar_dockmenu.svg"));
    m_dockMenuButton->setToolTip("Docks layout menu");
    connect(m_dockMenuButton, &QToolButton::clicked,
            this, &SampleViewStatusBar::dockMenuRequest);

    layout->addStretch();
    layout->addWidget(m_dockMenuButton);

    setLayout(layout);
    initAppearance();
}

//! Init appearance of MainWindow's statusBar.

void SampleViewStatusBar::initAppearance()
{
    Q_ASSERT(m_mainWindow);
    m_mainWindow->statusBar()->addWidget(this, 1);
    m_mainWindow->statusBar()->setSizeGripEnabled(false);
    this->hide();
}
