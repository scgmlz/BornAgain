// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/main/MessageHandler.cpp
//! @brief     Implements function MessageHandler
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/main/MessageHandler.h"
#include <QMessageBox>
#include <iostream>

//! This is set by main to be the message handler of our GUI.
void MessageHandler(QtMsgType type, const QMessageLogContext&, const QString& msg)
{
    switch (type) {
    case QtDebugMsg:
        if (!msg.size()) // KDE will pass a zero-length msg qstring
            break;
        std::cerr << "DEBUG: " << msg.toStdString() << std::endl;
        break;
    case QtInfoMsg:
        std::cerr << "INFO: " << msg.toStdString() << std::endl;
        break;
    case QtWarningMsg:
    default:
        if (msg.left(4) == "QXcb")
            return;
        std::cerr << "WARNING: " << msg.toStdString() << std::endl;
        // QMessageBox::warning(QApplication::activeWindow(), qAppName(), msg);
        break;
    case QtFatalMsg:
        std::cerr << "FATAL: " << msg.toStdString() << std::endl;
        qApp->restoreOverrideCursor();
        QMessageBox::critical(QApplication::activeWindow(), qAppName(),
                              "Sorry, you encountered a fatal bug.\n"
                              "The application will terminate.\n"
                              "Please note the following and inform the maintainers.\n\n"
                                  + msg + "\n");
        qApp->quit();
        exit(1);
    }
}
