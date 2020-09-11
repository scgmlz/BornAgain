// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/main/main.cpp
//! @brief     Main function of the whole GUI
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/FitWidgets/FitProgressInfo.h"
#include "GUI/coregui/mainwindow/SplashScreen.h"
#include "GUI/coregui/mainwindow/mainwindow.h"
#include "GUI/coregui/utils/hostosinfo.h"
#include "GUI/main/MessageHandler.h"
#include "GUI/main/appoptions.h"
#include <QLocale>
#include <QMetaType>

void messageHandler(QtMsgType, const QMessageLogContext&, const QString&) {}

int main(int argc, char* argv[])
{
    ApplicationOptions options(argc, argv);
    if (!options.isConsistent())
        return 0;

    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
    qRegisterMetaType<QVector<double>>("QVector<double>");

    if (!options.disableHighDPISupport())
        QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication app(argc, argv);

    qInstallMessageHandler(MessageHandler);

    std::unique_ptr<SplashScreen> splash;
    if (!options.find("no-splash")) {
        splash.reset(new SplashScreen);
        splash->start(/*show_during*/ 1200);
    }

    MainWindow win;
    if (options.find("geometry"))
        win.resize(options.mainWindowSize());

    win.show();

    if (splash)
        splash->finish(&win);

    return app.exec();
}
