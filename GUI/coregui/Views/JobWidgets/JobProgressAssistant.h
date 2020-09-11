// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobProgressAssistant.h
//! @brief     Defines class JobProgressAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBPROGRESSASSISTANT_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBPROGRESSASSISTANT_H

#include "Wrap/WinDllMacros.h"
#include <QObject>

class MainWindow;

//! The JobProgressAssistant class helps JobView to visualize current progress.

class BA_CORE_API_ JobProgressAssistant : public QObject
{
    Q_OBJECT
public:
    JobProgressAssistant(MainWindow* mainWindow);

private slots:
    void onGlobalProgress(int progress);

private:
    MainWindow* m_mainWindow;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBPROGRESSASSISTANT_H
