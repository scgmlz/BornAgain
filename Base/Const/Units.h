//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Const/Units.h
//! @brief     Defines some unit conversion factors and other constants in namespace Units.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_BASE_CONST_UNITS_H
#define BORNAGAIN_BASE_CONST_UNITS_H

//! Constants and functions for physical unit conversions.
//!
//! In user code, quantities that have a physical dimension should always
//! be given in the form _value * unit_, e.g. 0.529 * angstrom for a length,
//! or 45 * deg for an angle.
//!
//! Internally, BornAgain has length, angle, magnetic field units of nanometer,
//! radians, Tesla. Therefore, in principle, the multipliers nm, rad, tesla could
//! be ommited from code. However, to make code more readable, and to prevent
//! misunderstandings, we recommend that physical dimension be always made clear
//! by multiplying values with an appropriate constant, even if this expands to 1.

namespace Units {

// Length
static constexpr double nanometer = 1.; //!< Internal unit for lengths
static constexpr double angstrom = 1.e-1 * nanometer;
static constexpr double micrometer = 1.e+3 * nanometer;
static constexpr double millimeter = 1.e+6 * nanometer;

// Symbols for length
static constexpr double nm = nanometer;

// Area (cross-section)
static constexpr double nm2 = nanometer * nanometer;

// Angle
static constexpr double rad = 1.; //!< Radian, internal unit for angles
static constexpr double deg = (3.1415926535897932 / 180.0) * rad;

// Magnetic field
static constexpr double tesla = 1.; //!< Internal unit for magnetic fields
static constexpr double gauss = 1e-4;

// Converters

#ifndef SWIG
inline double rad2deg(double angle) {
    return angle / deg;
}
inline double deg2rad(double angle) {
    return angle * deg;
}
#endif // USER_API

} // namespace Units

#endif // BORNAGAIN_BASE_CONST_UNITS_H
