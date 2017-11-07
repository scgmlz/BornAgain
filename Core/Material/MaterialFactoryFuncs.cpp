#include "MaterialFactoryFuncs.h"
#include "MaterialBySLDImpl.h"
#include "RefractiveMaterialImpl.h"
#include "SlicedParticle.h"

namespace {
MATERIAL_TYPES checkMaterialTypes(const Material& layer_mat,
                                  const std::vector<HomogeneousRegion>& regions);

template <class T>
T averageData(const Material& layer_mat, const std::vector<HomogeneousRegion>& regions, T (*func_ptr) (const Material&));
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

Material MaterialBySLD(const std::string& name, double sld, double abs_term,
                       kvector_t magnetization)
{
    std::unique_ptr<MaterialBySLDImpl> mat_impl(
        new MaterialBySLDImpl(name, sld, abs_term, magnetization));
    return Material(std::move(mat_impl));
}

constexpr double basic_wavelength = 0.1798197; // nm, wavelength of 2200 m/s neutrons
Material MaterialByAbsCX(const std::string& name, double sld, double abs_cx,
                         kvector_t magnetization)
{
    return MaterialBySLD(name, sld, abs_cx / basic_wavelength, magnetization);
}

Material MaterialBySLD()
{
    return MaterialBySLD("vacuum", 0.0, 0.0, kvector_t{});
}

Material createAveragedMaterial(const Material& layer_mat,
                                const std::vector<HomogeneousRegion>& regions)
{
    // determine the type of returned material
    const MATERIAL_TYPES avr_material_type = checkMaterialTypes(layer_mat, regions);

    // create the name of returned material
    const std::string avr_mat_name = layer_mat.getName() + "_avg";

    // calculate averaged magnetization
    kvector_t (*avrMag)(const Material&)
        = [](const Material& mat) { return mat.magnetization(); };
    const kvector_t mag_avr = averageData(layer_mat, regions, avrMag);

    if (avr_material_type == MATERIAL_TYPES::RefractiveMaterial) {
        // avrData returns (1 - mdc)^2 - 1, where mdc is material data conjugate
        complex_t (*avrData)(const Material&) = [](const Material& mat) -> complex_t {
            const complex_t mdc = std::conj(mat.materialData());
            return mdc * mdc - 2.0 * mdc;
        };
        const complex_t avr_mat_data
            = std::conj(1.0 - std::sqrt(1.0 + averageData(layer_mat, regions, avrData)));
        return HomogeneousMaterial(avr_mat_name, avr_mat_data.real(), avr_mat_data.imag(), mag_avr);
    } else if (avr_material_type == MATERIAL_TYPES::MaterialBySLD) {
        complex_t (*avrData)(const Material&)
            = [](const Material& mat) { return mat.materialData(); };
        const complex_t avr_mat_data = averageData(layer_mat, regions, avrData);
        return MaterialBySLD(avr_mat_name, avr_mat_data.real(), avr_mat_data.imag(), mag_avr);
    } else
        throw std::runtime_error("Error in CalculateAverageMaterial: unknown material type.");
}

namespace
{
MATERIAL_TYPES checkMaterialTypes(const Material& layer_mat, const std::vector<HomogeneousRegion>& regions)
{
    MATERIAL_TYPES result = layer_mat.typeID();
    bool isDefault = layer_mat.isDefaultMaterial();
    for (auto& region : regions) {
        if (isDefault) {
            result = region.m_material.typeID();
            isDefault = region.m_material.isDefaultMaterial();
            continue;
        }
        if (region.m_material.typeID() != result && !region.m_material.isDefaultMaterial())
            throw std::runtime_error("Error in checkMaterialTypes(): non-default materials of "
                                     "different types used simultaneously.");
    }
    return result;
}

template <class T>
T averageData(const Material& layer_mat, const std::vector<HomogeneousRegion>& regions, T (*func_ptr) (const Material&))
{
    const T layer_data = func_ptr(layer_mat);
    T average = layer_data;
    for (auto& region : regions)
        average += region.m_volume * (func_ptr(region.m_material) - layer_data);
    return average;
}
}
