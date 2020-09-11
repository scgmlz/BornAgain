// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/SaveService.h
//! @brief     Defines class SaveService
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MAINWINDOW_SAVESERVICE_H
#define BORNAGAIN_GUI_COREGUI_MAINWINDOW_SAVESERVICE_H

#include "Wrap/WinDllMacros.h"
#include <QObject>
#include <QQueue>

class ProjectDocument;
class AutosaveController;

//! Provides save/autosave of ProjectDocument in a thread.

class BA_CORE_API_ SaveService : public QObject
{
    Q_OBJECT

public:
    explicit SaveService(QObject* parent = 0);

    void setDocument(ProjectDocument* document);

    void save(const QString& project_file_name);

    void setAutosaveEnabled(bool value);
    bool isAutosaveEnabled() const;

    //! Sets autosave time (in msec)
    void setAutosaveTime(int timerInterval);

    bool isSaving() const;

    void stopService();

signals:
    void projectSaved();

public slots:
    void onAutosaveRequest();

private slots:
    void onProjectSaved();

private:
    void process_queue();

    QQueue<QString> m_save_queue;
    bool m_is_saving;
    AutosaveController* m_autosave;
    ProjectDocument* m_document;
};

#endif // BORNAGAIN_GUI_COREGUI_MAINWINDOW_SAVESERVICE_H
