//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Axis/IAxis.cpp
//! @brief     Implements interface IAxis.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Base/Axis/IAxis.h"

bool IAxis::equals(const IAxis& other) const {
    return getName() == other.getName();
}

std::vector<double> IAxis::binCenters() const {
    throw std::runtime_error("IAxis::binCenters() -> Error. Not implemented.");
}

std::vector<double> IAxis::binBoundaries() const {
    throw std::runtime_error("IAxis::binBoundaries() -> Error. Not implemented.");
}

IAxis* IAxis::createClippedAxis(double /* left */, double /* right */) const {
    throw std::runtime_error("IAxis::createClippedAxis() -> Error. Not implemented.");
}

bool IAxis::contains(double value) const {
    return value >= lowerBound() && value < upperBound();
}

double IAxis::span() const {
    return upperBound() - lowerBound();
}

double IAxis::center() const {
    return (upperBound() + lowerBound()) / 2;
}
