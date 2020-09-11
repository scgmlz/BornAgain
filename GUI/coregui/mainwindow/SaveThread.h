// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/SaveThread.h
//! @brief     Defines SaveThread classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MAINWINDOW_SAVETHREAD_H
#define BORNAGAIN_GUI_COREGUI_MAINWINDOW_SAVETHREAD_H

#include "Wrap/WinDllMacros.h"
#include <QObject>
#include <QThread>

class ProjectDocument;

//! Performs saving of heavy intensity data in a thread.

class BA_CORE_API_ SaveThread : public QThread
{
    Q_OBJECT
public:
    explicit SaveThread(QObject* parent = 0);
    ~SaveThread();

    void run() override;

    void setSaveContext(ProjectDocument* document, const QString& project_file_name);

signals:
    void saveReady();

private:
    ProjectDocument* m_document;
    QString m_projectFile;
};

#endif // BORNAGAIN_GUI_COREGUI_MAINWINDOW_SAVETHREAD_H
