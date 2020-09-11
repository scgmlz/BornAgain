// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/AppSvc.cpp
//! @brief     Implements class AppSvc
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/mainwindow/AppSvc.h"
#include "GUI/coregui/utils/GUIHelpers.h"

ProjectManager* AppSvc::projectManager()
{
    return instance().this_projectManager();
}

void AppSvc::subscribe(ProjectManager* projectManager)
{
    return instance().this_subscribe(projectManager);
}

void AppSvc::unsubscribe(ProjectManager* projectManager)
{
    instance().this_unsubscribe(projectManager);
}

MaterialModel* AppSvc::materialModel()
{
    return instance().this_materialModel();
}

void AppSvc::subscribe(MaterialModel* materialModel)
{
    return instance().this_subscribe(materialModel);
}

void AppSvc::unsubscribe(MaterialModel* materialModel)
{
    instance().this_unsubscribe(materialModel);
}

AppSvc::AppSvc() : m_projectManager(nullptr), m_materialModel(nullptr) {}

ProjectManager* AppSvc::this_projectManager()
{
    if (!m_projectManager)
        throw GUIHelpers::Error("AppSvc::projectManager() -> Error. Attempt to access "
                                "non existing ProjectManager.");

    return m_projectManager;
}

MaterialModel* AppSvc::this_materialModel()
{
    return m_materialModel;
}

void AppSvc::this_subscribe(ProjectManager* projectManager)
{
    if (m_projectManager != nullptr)
        throw GUIHelpers::Error("AppSvc::projectManager() -> Error. Attempt to subscribe "
                                "ProjectManager twice.");

    m_projectManager = projectManager;
}

void AppSvc::this_unsubscribe(ProjectManager* projectManager)
{
    if (m_projectManager != projectManager)
        throw GUIHelpers::Error("AppSvc::projectManager() -> Error. Attempt to unsubscribe "
                                "ProjectManager before it was subscribed.");

    m_projectManager = nullptr;
}

void AppSvc::this_subscribe(MaterialModel* materialModel)
{
    if (m_materialModel)
        throw GUIHelpers::Error("AppSvc::projectManager() -> Error. Attempt to subscribe "
                                "MaterialModel twice.");

    m_materialModel = materialModel;
}

void AppSvc::this_unsubscribe(MaterialModel* materialModel)
{
    if (m_materialModel != materialModel)
        throw GUIHelpers::Error("AppSvc::projectManager() -> Error. Attempt to unsubscribe "
                                "MaterialModel before it was subscribed.");

    m_materialModel = nullptr;
}
