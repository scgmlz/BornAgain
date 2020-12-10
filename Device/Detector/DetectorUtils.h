//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Detector/DetectorUtils.h
//! @brief     Defines namespace DetectorUtils.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_DEVICE_DETECTOR_DETECTORUTILS_H
#define BORNAGAIN_DEVICE_DETECTOR_DETECTORUTILS_H

class IDetector2D;

namespace DetectorUtils {

bool isQuadratic(const IDetector2D& det);

} // namespace DetectorUtils

#endif // BORNAGAIN_DEVICE_DETECTOR_DETECTORUTILS_H
