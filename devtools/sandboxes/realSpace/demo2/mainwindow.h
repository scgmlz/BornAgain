// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      dev-tools/sandboxes/realSpace/demo2/mainwindow.h
//! @brief     Defines MainWin class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BA3D_MAINWINDOW_H
#define BA3D_MAINWINDOW_H

#include <QMainWindow>
#include "GUI/ba3d/model/particles.h"
#include "GUI/ba3d/widget.h"

//------------------------------------------------------------------------------

class QComboBox;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

    RealSpace::Widget3D& widg3t_1() { return *w3d_1; }

    RealSpace::Widget3D& widg3t_2() { return *w3d_2; }

    RealSpace::Widget3D& widg3t_3() { return *w3d_3; }

signals:
    void showKind(RealSpace::Particles::EShape);

private:
    void closeEvent(QCloseEvent*);

    RealSpace::Widget3D *w3d_1, *w3d_2, *w3d_3;
    QComboBox* combo;

    void createLayout();
};

//------------------------------------------------------------------------------
#endif
