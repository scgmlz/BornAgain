// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/IsGISAXSDetector.cpp
//! @brief     Implements class IsGISAXSDetector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Detector/IsGISAXSDetector.h"
#include "Core/Binning/CustomBinAxis.h"

IsGISAXSDetector::IsGISAXSDetector()
{
    setName("IsGISAXSDetector");
}

IsGISAXSDetector::IsGISAXSDetector(size_t n_phi, double phi_min, double phi_max, size_t n_alpha,
                                   double alpha_min, double alpha_max)
{
    setName("IsGISAXSDetector");
    setDetectorParameters(n_phi, phi_min, phi_max, n_alpha, alpha_min, alpha_max);
}

IsGISAXSDetector::IsGISAXSDetector(const IsGISAXSDetector& other) : SphericalDetector(other)
{
    setName("IsGISAXSDetector");
}

IsGISAXSDetector* IsGISAXSDetector::clone() const
{
    return new IsGISAXSDetector(*this);
}

std::unique_ptr<IAxis> IsGISAXSDetector::createAxis(size_t index, size_t n_bins, double min,
                                                    double max) const
{
    if (max <= min) {
        throw Exceptions::LogicErrorException(
            "IsGISAXSDetector::createAxis() -> Error! max <= min");
    }
    if (n_bins == 0) {
        throw Exceptions::LogicErrorException(
            "IsGISAXSDetector::createAxis() -> Error! Number n_bins can't be zero.");
    }
    return std::make_unique<CustomBinAxis>(axisName(index), n_bins, min, max);
}

size_t IsGISAXSDetector::indexOfSpecular(const Beam& /*beam*/) const
{
    return totalSize();
}
