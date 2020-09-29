// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/ProjectUtils.h
//! @brief     Defines ProjectUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MAINWINDOW_PROJECTUTILS_H
#define BORNAGAIN_GUI_COREGUI_MAINWINDOW_PROJECTUTILS_H

#include <QString>

//! Defines convenience function for project manager and document.

namespace ProjectUtils
{

//! Returns project name deduced from project file name.
QString projectName(const QString& projectFileName);

//! Returns project directory deduced from project file name.
QString projectDir(const QString& projectFileName);

//! Returns fixed name for autosave sub-directory.
QString autosaveSubdir();

//! Returns name of autosave directory for project with given project file name.
QString autosaveDir(const QString& projectFileName);

//! Returns name of project for autoSave from given project file name.
QString autosaveName(const QString& projectFileName);

//! Returns true if file exists.
bool exists(const QString& fileName);

//! Returns true if project with given projectFileName contains autosaved data.
bool hasAutosavedData(const QString& projectFileName);

//! Returns a string representing modification time of given file
QString lastModified(const QString& fileName);

//! Returns list of files on disk representing nonXML data.
QStringList nonXMLDataInDir(const QString& dirname);

//! Removes recursively directory with given name. Directory name is relative
//! to the parent (working directory of the executable).
bool removeRecursively(const QString& dirname);

//! Remove file from given directory.
bool removeFile(const QString& dirname, const QString& filename);
bool removeFiles(const QString& dirname, const QStringList& filenames);

//! Returns list of string from lhs, which are not in rhs.
QStringList substract(const QStringList& lhs, const QStringList& rhs);

//! Returns multi-lione string representing content of text file.
QString readTextFile(const QString& fileName);

//! Returns directory which user is normally using to export files.
QString userExportDir();

} // namespace ProjectUtils

#endif // BORNAGAIN_GUI_COREGUI_MAINWINDOW_PROJECTUTILS_H
