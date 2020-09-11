// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      dev-tools/sandboxes/realSpace/demo2/main.cpp
//! @brief     Main program
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/ba3d/def.h"
#include "GUI/ba3d/view/camera.h"

#include "mainwindow.h"
#include "modelLayers.h"
#include "modelShowcase.h"
#include <QApplication>

//------------------------------------------------------------------------------

class App : public QApplication
{
public:
    App(int& argc, char* argv[]);
    ~App();

    int exec();
};

App::App(int& argc, char* argv[]) : QApplication(argc, argv)
{
    setOrganizationName("c53");
    setApplicationName("ba3d");
}

App::~App() {}

int App::exec()
{
    MainWindow win;
    win.show();

    QScopedPointer<ModelLayers> ml(new ModelLayers);
    QScopedPointer<ModelShowcase> ms(new ModelShowcase);

    auto &w1(win.widg3t_1()), &w2(win.widg3t_2()), &w3(win.widg3t_3());

    w1.setModel(ml.data());
    w2.setModel(ml.data());
    w3.setModel(ms.data());

    w2.cam().lookAt(RealSpace::Camera::Position(
        RealSpace::Vector3D::_z * 90, RealSpace::Vector3D(0, 0, 0), RealSpace::Vector3D::_y));

    connect(&win, &MainWindow::showKind, [&](RealSpace::Particles::EShape kind) {
        ml->showKind(kind);
        ms->showKind(kind);
    });

    return QApplication::exec();
}

//------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    App(argc, argv).exec();
}

//------------------------------------------------------------------------------
