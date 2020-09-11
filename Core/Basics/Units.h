// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/Units.h
//! @brief     Defines some unit conversion factors and other constants in namespace Units.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_BASICS_UNITS_H
#define BORNAGAIN_CORE_BASICS_UNITS_H

//! Constants and functions for physical unit conversions.

namespace Units
{

// Length
static constexpr double nanometer = 1.;
static constexpr double angstrom = 1.e-1 * nanometer;
static constexpr double micrometer = 1.e+3 * nanometer;
static constexpr double millimeter = 1.e+6 * nanometer;
static constexpr double meter = 1.e+9 * nanometer;

// Symbols for length
static constexpr double nm = nanometer;

// Area (cross-section)
static constexpr double nm2 = nanometer * nanometer;
static constexpr double barn = nanometer * nanometer * 1e-10;

// Angle
static constexpr double radian = 1.;
static constexpr double milliradian = 1.e-3 * radian;
static constexpr double degree = (3.1415926535897932 / 180.0) * radian;
static constexpr double steradian = 1.;

inline double rad2deg(double angle)
{
    return angle / degree;
}
inline double deg2rad(double angle)
{
    return angle * degree;
}

// Symbols for (solid) angle
static constexpr double rad = radian;
static constexpr double mrad = milliradian;
static constexpr double sr = steradian;
static constexpr double deg = degree;

// Magnetic field
static constexpr double tesla = 1.;
static constexpr double gauss = 1e-4;

} // namespace Units

#endif // BORNAGAIN_CORE_BASICS_UNITS_H
