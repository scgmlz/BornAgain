// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/main/MessageHandler.h
//! @brief     Declares function MessageHandler
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_MAIN_MESSAGEHANDLER_H
#define BORNAGAIN_GUI_MAIN_MESSAGEHANDLER_H

#include <QApplication>

void MessageHandler(QtMsgType type, const QMessageLogContext&, const QString& msg);

#endif // BORNAGAIN_GUI_MAIN_MESSAGEHANDLER_H
