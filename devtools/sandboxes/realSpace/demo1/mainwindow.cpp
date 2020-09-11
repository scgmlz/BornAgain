// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      dev-tools/sandboxes/realSpace/demo1/mainwindow.cpp
//! @brief     Implement MainWin class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "mainwindow.h"

#include <QApplication>
#include <QBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QSettings>
#include <QSlider>

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

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    if ("q" == e->text())
        close();
}

void MainWindow::createLayout()
{
    setCentralWidget(new QWidget);

    auto vb = new QVBoxLayout;
    centralWidget()->setLayout(vb);

    vb->addWidget((w3d = new RealSpace::Widget3D));

#ifdef Q_OS_OSX
    QColor clrBg(160, 160, 160);
#else
    QColor clrBg(palette().color(QPalette::Background));
#endif
    w3d->setBackground(clrBg);

    auto hb = new QHBoxLayout;
    vb->addLayout(hb);

    auto btnSide = new QPushButton("side");
    auto btnTop = new QPushButton("top");
    auto btnOne = new QPushButton("one");
    auto btn0 = new QPushButton("=");
    auto btn1 = new QPushButton("1|n");
    auto btnP = new QPushButton("p");
    auto sldSigma = new QSlider(Qt::Horizontal);
    auto btnSq = new QPushButton("><");

    hb->addWidget(btnSide);
    hb->addWidget(btnTop);
    hb->addWidget(btnOne);
    hb->addStretch();
    hb->addWidget(btn0);
    hb->addWidget(btn1);
    hb->addWidget(btnP);
    hb->addStretch();
    hb->addWidget(sldSigma);
    hb->addWidget(btnSq);

    sldSigma->setRange(0, 30);
    sldSigma->setSingleStep(5);
    sldSigma->setTickInterval(5);
    sldSigma->setTickPosition(QSlider::TicksBelow);

    connect(btnSide, &QPushButton::clicked, [this]() { model()->setCameraSide(true); });

    connect(btnTop, &QPushButton::clicked, [this]() { model()->setCameraTop(true); });

    connect(btnOne, &QPushButton::clicked, [this]() { model()->setCameraOne(true); });

    connect(btn0, &QPushButton::clicked, [this]() { model()->switchBack(); });

    connect(btn1, &QPushButton::clicked, [this]() { model()->switchFront(); });

    connect(btnP, &QPushButton::clicked, [this]() { model()->switchOne(); });

    connect(btnSq, &QPushButton::clicked,
            [this, sldSigma]() { model()->square(sldSigma->value() / 100.f); });
}

DemoModel* MainWindow::model()
{
    auto model = dynamic_cast<DemoModel*>(w3d->model());
    Q_ASSERT(model);
    return model;
}
