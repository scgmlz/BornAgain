// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/OutputDataIOHistory.h
//! @brief     Defines OutputDataIOHistory classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MAINWINDOW_OUTPUTDATAIOHISTORY_H
#define BORNAGAIN_GUI_COREGUI_MAINWINDOW_OUTPUTDATAIOHISTORY_H

#include "Wrap/WinDllMacros.h"
#include <QDateTime>
#include <QMap>
#include <QVector>

class SaveLoadInterface;

//! Holds information about last save for items with non-XML data.

class BA_CORE_API_ OutputDataSaveInfo
{
public:
    OutputDataSaveInfo() : m_data(nullptr) {}

    static OutputDataSaveInfo createSaved(const SaveLoadInterface* item);

    const SaveLoadInterface* item() const { return m_data; }

    QString fileName() const { return m_file_name; }

    bool wasModifiedSinceLastSave() const;

private:
    bool wasSavedBefore(const QDateTime& dtime) const;

    QDateTime m_last_saved;
    QString m_file_name;
    const SaveLoadInterface* m_data;
};

//! Save history information for collection of items with non-XML data.

class BA_CORE_API_ OutputDataDirHistory
{
public:
    OutputDataDirHistory() {}

    void markAsSaved(const SaveLoadInterface* item);

    bool wasModifiedSinceLastSave(const SaveLoadInterface* item);

    bool contains(const SaveLoadInterface* item);

    QStringList savedFileNames() const;

private:
    OutputDataSaveInfo itemInfo(const SaveLoadInterface* item) const;

    QVector<OutputDataSaveInfo> m_history;
};

//! Save history information for set of directories.

class BA_CORE_API_ OutputDataIOHistory
{
public:
    bool hasHistory(const QString& dirname) const;

    bool wasModifiedSinceLastSave(const QString& dirname, const SaveLoadInterface* item);

    void setHistory(const QString& dirname, const OutputDataDirHistory& history);

    QStringList savedFileNames(const QString& dirname) const;

private:
    //!< Correspondance of directory name to save history.
    QMap<QString, OutputDataDirHistory> m_dir_history;
};

#endif // BORNAGAIN_GUI_COREGUI_MAINWINDOW_OUTPUTDATAIOHISTORY_H
