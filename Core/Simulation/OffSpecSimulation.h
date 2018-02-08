// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/OffSpecSimulation.h
//! @brief     Defines class OffSpecSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef OFFSPECSIMULATION_H
#define OFFSPECSIMULATION_H

#include "Simulation2D.h"
#include "SimulationElement.h"

class Histogram2D;

//! Main class to run an off-specular simulation.
//! @ingroup simulation

class BA_CORE_API_ OffSpecSimulation : public Simulation2D
{
public:
    OffSpecSimulation();
    OffSpecSimulation(const MultiLayer& p_sample);
    OffSpecSimulation(const std::shared_ptr<class IMultiLayerBuilder> p_sample_builder);

    ~OffSpecSimulation() final {}

    OffSpecSimulation* clone() const override { return new OffSpecSimulation(*this); }

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    //! Put into a clean state for running a simulation
    void prepareSimulation() final;

    //! Gets the number of elements this simulation needs to calculate
    size_t numberOfSimulationElements() const final;

    //! Returns the results of the simulation in a format that supports unit conversion and export
    //! to numpy arrays
    SimulationResult result() const override;

    //! Sets beam parameters from here (forwarded to Instrument)
    void setBeamParameters(double wavelength, const IAxis& alpha_axis, double phi_i);

    //! Returns axis of the beam.
    const IAxis* beamAxis() const;

private:
    OffSpecSimulation(const OffSpecSimulation& other);

    //! Initializes the vector of Simulation elements
    void initSimulationElementVector() override;

    //! Creates the appropriate data structure (e.g. 2D intensity map) from the calculated
    //! SimulationElement objects
    void transferResultsToIntensityMap() final;

    //! Default implementation only adds the detector axes
    void updateIntensityMap() override final;

    //! Normalize, apply detector resolution and transfer detector image corresponding to
    //! alpha_i = mp_alpha_i_axis->getBin(index)
    void transferDetectorImage(size_t index);

    //! Check correct number of axes
    void checkInitialization() const;

    void initialize();

    std::unique_ptr<IAxis> mP_alpha_i_axis;
    OutputData<double> m_intensity_map;
};

#endif // OFFSPECSIMULATION_H
