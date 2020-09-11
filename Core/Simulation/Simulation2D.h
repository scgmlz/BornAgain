// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/Simulation2D.h
//! @brief     Defines class Simulation2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SIMULATION_SIMULATION2D_H
#define BORNAGAIN_CORE_SIMULATION_SIMULATION2D_H

#include "Core/Instrument/SimulationResult.h"
#include "Core/Simulation/Simulation.h"

class DetectorContext;

//! Pure virtual base class of OffSpecularSimulation and GISASSimulation.
//! Holds the common implementations for simulations with a 2D detector
//! @ingroup simulation

class BA_CORE_API_ Simulation2D : public Simulation
{
public:
    Simulation2D();
    Simulation2D(const MultiLayer& p_sample);
    Simulation2D(const std::shared_ptr<IMultiLayerBuilder> p_sample_builder);
    ~Simulation2D() override;

    Simulation2D* clone() const override = 0;

    //! Put into a clean state for running a simulation
    void prepareSimulation() override;

    //! Sets spherical detector parameters using angle ranges
    //! @param n_phi number of phi-axis bins
    //! @param phi_min low edge of first phi-bin
    //! @param phi_max upper edge of last phi-bin
    //! @param n_alpha number of alpha-axis bins
    //! @param alpha_min low edge of first alpha-bin
    //! @param alpha_max upper edge of last alpha-bin
    void setDetectorParameters(size_t n_phi, double phi_min, double phi_max, size_t n_alpha,
                               double alpha_min, double alpha_max);

    //! Sets the detector (axes can be overwritten later)
    void setDetector(const IDetector2D& detector);

    //! removes all masks from the detector
    void removeMasks();

    //! Adds mask of given shape to the stack of detector masks. The mask value 'true' means
    //! that the channel will be excluded from the simulation. The mask which is added last
    //! has priority.
    //! @param shape The shape of mask (Rectangle, Polygon, Line, Ellipse)
    //! @param mask_value The value of mask
    void addMask(const IShape2D& shape, bool mask_value = true);

    //! Put the mask for all detector channels (i.e. exclude whole detector from the analysis)
    void maskAll();

    //! Sets rectangular region of interest with lower left and upper right corners defined.
    void setRegionOfInterest(double xlow, double ylow, double xup, double yup);

protected:
    Simulation2D(const Simulation2D& other);

    virtual void initUnitConverter() {}

    //! Gets the number of elements this simulation needs to calculate
    size_t numberOfSimulationElements() const override;

    //! Generate a single threaded computation for a given range of simulation elements
    //! @param start Index of the first element to include into computation
    //! @param n_elements Number of elements to process
    std::unique_ptr<IComputation> generateSingleThreadedComputation(size_t start,
                                                                    size_t n_elements) override;

    //! Generate simulation elements for given beam
    std::vector<SimulationElement> generateSimulationElements(const Beam& beam);

    //! Normalize the detector counts to beam intensity, to solid angle, and to exposure angle.
    //! @param start_ind Index of the first element to operate on
    //! @param n_elements Number of elements to process
    void normalize(size_t start_ind, size_t n_elements) override;

    void addBackGroundIntensity(size_t start_ind, size_t n_elements) override;

    void addDataToCache(double weight) override;

    void moveDataFromCache() override;

    std::vector<SimulationElement> m_sim_elements;
    std::vector<double> m_cache;
    std::unique_ptr<DetectorContext> detector_context;

private:
    std::vector<double> rawResults() const override;
    void setRawResults(const std::vector<double>& raw_data) override;
};

#endif // BORNAGAIN_CORE_SIMULATION_SIMULATION2D_H
