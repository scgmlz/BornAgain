// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/PhysicalConstants.h
//! @brief     Defines the values of physical constants (SI)
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PHYSICALCONSTANTS_H_
#define PHYSICALCONSTANTS_H_

namespace PhysConsts {
constexpr double m_n = 1.674927471e-27; //!< Neutron mass, kg
constexpr double h_bar = 1.05457180e-34; //!< Reduced Plank constant, J s
constexpr double mu_N = 5.050783699e-27; //!< Nuclear magneton (\f$ \mu_N \f$), J/T
constexpr double mu_B = 9.274009994e-24; //!< Bohr magneton (\f$ \mu_B \f$), J/T
constexpr double r_e = 2.8179403227e-15; //!< Thomson scattering length (\f$ r_e \f$), m
constexpr double gamma_n = 1.91304272; //!< \f$\gamma\f$ factor for neutron magnetic moment,
                                             //!< \f$\mu_n = \gamma \cdot \mu_N\f$
constexpr double g_factor_n = -3.82608545; //!< neutron g-factor
}

#endif /* PHYSICALCONSTANTS_H_ */
