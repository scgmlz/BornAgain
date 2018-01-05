// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/Instrument.h
//! @brief     Defines class Instrument.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "IDetector.h"
#include "INode.h"
#include "Beam.h"
#include "SimulationElementsProvider.h"
#include <memory>

template<class T> class OutputData;
class Histogram2D;
class DetectorMask;
class IAxis;
class IDetector2D;
class IResolutionFunction2D;

//! Assembles beam, detector and their relative positions wrt the sample.
//! @ingroup simulation_internal

class BA_CORE_API_ Instrument : public INode
{
public:
    Instrument();
    Instrument(const Instrument& other);
    Instrument& operator=(const Instrument& other);

    virtual ~Instrument();

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    Beam& getBeam() { return m_beam; }
    const Beam& getBeam() const { return m_beam; }
    void setBeam(const Beam& beam);

    //! Sets the beam wavelength and incoming angles
    void setBeamParameters(double wavelength, double alpha_i, double phi_i);

    //! Sets the beam's intensity
    void setBeamIntensity(double intensity);

    //! Sets the beam's polarization according to the given Bloch vector
    void setBeamPolarization(const kvector_t bloch_vector);

    //! Returns the beam's intensity
    double getBeamIntensity() const;

    //! Returns the detector data
    const IDetector* getDetector() const;
    IDetector* getDetector();

    //! Returns 2D detector data if detector is truly 2D. Otherwise returns nullptr
    IDetector2D* detector2D();

    const DetectorMask* getDetectorMask() const;

    //! Returns a detector axis
    const IAxis& getDetectorAxis(size_t index) const;

    //! Returns the detector's dimension
    size_t getDetectorDimension() const;

    //! Sets the detector (axes can be overwritten later)
    void setDetector(const IDetector& detector);

    //! Sets detector resolution function
    void setDetectorResolutionFunction(const IResolutionFunction2D& p_resolution_function);

    //! Removes detector resolution function.
    void removeDetectorResolution();

    //! Sets the polarization analyzer characteristics of the detector
    void setAnalyzerProperties(const kvector_t direction, double efficiency,
                               double total_transmission);

    //! apply the detector resolution to the given intensity map
    void applyDetectorResolution(OutputData<double>* p_intensity_map) const;

#ifndef SWIG
    //! Returns new intensity map with detector resolution applied and axes in requested units
    template <class SimElement>
    std::unique_ptr<OutputData<double>>
    createDetectorIntensity(const std::vector<SimElement>& elements,
                            AxesUnits units = AxesUnits::DEFAULT) const
    {
        return mP_detector->createDetectorIntensity(elements, m_beam, units);
    }

    //! Returns histogram representing intensity map in requested axes units
    template<class SimElement>
    Histogram2D* createIntensityData(const std::vector<SimElement>& elements,
                                     AxesUnits units_type = AxesUnits::DEFAULT) const
    {
        auto data = createDetectorIntensity(elements, units_type);
        return createUnitSpecificHistogram(std::move(data), units_type).release();
    }

    //! Create a vector of SimulationElement objects according to the beam, detector and its mask
    template <class SimElement> std::vector<SimElement> createSimulationElements()
    {
        using ElementProvider = SimulationElementsProvider<SimElement>;
        auto agent_base = mP_detector->createSimulationElements(m_beam);
        auto agent = dynamic_cast<ElementProvider*>(agent_base.get());
        if (!agent)
            throw std::runtime_error("Error in Instrument::createSimulationElements: Incorrect detector or element type");
        return agent->releaseSimElements();
    }

    //! Returns empty detector map in given axes units.
    OutputData<double>* createDetectorMap(AxesUnits units = AxesUnits::DEFAULT) const;
#endif

    //! init detector with beam settings
    void initDetector();

    std::vector<const INode*> getChildren() const;

private:
    //! Creates 2D Histogram in specified units from OutputData array
    std::unique_ptr<Histogram2D>
    createUnitSpecificHistogram(std::unique_ptr<OutputData<double>> output_data, AxesUnits units) const;

    std::unique_ptr<IDetector> mP_detector;
    Beam m_beam;
};

#endif // INSTRUMENT_H
