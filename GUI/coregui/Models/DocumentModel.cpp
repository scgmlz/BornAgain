// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DocumentModel.cpp
//! @brief     Implements class DocumentModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/DocumentModel.h"
#include "GUI/coregui/Models/SimulationOptionsItem.h"

DocumentModel::DocumentModel(QObject* parent) : SessionModel(SessionXML::DocumentModelTag, parent)
{
    setObjectName(SessionXML::DocumentModelTag);
}

SimulationOptionsItem* DocumentModel::simulationOptionsItem()
{
    return topItem<SimulationOptionsItem>();
}
