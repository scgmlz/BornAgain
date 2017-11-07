#include "MaterialFactoryFuncs.h"
#include "MaterialBySLDImpl.h"
#include "RefractiveMaterialImpl.h"
#include "SlicedParticle.h"
#include "WavevectorInfo.h"
#include "Rotations.h"
#include "Units.h"
#include "Exceptions.h"

class MaterialTest : public ::testing::Test
{
public:
    MaterialTest()
    {
    }
    virtual ~MaterialTest()
    {
    }
};

TEST_F(MaterialTest, MaterialConstruction)
{
    complex_t material_data = complex_t(0.0, 2.0);
    complex_t refIndex = complex_t(1.0 - material_data.real(), material_data.imag());
    kvector_t magnetism = kvector_t(3.0, 4.0, 5.0);

    Material material = HomogeneousMaterial("MagMaterial", refIndex, magnetism);
    EXPECT_EQ("MagMaterial", material.getName());
    EXPECT_EQ(material_data, material.materialData());
    EXPECT_EQ(magnetism, material.magnetization());

    Material material2 = HomogeneousMaterial("MagMaterial", material_data.real(),
                                                 material_data.imag(), magnetism);
    EXPECT_EQ("MagMaterial", material2.getName());
    EXPECT_EQ(material_data, material2.materialData());
    EXPECT_EQ(magnetism, material2.magnetization());

    Material material3 = MaterialBySLD("MagMaterial", material_data.real(),
                                                    material_data.imag(), magnetism);
    EXPECT_EQ("MagMaterial", material3.getName());
    EXPECT_EQ(material_data, material3.materialData());
    EXPECT_EQ(magnetism, material3.magnetization());

    kvector_t default_magnetism = kvector_t{};

    Material material4 = HomogeneousMaterial("Material", refIndex);
    EXPECT_EQ("Material", material4.getName());
    EXPECT_EQ(material_data, material4.materialData());
    EXPECT_EQ(default_magnetism, material4.magnetization());

    Material material5
        = HomogeneousMaterial("Material", material_data.real(), material_data.imag());
    EXPECT_EQ("Material", material5.getName());
    EXPECT_EQ(material_data, material5.materialData());
    EXPECT_EQ(default_magnetism, material5.magnetization());

    Material material6
        = MaterialBySLD("Material", material_data.real(), material_data.imag());
    EXPECT_EQ("Material", material6.getName());
    EXPECT_EQ(material_data, material6.materialData());
    EXPECT_EQ(default_magnetism, material6.magnetization());

    constexpr double basic_wavelength = 0.1798197; // nm
    Material material7 = MaterialByAbsCX("Material", material_data.real(),
                                         material_data.imag() * basic_wavelength);
    EXPECT_TRUE(material7.getName() == material6.getName());
    EXPECT_TRUE(material7.magnetization() == material6.magnetization());
    EXPECT_DOUBLE_EQ(material7.materialData().real(), material6.materialData().real());
    EXPECT_DOUBLE_EQ(material7.materialData().imag(), material6.materialData().imag());
    EXPECT_TRUE(material7.typeID() == material6.typeID());
}

TEST_F(MaterialTest, MaterialTransform)
{
    complex_t material_data = complex_t(1.0, 0.0);
    complex_t refIndex = complex_t(1.0 - material_data.real(), material_data.imag());
    kvector_t magnetism = kvector_t(1.0, 0.0, 0.0);
    RotationZ transform(90. * Units::degree);
    kvector_t transformed_mag = transform.getTransform3D().transformed(magnetism);

    Material material = HomogeneousMaterial("Material", refIndex, magnetism);
    Material material2 = material.transformedMaterial(transform.getTransform3D());

    EXPECT_EQ("Material", material2.getName());
    EXPECT_EQ(material_data, material2.materialData());
    EXPECT_EQ(transformed_mag, material2.magnetization());

    Material material3 = MaterialBySLD("Material", material_data.real(), material_data.imag(), magnetism);
    Material material4 = material.transformedMaterial(transform.getTransform3D());

    EXPECT_EQ("Material", material4.getName());
    EXPECT_EQ(material_data, material4.materialData());
    EXPECT_EQ(transformed_mag, material4.magnetization());
}

TEST_F(MaterialTest, DefaultMaterials)
{
    Material material = HomogeneousMaterial();
    const double dummy_wavelength = 1.0;

    EXPECT_EQ(material.getName(), std::string("vacuum"));
    EXPECT_EQ(material.getName(), MaterialBySLD().getName());

    EXPECT_EQ(material.materialData(), complex_t());
    EXPECT_EQ(material.materialData(), MaterialBySLD().materialData());

    EXPECT_EQ(material.magnetization(), kvector_t{});
    EXPECT_EQ(material.magnetization(), MaterialBySLD().magnetization());

    EXPECT_EQ(material.refractiveIndex(dummy_wavelength), complex_t(1.0, 0.0));
    EXPECT_EQ(material.refractiveIndex(dummy_wavelength),
              MaterialBySLD().refractiveIndex(dummy_wavelength));

    EXPECT_TRUE(material.typeID() == HomogeneousMaterial().typeID());
    EXPECT_FALSE(material.typeID() == MaterialBySLD().typeID());
}

TEST_F(MaterialTest, ComputationTest)
{
    // Reference data for Fe taken from
    // https://sld-calculator.appspot.com/save
    // http://www.ati.ac.at/~neutropt/scattering/table.html
    const double bc = 9.45e-6; // nm, bound coherent scattering length
    const double abs_cs = 2.56e-10; // nm^2, absorption cross-section for 2200 m/s neutrons
    const double basic_wavelength = 0.1798197; // nm, wavelength of 2200 m/s neutrons
    const double mol_mass = 55.845; // g/mol, Fe molar mass
    const double avog_number = 6.022e+23; // mol^{-1}, Avogadro number
    const double density = 7.874e-21; // g/nm^3, Fe material density
    const double number_density = avog_number * density / mol_mass; // 1/nm^3, Fe number density
    const double sld = number_density * bc;
    const double abs_term = number_density * abs_cs / basic_wavelength;

    const complex_t sld_ref(8.0241e-04, -6.0448e-8); // nm^{-2}, reference data, wavelength-independent
    const double wl_factor_2200 = basic_wavelength * basic_wavelength / M_PI;
    const double wl_factor_1100 = 4.0 * basic_wavelength * basic_wavelength / M_PI;

    Material material = MaterialBySLD("Fe", sld, abs_term);
    const complex_t sld_res_2200 = (1.0 - material.refractiveIndex2(basic_wavelength)) / wl_factor_2200;
    const complex_t sld_res_1100 = (1.0 - material.refractiveIndex2(2.0 * basic_wavelength)) / wl_factor_1100;

    EXPECT_NEAR(0.0, (sld_ref.real() - sld_res_2200.real()) / sld_ref.real(), 1.e-3);
    EXPECT_NEAR(0.0, (sld_ref.imag() - sld_res_2200.imag()) / sld_ref.imag(), 1.e-3);
    EXPECT_NEAR(0.0, (sld_ref.real() - sld_res_1100.real()) / sld_ref.real(), 1.e-3);
    EXPECT_NEAR(0.0, (sld_ref.imag() - sld_res_1100.imag()) / sld_ref.imag(), 1.e-3);

    const complex_t refr_index = material.refractiveIndex(2.0 * basic_wavelength);
    WavevectorInfo wv_info(cvector_t{}, cvector_t{}, 2.0 * basic_wavelength);

    Material material2 = HomogeneousMaterial("Fe", 1.0 - refr_index.real(), std::abs(refr_index.imag()));
    const complex_t subtrSLD = material2.scalarSubtrSLD(wv_info);
    const complex_t subtrSLDWlIndep = material.scalarSubtrSLD(wv_info);
    EXPECT_FLOAT_EQ(subtrSLD.real(), subtrSLDWlIndep.real());
    EXPECT_FLOAT_EQ(subtrSLD.imag(), subtrSLDWlIndep.imag());
}

TEST_F(MaterialTest, AveragedMaterialTest)
{
    kvector_t magnetization = kvector_t {1.0, 0.0, 0.0};
    const Material material = HomogeneousMaterial("Material", 0.5, 0.5, magnetization);
    const std::vector<HomogeneousRegion> regions = {HomogeneousRegion{0.25, material},
                                                    HomogeneousRegion{0.25, material}};

    const Material material_avr = createAveragedMaterial(material, regions);
    EXPECT_EQ(material_avr.getName(), material.getName() + "_avg");
    EXPECT_EQ(material_avr.magnetization(), magnetization);
    EXPECT_DOUBLE_EQ(material_avr.materialData().real(), 0.5);
    EXPECT_DOUBLE_EQ(material_avr.materialData().imag(), 0.5);
    EXPECT_TRUE(material_avr.typeID() == MATERIAL_TYPES::RefractiveMaterial);

    const Material material2 = MaterialBySLD();
    const Material material_avr2 = createAveragedMaterial(material2, regions);
    const complex_t expected_res = std::conj(1.0 - std::sqrt(complex_t(0.5, 0.25)));
    EXPECT_DOUBLE_EQ(material_avr2.materialData().real(), expected_res.real());
    EXPECT_DOUBLE_EQ(material_avr2.materialData().imag(), expected_res.imag());
    EXPECT_EQ(material_avr2.magnetization(), kvector_t(0.5, 0.0, 0.0));
    EXPECT_TRUE(material_avr2.typeID() == MATERIAL_TYPES::RefractiveMaterial);

    const Material material3 = MaterialBySLD("Material3", 0.5, 0.5, magnetization);
    EXPECT_THROW(createAveragedMaterial(material3, regions), std::runtime_error);

    const Material material4 = HomogeneousMaterial();
    const std::vector<HomogeneousRegion> regions2
        = {HomogeneousRegion{0.25, material3}, HomogeneousRegion{0.25, material3}};
    const Material material_avr3 = createAveragedMaterial(material4, regions2);
    EXPECT_DOUBLE_EQ(material_avr3.materialData().real(), 0.25);
    EXPECT_DOUBLE_EQ(material_avr3.materialData().imag(), 0.25);
    EXPECT_EQ(material_avr3.magnetization(), kvector_t(0.5, 0.0, 0.0));
    EXPECT_TRUE(material_avr3.typeID() == MATERIAL_TYPES::MaterialBySLD);
}

TEST_F(MaterialTest, TypeIdsTest)
{
    Material material = MaterialBySLD("Material", 1.0, 1.0);
    Material material2 = HomogeneousMaterial("Material", 1.0, 1.0);
    EXPECT_TRUE(material.typeID() == MATERIAL_TYPES::MaterialBySLD);
    EXPECT_TRUE(material2.typeID() == MATERIAL_TYPES::RefractiveMaterial);
    EXPECT_TRUE(material.typeID() != material2.typeID());
    Material material3 = MaterialBySLD("Material", 1.0, 1.0);
    EXPECT_TRUE(material.typeID() == material3.typeID());
}

TEST_F(MaterialTest, MaterialComparison)
{
    Material material = MaterialBySLD("Material", 1.0, 1.0);
    Material material2 = HomogeneousMaterial("Material", 1.0, 1.0);
    EXPECT_TRUE(material == material);
    EXPECT_FALSE(material != material);
    EXPECT_FALSE(material == material2);

    Material material3 = HomogeneousMaterial("Material3", 2.0, 2.0);
    EXPECT_FALSE(material3 == material2);
    EXPECT_TRUE(material3 != material2);

    Material material4 = HomogeneousMaterial("Material", 1.0, 1.0, kvector_t{1.0, 2.0, 3.0});
    EXPECT_FALSE(material4 == material2);
    EXPECT_TRUE(material4 != material2);

    EXPECT_FALSE(HomogeneousMaterial() == MaterialBySLD());
    EXPECT_TRUE(HomogeneousMaterial() != MaterialBySLD());
}

TEST_F(MaterialTest, MaterialCopy)
{
    complex_t material_data = complex_t(0.0, 2.0);
    complex_t refIndex = complex_t(1.0 - material_data.real(), material_data.imag());
    kvector_t magnetism = kvector_t(3.0, 4.0, 5.0);
    Material material = HomogeneousMaterial("MagMaterial", refIndex, magnetism);

    Material copy = material;

    EXPECT_EQ("MagMaterial", copy.getName());
    EXPECT_EQ(material_data, copy.materialData());
    EXPECT_EQ(magnetism, copy.magnetization());
    EXPECT_TRUE(material == copy);
}

TEST_F(MaterialTest, MaterialMove)
{
    complex_t material_data = complex_t(0.0, 2.0);
    complex_t refIndex = complex_t(1.0 - material_data.real(), material_data.imag());
    kvector_t magnetism = kvector_t(3.0, 4.0, 5.0);
    Material material = HomogeneousMaterial("MagMaterial", refIndex, magnetism);

    Material move(std::move(material));
    EXPECT_EQ("MagMaterial", move.getName());
    EXPECT_EQ(material_data, move.materialData());
    EXPECT_EQ(magnetism, move.magnetization());
    EXPECT_TRUE(material.isEmpty());
}

TEST_F(MaterialTest, MaterialAssignment)
{
    Material material = MaterialBySLD("Material", 1.0, 1.0);
    Material material_ref = MaterialBySLD("Material", 1.0, 1.0);

    material = material;
    EXPECT_TRUE(material == material_ref);

    material = std::move(material);
    EXPECT_TRUE(material == material_ref);

    Material material2 = std::move(material);
    EXPECT_TRUE(material.isEmpty());
    EXPECT_THROW(material2 = material, Exceptions::NullPointerException);
}
