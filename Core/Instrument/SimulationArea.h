// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SimulationArea.h
//! @brief     Defines class SimulationArea.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SIMULATIONAREA_H
#define SIMULATIONAREA_H

#include "WinDllMacros.h"
#include "SimulationAreaIterator.h"
class IDetector2D;

//! Holds iteration logic over active detector channels in the presence of masked areas
//! and RegionOfInterest defined.
//! @ingroup simulation

class BA_CORE_API_ SimulationArea
{
public:
    using iterator = SimulationAreaIterator;
    explicit SimulationArea(const IDetector2D *detector);
    virtual ~SimulationArea(){}

    SimulationAreaIterator begin();
    SimulationAreaIterator end();

    //! returns trus if given iterator index correspond to masked detector channel
    virtual bool isMasked(size_t index) const;

    size_t totalSize() const;

    //! Return index in ROI map from iterator index
    size_t roiIndex(size_t index) const;

    //! Return detector index from iterator index
    size_t detectorIndex(size_t index) const;

protected:
    const IDetector2D *m_detector;
    size_t m_max_index;
};

inline size_t SimulationArea::totalSize() const
{
    return m_max_index;
}


//! Holds iteration logic over active detector channels in the presence of ROI. On the contrary
//! to SimulationArea class, iterates also over masked areas.
//! @ingroup simulation

class BA_CORE_API_ SimulationRoiArea : public SimulationArea
{
public:
    explicit SimulationRoiArea(const IDetector2D *detector);

    virtual bool isMasked(size_t) const;

};

#endif // SIMULATIONAREA_H
