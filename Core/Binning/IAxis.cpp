// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Binning/IAxis.cpp
//! @brief     Implements class IAxis.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Binning/IAxis.h"
#include "Core/Basics/Exceptions.h"

bool IAxis::equals(const IAxis& other) const
{
    return getName() == other.getName();
}

std::vector<double> IAxis::getBinCenters() const
{
    throw Exceptions::NotImplementedException("IAxis::getBinCenters() -> Error. Not implemented.");
}

std::vector<double> IAxis::getBinBoundaries() const
{
    throw Exceptions::NotImplementedException(
        "IAxis::getBinBoundaries() -> Error. Not implemented.");
}

IAxis* IAxis::createClippedAxis(double /* left */, double /* right */) const
{
    throw Exceptions::NotImplementedException(
        "IAxis::createClippedAxis() -> Error. Not implemented.");
}

bool IAxis::contains(double value) const
{
    return value >= getMin() && value < getMax();
}
