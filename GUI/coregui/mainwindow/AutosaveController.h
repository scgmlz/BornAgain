// ************************************************************************** //
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
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MAINWINDOW_AUTOSAVECONTROLLER_H
#define BORNAGAIN_GUI_COREGUI_MAINWINDOW_AUTOSAVECONTROLLER_H

#include "Wrap/WinDllMacros.h"
#include <QObject>

class ProjectDocument;
class UpdateTimer;

//! Triggers autosave request after some accumulated ammount of document changes.

class BA_CORE_API_ AutosaveController : public QObject
{
    Q_OBJECT
public:
    explicit AutosaveController(QObject* parent = 0);

    void setDocument(ProjectDocument* document);

    //! Sets autosave time (in msec)
    void setAutosaveTime(int timerInterval);

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

    ProjectDocument* m_document;
    UpdateTimer* m_timer;
};

#endif // BORNAGAIN_GUI_COREGUI_MAINWINDOW_AUTOSAVECONTROLLER_H
