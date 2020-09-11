// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/MaterialFactoryFuncs.cpp
//! @brief     Factory functions used to create material instances.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Basics/Units.h"
#include "Core/Material/MaterialBySLDImpl.h"
#include "Core/Material/MaterialUtils.h"
#include "Core/Material/RefractiveMaterialImpl.h"
#include <functional>

Material HomogeneousMaterial(const std::string& name, complex_t refractive_index,
                             kvector_t magnetization)
{
    const double delta = 1.0 - refractive_index.real();
    const double beta = refractive_index.imag();
    return HomogeneousMaterial(name, delta, beta, magnetization);
}

Material HomogeneousMaterial(const std::string& name, double delta, double beta,
                             kvector_t magnetization)
{
    std::unique_ptr<RefractiveMaterialImpl> mat_impl(
        new RefractiveMaterialImpl(name, delta, beta, magnetization));
    return Material(std::move(mat_impl));
}

Material HomogeneousMaterial()
{
    return HomogeneousMaterial("vacuum", 0.0, 0.0, kvector_t{});
}

Material MaterialBySLD()
{
    return MaterialBySLD("vacuum", 0.0, 0.0, kvector_t{});
}

Material MaterialBySLD(const std::string& name, double sld_real, double sld_imag,
                       kvector_t magnetization)
{
    constexpr double inv_sq_angstroms = 1.0 / (Units::angstrom * Units::angstrom);
    std::unique_ptr<MaterialBySLDImpl> mat_impl(new MaterialBySLDImpl(
        name, sld_real * inv_sq_angstroms, sld_imag * inv_sq_angstroms, magnetization));
    return Material(std::move(mat_impl));
}
