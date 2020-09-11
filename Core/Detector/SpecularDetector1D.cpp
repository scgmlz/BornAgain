// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/SpecularDetector1D.cpp
//! @brief     Implements a detector for specular simulations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Detector/SpecularDetector1D.h"

SpecularDetector1D::SpecularDetector1D(const IAxis& axis)
{
    initialize();
    addAxis(axis);
}

SpecularDetector1D::SpecularDetector1D(const SpecularDetector1D& detector) : IDetector(detector)
{
    initialize();
}

SpecularDetector1D::~SpecularDetector1D() = default;

SpecularDetector1D* SpecularDetector1D::clone() const
{
    return new SpecularDetector1D(*this);
}

AxesUnits SpecularDetector1D::defaultAxesUnits() const
{
    return AxesUnits::RADIANS;
}

std::string SpecularDetector1D::axisName(size_t index) const
{
    if (index == 0) {
        return "u";
    } else
        throw std::runtime_error(
            "SpecularDetector1D::getAxisName(size_t index) -> Error! index > 0");
}

void SpecularDetector1D::initialize()
{
    setName("SpecularDetector1D");
}
