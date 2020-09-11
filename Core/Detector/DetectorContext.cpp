// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/DetectorContext.cpp
//! @brief     Implements DetectorContext class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Detector/DetectorContext.h"
#include "Core/Detector/IDetector2D.h"

DetectorContext::DetectorContext(const IDetector2D* detector)
{
    setup_context(detector);
}

size_t DetectorContext::numberOfSimulationElements() const
{
    return active_indices.size();
}

//! Creates pixel for given element index. Element index is sequetial index in a vector
//! of SimulationElements. Corresponds to sequence of detector bins inside ROI and outside
//! of masked areas.

std::unique_ptr<IPixel> DetectorContext::createPixel(size_t element_index) const
{
    return std::unique_ptr<IPixel>(pixels[element_index]->clone());
}

size_t DetectorContext::detectorIndex(size_t element_index) const
{
    return active_indices[element_index];
}

void DetectorContext::setup_context(const IDetector2D* detector)
{
    active_indices = detector->active_indices();
    analyzer_operator = detector->detectionProperties().analyzerOperator();
    pixels.reserve(active_indices.size());
    for (auto detector_index : active_indices)
        pixels.emplace_back(detector->createPixel(detector_index));
}
