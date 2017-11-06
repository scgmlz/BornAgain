#include "MaterialFactoryFuncs.h"
#include "RefractiveCoefMaterial.h"
#include "WavelengthIndependentMaterial.h"

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
    std::unique_ptr<RefractiveCoefMaterial> mat_impl(
        new RefractiveCoefMaterial(name, delta, beta, magnetization));
    return Material(std::move(mat_impl));
}

Material HomogeneousMaterial()
{
    return HomogeneousMaterial("vacuum", 0.0, 0.0, kvector_t{});
}

Material MaterialBySLD(const std::string& name, double sld, double abs_term,
                       kvector_t magnetization)
{
    std::unique_ptr<WavelengthIndependentMaterial> mat_impl(
        new WavelengthIndependentMaterial(name, sld, abs_term, magnetization));
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
