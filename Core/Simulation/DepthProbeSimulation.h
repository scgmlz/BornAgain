// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/DepthProbeSimulation.h
//! @brief     Defines class DepthProbeSimulation
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SIMULATION_DEPTHPROBESIMULATION_H
#define BORNAGAIN_CORE_SIMULATION_DEPTHPROBESIMULATION_H

#include "Core/Intensity/OutputData.h"
#include "Core/RT/ILayerRTCoefficients.h"
#include "Core/Simulation/Simulation.h"
#include "Core/SimulationElement/DepthProbeElement.h"

#include <vector>

class IAxis;
class IComputation;
class IFootprintFactor;
class ISample;
class IMultiLayerBuilder;
class MultiLayer;
class Histogram1D;
class IUnitConverter;

class BA_CORE_API_ DepthProbeSimulation : public Simulation
{
public:
    DepthProbeSimulation();
    DepthProbeSimulation(const MultiLayer& sample);
    DepthProbeSimulation(const std::shared_ptr<IMultiLayerBuilder> sample_builder);
    ~DepthProbeSimulation() override;

    DepthProbeSimulation* clone() const override;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    //! Returns the results of the simulation in a format that supports unit conversion and export
    //! to numpy arrays
    SimulationResult result() const override;

    //! Sets beam parameters with alpha_i of the beam defined in the range.
    void setBeamParameters(double lambda, int nbins, double alpha_i_min, double alpha_i_max,
                           const IFootprintFactor* beam_shape = nullptr);

    //! Set z positions for intensity calculations. Negative z's correspond to the area
    //! under sample surface. The more negative z is, the deeper layer corresponds to it.
    void setZSpan(size_t n_bins, double z_min, double z_max);

    //! Returns a pointer to incident angle axis.
    const IAxis* getAlphaAxis() const;

    //! Returns a pointer to z-position axis.
    const IAxis* getZAxis() const;

    //! Returns the total number of the intensity values in the simulation result
    size_t intensityMapSize() const override;

#ifndef SWIG
    std::unique_ptr<IUnitConverter> createUnitConverter() const;
#endif

private:
    DepthProbeSimulation(const DepthProbeSimulation& other);

    //! Sets beam parameters with alpha_i of the beam defined in the range.
    void setBeamParameters(double lambda, const IAxis& alpha_axis,
                           const IFootprintFactor* beam_shape);

    //! Initializes the vector of Simulation elements
    void initSimulationElementVector() override;

    //! Gets the number of elements this simulation needs to calculate
    size_t numberOfSimulationElements() const override;

    //! Generate simulation elements for given beam
    std::vector<DepthProbeElement> generateSimulationElements(const Beam& beam);

    //! Generate a single threaded computation for a given range of simulation elements
    //! @param start Index of the first element to include into computation
    //! @param n_elements Number of elements to process
    std::unique_ptr<IComputation> generateSingleThreadedComputation(size_t start,
                                                                    size_t n_elements) override;

    //! Checks if simulation data is ready for retrieval.
    void validityCheck() const;

    void checkCache() const;

    //! Checks the distribution validity for simulation.
    void validateParametrization(const ParameterDistribution& par_distr) const override;

    //! Initializes simulation
    void initialize();

    //! Normalize the detector counts to beam intensity, to solid angle, and to exposure angle.
    //! @param start_ind Index of the first element to operate on
    //! @param n_elements Number of elements to process
    void normalize(size_t start_ind, size_t n_elements) override;

    void addBackGroundIntensity(size_t start_ind, size_t n_elements) override;

    void addDataToCache(double weight) override;

    void moveDataFromCache() override;

    double incidentAngle(size_t index) const;

    //! Creates intensity data from simulation elements
    std::unique_ptr<OutputData<double>> createIntensityData() const;

    std::vector<double> rawResults() const override;
    void setRawResults(const std::vector<double>& raw_data) override;

    std::unique_ptr<IAxis> m_alpha_axis;
    std::unique_ptr<IAxis> m_z_axis;
    std::vector<DepthProbeElement> m_sim_elements;
    std::vector<std::valarray<double>> m_cache;
};

#endif // BORNAGAIN_CORE_SIMULATION_DEPTHPROBESIMULATION_H
