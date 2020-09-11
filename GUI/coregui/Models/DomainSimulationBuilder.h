// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DomainSimulationBuilder.h
//! @brief     Defines class DomainSimulationBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_DOMAINSIMULATIONBUILDER_H
#define BORNAGAIN_GUI_COREGUI_MODELS_DOMAINSIMULATIONBUILDER_H

#include "Wrap/WinDllMacros.h"
#include <memory>

class Simulation;
class MultiLayerItem;
class InstrumentItem;
class SimulationOptionsItem;

//! Contains functions to build the domain simulation from instrument and sample models.

namespace DomainSimulationBuilder
{

//! Creates domain simulation from sample and instrument items.

BA_CORE_API_ std::unique_ptr<Simulation>
createSimulation(const MultiLayerItem* sampleItem, const InstrumentItem* instrumentItem,
                 const SimulationOptionsItem* optionsItem = nullptr);
}; // namespace DomainSimulationBuilder

#endif // BORNAGAIN_GUI_COREGUI_MODELS_DOMAINSIMULATIONBUILDER_H
