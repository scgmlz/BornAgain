// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/PyImportAssistant.cpp
//! @brief     Implements class PyImportAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "PyImportAssistant.h"
#include "AppSvc.h"
#include "mainwindow.h"
#include "projectmanager.h"
#include "GUIHelpers.h"
#include "PyImport.h"
#include "MultiLayer.h"
#include "BABuild.h"
#include "GUIObjectBuilder.h"
#include "ProjectUtils.h"
#include "SysUtils.h"
#include "BornAgainNamespace.h"
#include "ComboSelectorDialog.h"
#include "DetailedMessageBox.h"
#include <QFileDialog>
#include <QTextStream>
#include <QApplication>
#include <QDebug>

namespace {

//! Returns directory with BornAgain library. If PYTHONPATH is not empty,
//! returns an empty string.

std::string bornagainDir() {
    std::string pythonPath = SysUtils::getenv("PYTHONPATH");
    return pythonPath.empty() ? BABuild::buildLibDir() : std::string();
}

//! Returns a name from the list which looks like a function name intended for sample
//! creation.

QString getCandidate(const QStringList& funcNames) {
    if (funcNames.isEmpty())
        return QString();

    for(auto str : funcNames) {
        QString name = str.toLower();
        if (name.contains(QStringLiteral("sample")) || name.contains(QStringLiteral("multilayer")))
            return str;
    }

    return funcNames.front();
}

}

PyImportAssistant::PyImportAssistant(MainWindow* mainwin)
    : QObject(mainwin)
    , m_mainWindow(mainwin)
{

}

void PyImportAssistant::exec()
{
    auto fileName = fileNameToOpen();

    if (fileName.isEmpty())
        return;

    QString snippet = readFile(fileName);
    if (snippet.isEmpty())
        return;

    QString funcName = getPySampleFunctionName(snippet);
    if (funcName.isEmpty())
        return;

    auto multilayer = createMultiLayer(snippet, funcName);
    if (!multilayer)
        return;

    populateModels(*multilayer, GUIHelpers::baseName(fileName));
}

//! Lets user to select Python file on disk.

QString PyImportAssistant::fileNameToOpen()
{
    QString dirname = AppSvc::projectManager()->userImportDir();

    QString result = QFileDialog::getOpenFileName(m_mainWindow, "Open python script",
            dirname, "Python scripts (*.py)");

    saveImportDir(result);

    return result;
}

//! Saves file location as a future import dir.

void PyImportAssistant::saveImportDir(const QString& fileName)
{
    if (fileName.isEmpty())
        return;

    AppSvc::projectManager()->setImportDir(GUIHelpers::fileDir(fileName));
}

//! Read content of text file and returns it as a multi-line string.
//! Pop-ups warning dialog in the case of failure.

QString PyImportAssistant::readFile(const QString& fileName)
{
    QString result;

    try {
        result = ProjectUtils::readTextFile(fileName);

    } catch (const std::exception& ex) {
        QString message("Can't read the file. \n\n");
        message += QString::fromStdString(std::string(ex.what()));
        GUIHelpers::warning(m_mainWindow, "File read failure.", message);
    }

    return result;
}

//! Returns the name of function which might generate a MultiLayer in Python code snippet.
//! Pop-ups dialog and asks user for help in the case of doubts.

QString PyImportAssistant::getPySampleFunctionName(const QString& snippet)
{
    QStringList funcList;

    QApplication::setOverrideCursor(Qt::WaitCursor);
    try {
        auto funcs = PyImport::listOfFunctions(snippet.toStdString(), bornagainDir());
        funcList = GUIHelpers::fromStdStrings(funcs);

    } catch (const std::exception& ex) {
        QApplication::restoreOverrideCursor();
        QString message("Exception thrown while executing a Python code.\n\n");
        QString details = QString::fromStdString(std::string(ex.what()));
        DetailedMessageBox warning(m_mainWindow, "Python failure", message, details);
        warning.exec();

        return QString();
    }
    QApplication::restoreOverrideCursor();

    return selectPySampleFunction(funcList);
}

//! Lets user select a function name which generates a MultiLayer.

QString PyImportAssistant::selectPySampleFunction(const QStringList& funcNames)
{
    QString result;

    if(funcNames.empty()) {
        QString message("Python code doesn't contain any functions.\n\n");
        GUIHelpers::warning(m_mainWindow, "Python failure", message);

    } else if(funcNames.size() == 1) {
        return funcNames.front();

    } else {
        ComboSelectorDialog dialog;
        dialog.addItems(funcNames, getCandidate(funcNames));
        dialog.setTextTop("Python code contains a few functions. Do you know by chance, "
                          "which one is intended to produce a valid MultiLayer?");
        dialog.setTextBottom("Please select a valid function in combo box and press OK to continue.");
        if(dialog.exec() == QDialog::Accepted)
            result = dialog.currentText();
    }

    return result;
}

//! Creates a multi-layer by executing a funcName in embedded Python.
//! Function is supposed to be in code provided by 'snippet'.

std::unique_ptr<MultiLayer> PyImportAssistant::createMultiLayer(const QString& snippet,
                                                                const QString& funcName)
{
    std::unique_ptr<MultiLayer> result;

    QApplication::setOverrideCursor(Qt::WaitCursor);
    try {
        result = PyImport::createFromPython(snippet.toStdString(),
                                            funcName.toStdString(), bornagainDir());

    } catch (const std::exception& ex) {
        QApplication::restoreOverrideCursor();
        QString message("Exception thrown while executing a Python code.\n\n");
        QString details = QString::fromStdString(std::string(ex.what()));
        DetailedMessageBox warning(m_mainWindow, "Python failure", message, details);
        warning.exec();
    }
    QApplication::restoreOverrideCursor();

    return result;
}

//! Populates GUI models with domain multilayer.

void PyImportAssistant::populateModels(const MultiLayer& multilayer, const QString& sampleName)
{
    try {
        QString name = sampleName;
        if (multilayer.getName() != BornAgain::MultiLayerType)
            name = QString::fromStdString(multilayer.getName());

        GUIObjectBuilder::populateSampleModel(m_mainWindow->sampleModel(),
                m_mainWindow->materialModel(), multilayer, name);

        QString message("Seems that import was successfull.\n\n"
                        "Check SampleView for new sample and material editor for new materials.");
        GUIHelpers::information(m_mainWindow, "PyImport", message);

    } catch(const std::exception& ex) {
        QString message("Exception thrown while trying to build GUI models.\n"
                        "GUI models might be in unconsistent state.\n\n");
        QString details = QString::fromStdString(std::string(ex.what()));
        DetailedMessageBox warning(m_mainWindow, "GUIObjectBuilder failure", message, details);
        warning.exec();
    }

}

