// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/ProjectUtils.cpp
//! @brief     Implements ProjectUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/mainwindow/ProjectUtils.h"
#include "GUI/coregui/Models/ItemFileNameUtils.h"
#include "GUI/coregui/mainwindow/AppSvc.h"
#include "GUI/coregui/mainwindow/projectdocument.h"
#include "GUI/coregui/mainwindow/projectmanager.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFileInfo>

QString ProjectUtils::projectName(const QString& projectFileName)
{
    QFileInfo info(projectFileName);
    return info.baseName();
}

QString ProjectUtils::projectDir(const QString& projectFileName)
{
    QFileInfo info(projectFileName);
    return info.path();
}

QString ProjectUtils::autosaveSubdir()
{
    return "autosave";
}

//! From '/projects/Untitled2/Untitled2.pro' returns '/projects/Untitled2/autosave'.

QString ProjectUtils::autosaveDir(const QString& projectFileName)
{
    return ProjectUtils::projectDir(projectFileName) + "/" + autosaveSubdir();
}

//! From '/projects/Untitled2/Untitled2.pro' returns '/projects/Untitled2/autosave/Untitled2.pro'.

QString ProjectUtils::autosaveName(const QString& projectFileName)
{
    return ProjectUtils::autosaveDir(projectFileName) + "/"
           + ProjectUtils::projectName(projectFileName) + ProjectDocument::projectFileExtension();
}

bool ProjectUtils::exists(const QString& fileName)
{
    QFileInfo info(fileName);
    return info.exists();
}

bool ProjectUtils::hasAutosavedData(const QString& projectFileName)
{
    return exists(projectFileName) && exists(autosaveName(projectFileName));
}

QString ProjectUtils::lastModified(const QString& fileName)
{
    QFileInfo info(fileName);
    return info.lastModified().toString("hh:mm:ss, MMMM d, yyyy");
}

QStringList ProjectUtils::nonXMLDataInDir(const QString& dirname)
{
    QDir dir(dirname);

    if (!dir.exists())
        throw GUIHelpers::Error("ProjectUtils::nonXMLDataInDir() -> Error. Non existing "
                                "directory '"
                                + dirname + "'.");

    return dir.entryList(ItemFileNameUtils::nonXMLFileNameFilters());
}

bool ProjectUtils::removeRecursively(const QString& dirname)
{
    QDir dir(dirname);

    if (!dir.exists())
        throw GUIHelpers::Error("ProjectUtils::removeRecursively() -> Error. Non existing "
                                "directory '"
                                + dirname + "'.");

    return dir.removeRecursively();
}

bool ProjectUtils::removeFile(const QString& dirname, const QString& filename)
{
    QString name = dirname + "/" + filename;
    QFile fin(name);

    if (!fin.exists())
        throw GUIHelpers::Error("ProjectUtils::removeFile() -> Error. Non existing "
                                "file '"
                                + name + "'.");

    return fin.remove();
}

bool ProjectUtils::removeFiles(const QString& dirname, const QStringList& filenames)
{
    bool success(true);

    for (auto& name : filenames)
        success &= removeFile(dirname, name);

    return success;
}

QStringList ProjectUtils::substract(const QStringList& lhs, const QStringList& rhs)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    auto lhs_set = QSet<QString>{lhs.begin(), lhs.end()};
    auto rhs_set = QSet<QString>{rhs.begin(), rhs.end()};
    QSet<QString> diff = lhs_set.subtract(rhs_set);
    return diff.values();
#else
    QSet<QString> diff = lhs.toSet().subtract(rhs.toSet());
    return diff.toList();
#endif
}

QString ProjectUtils::readTextFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw GUIHelpers::Error("ProjectUtils::readTextFile -> Error. Can't open the file '"
                                + fileName + "' for reading.");
    QTextStream in(&file);
    return in.readAll();
}

QString ProjectUtils::userExportDir()
{
    return AppSvc::projectManager()->userExportDir();
}
