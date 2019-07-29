// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUISpecial/GUISaveLoadProject.h
//! @brief     Defines GUISaveLoadProject test.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef GUISAVELOADPROJECT_H
#define GUISAVELOADPROJECT_H

#include "IFunctionalTest.h"
#include <QString>
#include <QMap>
#include <QVector>
#include <memory>

class ApplicationModels;
class SessionModel;

//! Functional test to check persistency of application models after save/load.

class GUISaveLoadProject : public IFunctionalTest
{
public:
    GUISaveLoadProject();

protected:
    bool runTest();

private:

    struct DataXML {
        QString m_model_tag;
        QString m_model_xml;
    };

    int run_job();
    int save_project(const QString& projectName);
    int save_project_dir(const QString& projectName);
    int save_xml(const QString& projectName);
    int load_project(const QString& projectName);
    int check_difference(const QString& projectName1, const QString& projectName2);
    DataXML dataXML(SessionModel* model);
    void resetModels();

    std::unique_ptr<ApplicationModels> m_models;
    //! Correspondance of projectname to collected xml data.
    QMap<QString, QVector<DataXML>> m_results;
};

#endif // GUISAVELOADPROJECT_H
