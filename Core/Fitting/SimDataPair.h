// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/SimDataPair.h
//! @brief     Defines class SimDataPair.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SIMDATAPAIR_H
#define SIMDATAPAIR_H

#include "ICloneable.h"
#include "FitTypes.h"
#include "OutputData.h"
#include "SimulationResult.h"

//! Holds pair of simulation/experimental data to fit.

class BA_CORE_API_ SimDataPair : public ICloneable
{
public:
    SimDataPair(simulation_builder_t builder, const OutputData<double>& data, double weight = 1.0);

    virtual ~SimDataPair() override;

    SimDataPair* clone() const override;

    size_t numberOfFitElements() const;

    double weight() const;

    SimulationResult simulationResult() const;

    SimulationResult experimentalData() const;

    void runSimulation(const Fit::Parameters& params);

    std::vector<double> experimental_array() const;

    std::vector<double> simulation_array() const;

private:
    void create_simulation(const Fit::Parameters& params);

    //!< Current simulation for given set of parameters.
    std::unique_ptr<Simulation> m_simulation;
    //!< Current simulation results.
    SimulationResult m_simulation_result;
    //!< Experimental data.
    SimulationResult m_experimental_data;

    //!< Simulated data in the form of flat array (masked areas excluded, ROI only).
    std::vector<double> m_simulation_array;
    //!< Experimental data in the form of flat array (masked areas excluded, ROI only).
    std::vector<double> m_experimental_array;

    //!< Simulation builder from the user to construct simulation for given set of parameters.
    simulation_builder_t m_simulation_builder;
    //!< Raw experimental data as obtained from the user.
    std::unique_ptr<OutputData<double>> m_data;
    //!< Weight of dataset in 'fitting multiple datasets' scenario.
    double m_weight;
    //!< Cached number of fit elements (unmasked detector chanels inside region of interest).
    size_t m_fit_elements_count;
};

#endif // SIMDATAPAIR_H

