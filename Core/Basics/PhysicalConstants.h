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

#ifndef BORNAGAIN_CORE_BASICS_PHYSICALCONSTANTS_H
#define BORNAGAIN_CORE_BASICS_PHYSICALCONSTANTS_H

namespace PhysConsts
{
constexpr double m_n = 1.67492749804e-27;  //!< Neutron mass, kg
constexpr double h_bar = 1.054571817e-34;  //!< Reduced Plank constant, J s
constexpr double mu_N = 5.0507837461e-27;  //!< Nuclear magneton (\f$ \mu_N \f$), J/T
constexpr double mu_B = 9.2740100783e-24;  //!< Bohr magneton (\f$ \mu_B \f$), J/T
constexpr double r_e = 2.8179403262e-15;   //!< Thomson scattering length (\f$ r_e \f$), m
constexpr double gamma_n = 1.91304272;     //!< \f$\gamma\f$ factor for neutron magnetic moment,
                                           //!< \f$\mu_n = \gamma \cdot \mu_N\f$
constexpr double g_factor_n = -3.82608545; //!< neutron g-factor
} // namespace PhysConsts

#endif // BORNAGAIN_CORE_BASICS_PHYSICALCONSTANTS_H
