//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/ExportToPython.h
//! @brief     Defines ExportToPython namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_CORE_EXPORT_EXPORTTOPYTHON_H
#define BORNAGAIN_CORE_EXPORT_EXPORTTOPYTHON_H

#include <string>

class MultiLayer;
class ISimulation;

//! Wraps methods that serialize objects to Python.

namespace ExportToPython {

std::string generateSampleCode(const MultiLayer& multilayer);
std::string generateSimulationCode(const ISimulation& simulation);

} // namespace ExportToPython

#endif // BORNAGAIN_CORE_EXPORT_EXPORTTOPYTHON_H
