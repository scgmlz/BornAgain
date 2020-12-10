//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Detector/DetectorUtils.cpp
//! @brief     Implements namespace DetectorUtils.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Device/Detector/DetectorUtils.h"
#include "Device/Detector/IDetector2D.h"

bool DetectorUtils::isQuadratic(const IDetector2D& det) {
    ASSERT(det.dimension() == 2);
    if (det.axis(0).size() != det.axis(1).size())
        return false;
    if (std::abs(det.axis(0).span() - det.axis(1).span())
        > 1e-12 * (det.axis(0).span() + det.axis(1).span()))
        return false;
    return true;
}
