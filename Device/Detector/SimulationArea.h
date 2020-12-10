//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Detector/SimulationArea.h
//! @brief     Defines class SimulationArea.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_DEVICE_DETECTOR_SIMULATIONAREA_H
#define BORNAGAIN_DEVICE_DETECTOR_SIMULATIONAREA_H

#include "Device/Detector/SimulationAreaIterator.h"

class IDetector;

//! Holds iteration logic over active detector channels in the presence of masked areas
//! and RegionOfInterest defined.
//! @ingroup detector

class SimulationArea {
public:
    using iterator = SimulationAreaIterator;
    explicit SimulationArea(const IDetector* detector);
    virtual ~SimulationArea() {}

    SimulationAreaIterator begin();
    SimulationAreaIterator end();

    //! returns true if given iterator index correspond to masked detector channel
    virtual bool isMasked(size_t index) const;

    size_t totalSize() const;

    //! Return index in ROI map from iterator index
    size_t roiIndex(size_t index) const;

    //! Return detector index from iterator index
    size_t detectorIndex(size_t index) const;

protected:
    const IDetector* m_detector;
    size_t m_max_index;
};

inline size_t SimulationArea::totalSize() const {
    return m_max_index;
}

//! Holds iteration logic over active detector channels in the presence of ROI. On the contrary
//! to SimulationArea class, iterates also over masked areas.
//! @ingroup detector

class SimulationRoiArea : public SimulationArea {
public:
    explicit SimulationRoiArea(const IDetector* detector);

    virtual bool isMasked(size_t) const;
};

#endif // BORNAGAIN_DEVICE_DETECTOR_SIMULATIONAREA_H
#endif // USER_API
