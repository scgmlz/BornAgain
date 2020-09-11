// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/PyImportAssistant.h
//! @brief     Implements class PyImportAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MAINWINDOW_PYIMPORTASSISTANT_H
#define BORNAGAIN_GUI_COREGUI_MAINWINDOW_PYIMPORTASSISTANT_H

#ifdef BORNAGAIN_PYTHON

#include "Wrap/WinDllMacros.h"
#include <QObject>
#include <memory>

class MainWindow;
class MultiLayer;

//! Assists in importing Python object to GUI models.

class BA_CORE_API_ PyImportAssistant : public QObject
{
    Q_OBJECT
public:
    PyImportAssistant(MainWindow* mainwin);

    void exec();

private:
    QString fileNameToOpen();
    void saveImportDir(const QString& fileName);
    QString readFile(const QString& fileName);
    QString getPySampleFunctionName(const QString& snippet);
    QString selectPySampleFunction(const QStringList& funcNames);
    std::unique_ptr<MultiLayer> createMultiLayer(const QString& snippet, const QString& funcName);
    void populateModels(const MultiLayer& multilayer, const QString& sampleName);

    MainWindow* m_mainWindow;
};

#endif // BORNAGAIN_PYTHON

#endif // BORNAGAIN_GUI_COREGUI_MAINWINDOW_PYIMPORTASSISTANT_H
