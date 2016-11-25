// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/OffSpecSimulation.h
//! @brief     Defines class OffSpecSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OFFSPECSIMULATION_H
#define OFFSPECSIMULATION_H

#include "Simulation.h"

class Histogram2D;

//! Main class to run an off-specular simulation.
//! @ingroup simulation

class BA_CORE_API_ OffSpecSimulation : public Simulation
{
public:
    OffSpecSimulation();
    OffSpecSimulation(const MultiLayer& p_sample);
    OffSpecSimulation(const std::shared_ptr<class IMultiLayerBuilder> p_sample_builder);
    ~OffSpecSimulation() final {}

    OffSpecSimulation* clone() const { return new OffSpecSimulation(*this); }

    //! Put into a clean state for running a simulation
    void prepareSimulation() final;

    //! Gets the number of elements this simulation needs to calculate
    int numberOfSimulationElements() const final;

    //! Returns clone of the detector intensity map
    OutputData<double>*
    getDetectorIntensity(IDetector2D::EAxesUnits units_type = IDetector2D::DEFAULT) const
    {
        (void)units_type;
        return m_intensity_map.clone();
    }

    //! Returns clone of the detector intensity map in the form of 2D histogram.
    Histogram2D* getIntensityData() const;

    //! Sets beam parameters from here (forwarded to Instrument)
    void setBeamParameters(double lambda, const IAxis& alpha_axis, double phi_i);

    //! Sets detector parameters using angle ranges
    void setDetectorParameters(
        size_t n_x, double x_min, double x_max, size_t n_y, double y_min, double y_max);

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    std::string addParametersToExternalPool(
        const std::string& path, ParameterPool* external_pool, int copy_number = -1) const final;

private:
    OffSpecSimulation(const OffSpecSimulation& other);

    //! Initializes the vector of Simulation elements
    void initSimulationElementVector() final;

    //! Creates the appropriate data structure (e.g. 2D intensity map) from the calculated
    //! SimulationElement objects
    void transferResultsToIntensityMap() final;

    //! Default implementation only adds the detector axes
    void updateIntensityMap() final;

    //! Normalize, apply detector resolution and transfer detector image corresponding to
    //! alpha_i = mp_alpha_i_axis->getBin(index)
    void transferDetectorImage(int index);

    //! Check correct number of axes
    void checkInitialization() const;

    void initialize();

    IAxis* mp_alpha_i_axis;
};

#endif // OFFSPECSIMULATION_H
