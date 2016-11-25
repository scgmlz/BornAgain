// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IsGISAXSDetector.cpp
//! @brief     Implements class IsGISAXSDetector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IsGISAXSDetector.h"
#include "BornAgainNamespace.h"
#include "CustomBinAxis.h"


IsGISAXSDetector::IsGISAXSDetector()
{
    setName(BornAgain::IsGISAXSDetectorType);
    init_parameters();
}

IsGISAXSDetector::IsGISAXSDetector(
    size_t n_phi, double phi_min, double phi_max, size_t n_alpha, double alpha_min,
    double alpha_max)
{
    setName(BornAgain::IsGISAXSDetectorType);
    init_parameters();
    setDetectorParameters(n_phi, phi_min, phi_max, n_alpha, alpha_min, alpha_max);
}

IsGISAXSDetector::IsGISAXSDetector(const IsGISAXSDetector& other) : SphericalDetector(other)
{
    setName(BornAgain::IsGISAXSDetectorType);
    init_parameters();
}

IsGISAXSDetector* IsGISAXSDetector::clone() const { return new IsGISAXSDetector(*this); }

void IsGISAXSDetector::print(std::ostream& ostr) const
{
    ostr << "IsGISAXSDetector: '" << getName() << "' " << getParameterPool();
    for (size_t i = 0; i < m_axes.size(); ++i) {
        ostr << "    IAxis:" << *m_axes[i] << std::endl;
    }
}

IAxis* IsGISAXSDetector::createAxis(size_t index, size_t n_bins, double min, double max) const
{
    if (max <= min) {
        throw Exceptions::LogicErrorException(
            "IsGISAXSDetector::createAxis() -> Error! max <= min");
    }
    if (n_bins == 0) {
        throw Exceptions::LogicErrorException(
            "IsGISAXSDetector::createAxis() -> Error! Number n_bins can't be zero.");
    }
    return new CustomBinAxis(getAxisName(index), n_bins, min, max);
}

size_t IsGISAXSDetector::getIndexOfSpecular(const Beam&) const { return getTotalSize(); }
