// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SimulationElementsProvider.h
//! @brief     Implements class SimulationElementsProvider.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SIMULATIONELEMENTSPROVIDER_H_
#define SIMULATIONELEMENTSPROVIDER_H_

#include <vector>

//! Base for SimulationElementsProvider.
class ISimulationElementsProvider
{
public:
    virtual ~ISimulationElementsProvider() = default;
};

//! SimulationElementsProvider template, gives access to created simulation elements
//! Intended to be used in detectors for access to simulation elements of different types
template <class SimElement> class SimulationElementsProvider : public ISimulationElementsProvider
{
public:
    std::vector<SimElement>& getElementVector()
    {
        return m_elements;
    }
    std::vector<SimElement> releaseSimElements()
    {
        return std::move(m_elements);
    }

private:
    std::vector<SimElement> m_elements;
};

#endif /* SIMULATIONELEMENTSPROVIDER_H_ */
