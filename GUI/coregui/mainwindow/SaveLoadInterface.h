// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/SaveLoadInterface.h
//! @brief     Defines save/load interface.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MAINWINDOW_SAVELOADINTERFACE_H
#define BORNAGAIN_GUI_COREGUI_MAINWINDOW_SAVELOADINTERFACE_H

#include "Wrap/WinDllMacros.h"

#include <QDateTime>
#include <QString>

//! Purely virtual interface to handle non-XML
//! data save and load.

class BA_CORE_API_ SaveLoadInterface
{
public:
    virtual ~SaveLoadInterface();

    //! Loads non-XML data from _projectDir_ and returns
    //! success flag.
    virtual bool load(const QString& projectDir) = 0;

    //! Saves non-XML data in _projectDir_ and returns
    //! success flag.
    virtual bool save(const QString& projectDir) = 0;

    //! Checks if object owns non-XML data
    virtual bool containsNonXMLData() const = 0;

    //! Indicates last modification timepoint.
    virtual QDateTime lastModified() const = 0;

    //! Reports file name to save/load non-XML data.
    virtual QString fileName() const = 0;

    //! Reports file name to save/load non-XML data with directory
    //! name attached.
    QString fileName(const QString& projectDir) const;
};

#endif // BORNAGAIN_GUI_COREGUI_MAINWINDOW_SAVELOADINTERFACE_H
