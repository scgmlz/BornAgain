#ifndef DEPTHPROBESIMULATION_H
#define DEPTHPROBESIMULATION_H

#include "Simulation.h"
#include "DepthProbeElement.h"
#include "ILayerRTCoefficients.h"
#include "OutputData.h"

class IAxis;
class IComputation;
class IFootprintFactor;
class ISample;
class IMultiLayerBuilder;
class MultiLayer;
class Histogram1D;

class BA_CORE_API_ DepthProbeSimulation : public Simulation
{
public:
    DepthProbeSimulation();
    DepthProbeSimulation(const MultiLayer& sample);
    DepthProbeSimulation(const std::shared_ptr<IMultiLayerBuilder> sample_builder);
    virtual ~DepthProbeSimulation();

    DepthProbeSimulation* clone() const override;

    void accept(INodeVisitor* visitor) const override final {visitor->visit(this);}

    size_t numberOfSimulationElements() const override;

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

private:
    DepthProbeSimulation(const DepthProbeSimulation& other);

    //! Sets beam parameters with alpha_i of the beam defined in the range.
    void setBeamParameters(double lambda, const IAxis& alpha_axis,
                           const IFootprintFactor* beam_shape);

    //! Initializes the vector of Simulation elements
    void initSimulationElementVector() override;

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

    //! Normalize the detector counts to beam intensity, to solid angle, and to exposure angle
    //! for single simulation element specified by _index_.
    void normalizeIntensity(size_t index, double beam_intensity) override;

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

#endif // DEPTHPROBESIMULATION_H
