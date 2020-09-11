// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      dev-tools/sandboxes/realSpace/demo1/main.cpp
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

#include "demo_model.h"
#include "mainwindow.h"
#include <QApplication>
#include <memory>

class App : public QApplication
{
public:
    App(int& argc, char* argv[]);
    ~App();

    int exec();
};

App::App(int& argc, char* argv[]) : QApplication(argc, argv)
{
    setApplicationName("BornAgain real space demo");
}

App::~App() {}

int App::exec()
{
    MainWindow win;
    win.show();

    std::unique_ptr<DemoModel> model(new DemoModel);
    win.widget3d().setModel(model.get());

    return QApplication::exec();
}

int main(int argc, char* argv[])
{
    App(argc, argv).exec();
}
