// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/AppSvc.h
//! @brief     Defines class AppSvc
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MAINWINDOW_APPSVC_H
#define BORNAGAIN_GUI_COREGUI_MAINWINDOW_APPSVC_H

#include "Core/Basics/ISingleton.h"
#include "Wrap/WinDllMacros.h"

class ProjectManager;
class MaterialModel;

//! The AppSvc class provides common access for key components of the GUI.

class BA_CORE_API_ AppSvc : public ISingleton<AppSvc>
{
    friend class ISingleton<AppSvc>;

public:
    static ProjectManager* projectManager();
    static void subscribe(ProjectManager* projectManager);
    static void unsubscribe(ProjectManager* projectManager);

    static MaterialModel* materialModel();
    static void subscribe(MaterialModel* materialModel);
    static void unsubscribe(MaterialModel* materialModel);

private:
    AppSvc();
    ProjectManager* this_projectManager();
    MaterialModel* this_materialModel();
    void this_subscribe(ProjectManager* projectManager);
    void this_unsubscribe(ProjectManager* projectManager);
    void this_subscribe(MaterialModel* materialModel);
    void this_unsubscribe(MaterialModel* materialModel);

    ProjectManager* m_projectManager;
    MaterialModel* m_materialModel;
};

#endif // BORNAGAIN_GUI_COREGUI_MAINWINDOW_APPSVC_H
