// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/SaveLoadInterface.cpp
//! @brief     Impelments save/load interface.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/mainwindow/SaveLoadInterface.h"

SaveLoadInterface::~SaveLoadInterface() = default;

QString SaveLoadInterface::fileName(const QString& projectDir) const
{
    const auto filename = fileName();
    return projectDir.isEmpty() ? filename : projectDir + "/" + filename;
}
