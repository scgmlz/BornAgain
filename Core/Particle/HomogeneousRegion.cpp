// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/HomogeneousRegion.cpp
//! @brief     Implements fct createAveragedMaterial
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Particle/HomogeneousRegion.h"
#include "Core/Basics/Units.h"
#include "Core/Material/MaterialBySLDImpl.h"
#include "Core/Material/MaterialUtils.h"
#include "Core/Material/RefractiveMaterialImpl.h"
#include <functional>

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

} // namespace

Material createAveragedMaterial(const Material& layer_mat,
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
    const kvector_t mag_avr = averageData<kvector_t>(
        layer_mat, regions, [](const Material& mat) { return mat.magnetization(); });

    if (avr_material_type == MATERIAL_TYPES::RefractiveMaterial) {
        // avrData returns (1 - mdc)^2 - 1, where mdc is material data conjugate
        auto avrData = [](const Material& mat) -> complex_t {
            const complex_t mdc = std::conj(mat.materialData());
            return mdc * mdc - 2.0 * mdc;
        };
        const complex_t avr_mat_data =
            std::conj(1.0 - std::sqrt(1.0 + averageData<complex_t>(layer_mat, regions, avrData)));
        return HomogeneousMaterial(avr_mat_name, avr_mat_data.real(), avr_mat_data.imag(), mag_avr);
    } else if (avr_material_type == MATERIAL_TYPES::MaterialBySLD) {
        complex_t (*avrData)(const Material&) = [](const Material& mat) {
            return mat.materialData();
        };
        const complex_t avr_mat_data = averageData<complex_t>(layer_mat, regions, avrData);
        return MaterialBySLD(avr_mat_name, avr_mat_data.real(), avr_mat_data.imag(), mag_avr);
    } else
        throw std::runtime_error("Error in CalculateAverageMaterial: unknown material type.");
}
