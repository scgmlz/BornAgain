// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      dev-tools/sandboxes/realSpace/demo2/mainwindow.cpp
//! @brief     Implements MainWin class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QBoxLayout>
#include <QComboBox>
#include <QKeyEvent>
#include <QMenuBar>
#include <QSettings>

//------------------------------------------------------------------------------

static QString const MAINWIN_GEOMETRY("MainWin Geometry");

MainWindow::MainWindow()
{
    setWindowTitle(qApp->applicationName());
    createLayout();

    QSettings s;
    restoreGeometry(s.value(MAINWIN_GEOMETRY).toByteArray());
}

void MainWindow::closeEvent(QCloseEvent*)
{
    QSettings s;
    s.setValue(MAINWIN_GEOMETRY, saveGeometry());
}

void MainWindow::createLayout()
{
    setCentralWidget(new QWidget);

    auto hb = new QHBoxLayout;
    centralWidget()->setLayout(hb);

    // the thing
    hb->addWidget((w3d_1 = new RealSpace::Widget3D));
    hb->setStretchFactor(w3d_1, 2);
    w3d_1->setBackground(palette().color(QPalette::Background));

    auto vb = new QVBoxLayout;
    hb->addLayout(vb);
    hb->setStretchFactor(vb, 1);

    vb->addWidget((w3d_2 = new RealSpace::Widget3D));
    vb->setStretchFactor(w3d_2, 1);

    vb->addWidget((w3d_3 = new RealSpace::Widget3D));
    vb->setStretchFactor(w3d_3, 1);

    vb->addWidget((combo = new QComboBox));

    {
        using namespace RealSpace::Particles;
        connect(combo, static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),
                [&](int i) { emit showKind(EShape(int(Particle::firstKind) + i)); });

        for (EShape k = Particle::firstKind; k <= Particle::lastKind; k = EShape(uint(k) + 1))
            combo->addItem(name(k));
    }
}

//------------------------------------------------------------------------------
