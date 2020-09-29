// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/DetectorContext.h
//! @brief     Define DetectorContext class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_DETECTOR_DETECTORCONTEXT_H
#define BORNAGAIN_CORE_DETECTOR_DETECTORCONTEXT_H

#include "Core/Binning/IPixel.h"
#include "Core/Vector/EigenCore.h"
#include <memory>
#include <vector>

class IDetector2D;

//! Holds precalculated information for faster SimulationElement generation.
//! @ingroup detector

class DetectorContext
{
public:
    DetectorContext(const IDetector2D* detector);

    DetectorContext(const DetectorContext& other) = delete;
    DetectorContext& operator=(const DetectorContext& other) = delete;

    size_t numberOfSimulationElements() const;

    std::unique_ptr<IPixel> createPixel(size_t element_index) const;

    size_t detectorIndex(size_t element_index) const;

private:
    void setup_context(const IDetector2D* detector);

    Eigen::Matrix2cd analyzer_operator;
    std::vector<std::unique_ptr<IPixel>> pixels; //! All unmasked pixels inside ROI.
    std::vector<size_t> active_indices; //! The sequence of detector bin indices (unmasked, in ROI)
};

#endif // BORNAGAIN_CORE_DETECTOR_DETECTORCONTEXT_H
