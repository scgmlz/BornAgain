// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IDetector.h
//! @brief     Defines common detector interface.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IDETECTOR_H_
#define IDETECTOR_H_

#include "IAxis.h"
#include "ICloneable.h"
#include "INode.h"
#include "DetectionProperties.h"
#include "OutputData.h"
#include "SafePointerVector.h"
#include "SimulationArea.h"

class Beam;
class DetectorMask;
class IDetectorResolution;
class IResolutionFunction2D;
class ISimulationElementsProvider;
class RegionOfInterest;

//! Wrapper for detector axes units, required for a better representation of
//! detector axes units in python
//! @ingroup simulation

// workaround for SWIG (instead of just writing enum class AxesUnits...)
struct BA_CORE_API_ AxesUnitsWrap {
    enum AxesUnits { DEFAULT, NBINS, RADIANS, DEGREES, MM, QYQZ };
};
typedef AxesUnitsWrap::AxesUnits AxesUnits;

//! Abstract detector interface.
//! @ingroup simulation

class BA_CORE_API_ IDetector :  public ICloneable, public INode
{
public:
    IDetector();

    virtual IDetector* clone() const override = 0;

    virtual ~IDetector();

    //! Inits detector with the beam settings
    virtual void init(const Beam&) {}

    void clear() {m_axes.clear();}

    void addAxis(const IAxis& axis);

    const IAxis& getAxis(size_t index) const;

    //! Returns actual dimensionality of the detector (number of defined axes)
    size_t dimension() const {return m_axes.size();}

    //! Calculate axis index for given global index
    size_t axisBinIndex(size_t index, size_t selected_axis) const;

    //! Returns total number of pixels
    size_t totalSize() const;

    //! Returns detector masks container
    virtual const DetectorMask* detectorMask() const = 0;

    //! Sets the polarization analyzer characteristics of the detector
    void setAnalyzerProperties(const kvector_t direction, double efficiency,
                               double total_transmission);

    //! Sets the detector resolution
    void setDetectorResolution(const IDetectorResolution& p_detector_resolution);
    void setResolutionFunction(const IResolutionFunction2D& resFunc);

    //! Applies the detector resolution to the given intensity maps
    void applyDetectorResolution(OutputData<double>* p_intensity_map) const;

    //! Removes detector resolution function.
    void removeDetectorResolution();

    //! Returns a pointer to detector resolution object
    const IDetectorResolution* detectorResolution() const;

#ifndef SWIG
    //! Returns empty detector map in given axes units.
    std::unique_ptr<OutputData<double>> createDetectorMap(const Beam& beam, AxesUnits units) const;

    //! Create a vector of SimulationElement objects according to the detector and its mask
    virtual std::unique_ptr<ISimulationElementsProvider> createSimulationElements(const Beam& beam) = 0;

    //! Returns new intensity map with detector resolution applied and axes in requested units
    template <class SimElement>
    std::unique_ptr<OutputData<double>>
    createDetectorIntensity(const std::vector<SimElement>& elements, const Beam& beam,
                            AxesUnits units_type = AxesUnits::DEFAULT) const
    {
        auto detectorMap = createDetectorMap(beam, units_type);

        if (mP_detector_resolution) {
            if (units_type != AxesUnits::DEFAULT) {
                auto defaultMap = createDetectorMap(beam, AxesUnits::DEFAULT);
                setDataToDetectorMap(*defaultMap, elements);
                applyDetectorResolution(defaultMap.get());
                detectorMap->setRawDataVector(defaultMap->getRawDataVector());
            } else {
                setDataToDetectorMap(*detectorMap, elements);
                applyDetectorResolution(detectorMap.get());
            }
        } else {
            setDataToDetectorMap(*detectorMap, elements);
        }

        return detectorMap;
    }
#endif // SWIG

    //! Returns region of  interest if exists.
    virtual const RegionOfInterest* regionOfInterest() const = 0;

    //! Resets region of interest making whole detector plane available for the simulation.
    virtual void resetRegionOfInterest() = 0;

    //! Returns detection properties
    const DetectionProperties& detectionProperties() const {return m_detection_properties;}

    //! Inits axes of OutputData to match the detector and sets values to zero.
    void initOutputData(OutputData<double>& data) const;

    //! Return default axes units
    virtual AxesUnits defaultAxesUnits() const {return AxesUnits::DEFAULT;}

    //! Returns vector of valid axes units
    virtual std::vector<AxesUnits> validAxesUnits() const {return {AxesUnits::NBINS};}

    //! Returns number of simulation elements.
    size_t numberOfSimulationElements() const;

    virtual std::vector<const INode*> getChildren() const override;

protected:
    IDetector(const IDetector& other);

    //! Returns the name for the axis with given index
    virtual std::string axisName(size_t index) const = 0;

    //! Calculates axis range from original detector axes in given units (mm, rad, etc)
    virtual void calculateAxisRange(size_t axis_index, const Beam& beam, AxesUnits units,
                                    double& amin, double& amax) const;

    //! Constructs axis with min, max corresponding to selected units
    std::unique_ptr<IAxis> translateAxisToUnits(size_t axis_index, const Beam& beam,
                                                 AxesUnits units) const;

    //! Generates an axis with correct name and default binning for given index
    virtual std::unique_ptr<IAxis> createAxis(size_t index, size_t n_bins, double min,
                                              double max) const;

private:
    //! Checks if given unit is valid for the detector. Throws exception if it is not the case.
    void checkAxesUnits(AxesUnits units) const;

    template <class SimElement>
    void setDataToDetectorMap(OutputData<double>& detectorMap,
                              const std::vector<SimElement>& elements) const
    {
        if (elements.empty())
            return;
        SimulationArea area(this);
        for (SimulationArea::iterator it = area.begin(); it != area.end(); ++it)
            detectorMap[it.roiIndex()] = elements[it.elementIndex()].getIntensity();
    }

    SafePointerVector<IAxis> m_axes;
    DetectionProperties m_detection_properties;
    std::unique_ptr<IDetectorResolution> mP_detector_resolution;
};

#endif /* IDETECTOR_H_ */
