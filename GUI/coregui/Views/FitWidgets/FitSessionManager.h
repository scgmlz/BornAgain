// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitSessionManager.h
//! @brief     Defines class FitSessionManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITSESSIONMANAGER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITSESSIONMANAGER_H

#include "Wrap/WinDllMacros.h"
#include <QMap>
#include <QObject>

class JobModel;
class SessionItem;
class JobItem;
class FitSessionController;
class JobMessagePanel;

//! Handles all activity related to the simultaneous running of fitting jobs.

class BA_CORE_API_ FitSessionManager : public QObject
{
    Q_OBJECT
public:
    FitSessionManager(QObject* parent = nullptr);

    void setMessagePanel(JobMessagePanel* messagePanel);

    FitSessionController* sessionController(JobItem* item);

    void disableLogging();

private:
    FitSessionController* createController(JobItem* jobItem);
    void removeController(SessionItem* jobItem);

    //!< Fit controller which is currently attached to jobMessagePanel
    FitSessionController* m_activeController;
    JobMessagePanel* m_jobMessagePanel;
    QMap<SessionItem*, FitSessionController*> m_item_to_controller;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITSESSIONMANAGER_H
