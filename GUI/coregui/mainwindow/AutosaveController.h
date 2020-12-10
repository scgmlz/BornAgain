//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/AutosaveController.h
//! @brief     Defines class AutosaveController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_MAINWINDOW_AUTOSAVECONTROLLER_H
#define BORNAGAIN_GUI_COREGUI_MAINWINDOW_AUTOSAVECONTROLLER_H

#include <QObject>

class ProjectDocument;
class UpdateTimer;

//! Triggers autosave request after some accumulated ammount of document changes.

class AutosaveController : public QObject {
    Q_OBJECT
public:
    explicit AutosaveController(QObject* parent = 0);

    void setDocument(ProjectDocument* document);

    //! Sets autosave time (in msec)
    void setAutosaveTime(int timerInterval);

    //! The complete path to the autosave dir (e.g. '/projects/Untitled2/autosave').
    QString autosaveDir() const;
    QString autosaveName() const;

    //! remove auto save directory for given project and all its content
    void removeAutosaveDir();

signals:
    void autosaveRequest();

private slots:
    void onTimerTimeout();
    void onDocumentDestroyed(QObject* object);
    void onDocumentModified();

private:
    void autosave();
    void setDocumentConnected(bool set_connected);

    //! Tries to make sure that the directory for auto saving exists. Tries to create it if not
    //! existing so far. No creation, if project directory itself doesn't exist at all.
    //! Returns true, if the directory finally exists.
    bool assureAutoSaveDirExists() const;

    ProjectDocument* m_document;
    UpdateTimer* m_timer;
};

#endif // BORNAGAIN_GUI_COREGUI_MAINWINDOW_AUTOSAVECONTROLLER_H
