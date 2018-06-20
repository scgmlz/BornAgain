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

#include "MaterialFactoryFuncs.h"
#include "MaterialBySLDImpl.h"
#include "RefractiveMaterialImpl.h"
#include "SlicedParticle.h"
#include "MaterialUtils.h"
#include "Units.h"
#include <functional>

namespace
{
const double inv_sq_angstroms = 1.0 / (Units::angstrom * Units::angstrom);
template <class T>
T averageData(const Material& layer_mat, const std::vector<HomogeneousRegion>& regions,
              std::function<T(const Material&)> average);
}

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
    std::unique_ptr<MaterialBySLDImpl> mat_impl(new MaterialBySLDImpl(
        name, sld_real * inv_sq_angstroms, sld_imag * inv_sq_angstroms, magnetization));
    return Material(std::move(mat_impl));
}

Material CreateAveragedMaterial(const Material& layer_mat,
                                const std::vector<HomogeneousRegion>& regions)
{
    // determine the type of returned material
    std::vector<const Material*> materials(regions.size() + 1);
    materials[0] = &layer_mat;
    for (size_t i = 0, regions_size = regions.size(); i < regions_size; ++i)
        materials[i + 1] = &regions[i].m_material;
    const MATERIAL_TYPES avr_material_type = MaterialUtils::checkMaterialTypes(materials);
    if (avr_material_type == MATERIAL_TYPES::InvalidMaterialType)
        throw std::runtime_error("Error in createAveragedMaterial(): non-default materials of "
                                 "different types used simultaneously.");

    // create the name of returned material
    const std::string avr_mat_name = layer_mat.getName() + "_avg";

    // calculate averaged magnetization
    const kvector_t mag_avr =
            averageData<kvector_t>(layer_mat, regions,
                                   [](const Material& mat) { return mat.magnetization(); });

    if (avr_material_type == MATERIAL_TYPES::RefractiveMaterial) {
        // avrData returns (1 - mdc)^2 - 1, where mdc is material data conjugate
        auto avrData = [](const Material& mat) -> complex_t {
            const complex_t mdc = std::conj(mat.materialData());
            return mdc * mdc - 2.0 * mdc;
        };
        const complex_t avr_mat_data
            = std::conj(1.0 - std::sqrt(1.0 + averageData<complex_t>(layer_mat, regions, avrData)));
        return HomogeneousMaterial(avr_mat_name, avr_mat_data.real(), avr_mat_data.imag(), mag_avr);
    } else if (avr_material_type == MATERIAL_TYPES::MaterialBySLD) {
        complex_t (*avrData)(const Material&)
            = [](const Material& mat) { return mat.materialData(); };
        const complex_t avr_mat_data = averageData<complex_t>(layer_mat, regions, avrData);
        return MaterialBySLD(avr_mat_name, avr_mat_data.real(), avr_mat_data.imag(),
                                          mag_avr);
    } else
        throw std::runtime_error("Error in CalculateAverageMaterial: unknown material type.");
}

namespace
{
template <class T>
T averageData(const Material& layer_mat, const std::vector<HomogeneousRegion>& regions,
              std::function<T(const Material&)> average)
{
    const T layer_data = average(layer_mat);
    T averaged_data = layer_data;
    for (auto& region : regions)
        averaged_data += region.m_volume * (average(region.m_material) - layer_data);
    return averaged_data;
}
}
