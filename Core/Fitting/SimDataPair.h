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

#ifndef BORNAGAIN_CORE_FITTING_SIMDATAPAIR_H
#define BORNAGAIN_CORE_FITTING_SIMDATAPAIR_H

#include "Core/Fitting/FitTypes.h"
#include "Core/Instrument/SimulationResult.h"

template <class T> class OutputData;

//! Holds pair of simulation/experimental data to fit.

class BA_CORE_API_ SimDataPair
{
public:
    //! Constructs simulation/data pair for later fit.
    //! @param simulation: simulation builder capable of producing simulations
    //! @param data: experimental data
    //! @param uncertainties: uncertainties associated with experimental data
    //! @param user_weight: weight of dataset in objective metric computations
    SimDataPair(simulation_builder_t builder, const OutputData<double>& data,
                std::unique_ptr<OutputData<double>> uncertainties, double user_weight = 1.0);

    //! Constructs simulation/data pair for later fit.
    //! @param simulation: simulation builder capable of producing simulations
    //! @param data: experimental data
    //! @param uncertainties: uncertainties associated with experimental data
    //! @param user_weights: user weights associated with experimental data
    SimDataPair(simulation_builder_t builder, const OutputData<double>& data,
                std::unique_ptr<OutputData<double>> uncertainties,
                std::unique_ptr<OutputData<double>> user_weights);

    SimDataPair(SimDataPair&& other);

    ~SimDataPair();

    void runSimulation(const Fit::Parameters& params);

    bool containsUncertainties() const;

    //! Returns the number of elements in the fit area
    size_t numberOfFitElements() const;

    //! Returns the result of last computed simulation
    SimulationResult simulationResult() const;

    //! Returns the experimental data cut to the ROI area
    SimulationResult experimentalData() const;

    //! Returns the data uncertainties cut to the ROI area
    //! If no uncertainties present, returns zero-filled
    //! SimulationResult.
    SimulationResult uncertainties() const;

    //! Returns the user uncertainties cut to the ROI area.
    SimulationResult userWeights() const;

    //! Returns the relative difference between simulated
    //! and expeimental data cut to the ROI area
    SimulationResult relativeDifference() const;

    //! Returns the absolute difference between simulated
    //! and expeimental data cut to the ROI area
    SimulationResult absoluteDifference() const;

    //! Returns the flattened simulated intensities
    //! cut to the ROI area
    std::vector<double> simulation_array() const;

    //! Returns the flattened experimental data
    //! cut to the ROI area
    std::vector<double> experimental_array() const;

    //! Returns the flattened experimental uncertainties
    //! cut to the ROI area. If no uncertainties are
    //! available, returns a zero-filled array
    //! sized to the ROI area.
    std::vector<double> uncertainties_array() const;

    //! Returns a flat array of user weights
    //! cut to the ROI area.
    std::vector<double> user_weights_array() const;

private:
    void initResultArrays();
    void validate() const;

    //! Simulation builder from the user to construct simulation for given set of parameters.
    simulation_builder_t m_simulation_builder;

    //! Current simulation for given set of parameters.
    std::unique_ptr<Simulation> m_simulation;

    //! Current simulation results. Masked areas are nullified.
    SimulationResult m_sim_data;
    //! Experimental data cut to the ROI. Masked areas are nullified.
    SimulationResult m_exp_data;
    //! Weights from experimental data uncertainties. Masked areas are nullified.
    SimulationResult m_uncertainties;
    //! Manually defined (user) weights. Masked areas are nullified.
    SimulationResult m_user_weights;

    //! Raw experimental data as obtained from the user.
    std::unique_ptr<OutputData<double>> m_raw_data;
    //! Data uncertainties as provided by the user
    std::unique_ptr<OutputData<double>> m_raw_uncertainties;
    //! User-defined weights
    std::unique_ptr<OutputData<double>> m_raw_user_weights;
};

#endif // BORNAGAIN_CORE_FITTING_SIMDATAPAIR_H
