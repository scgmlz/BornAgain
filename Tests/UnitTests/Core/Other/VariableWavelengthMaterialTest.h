#include "VariableWavelengthMaterial.h"
#include "Rotations.h"
#include "WavevectorInfo.h"
#include "Units.h"

class VariableWavelengthMaterialTest : public ::testing::Test
{
public:
    VariableWavelengthMaterialTest() {}
    virtual ~VariableWavelengthMaterialTest() {}
};

TEST_F(VariableWavelengthMaterialTest, InitializationTest)
{
    double number_density = 1.0;
    double scatt_length = 2.0;
    double cx = 4.0;
    double wavelength = 2.0;
    complex_t sld = complex_t(number_density * scatt_length, number_density * cx / wavelength);
    double prefix = wavelength * wavelength / M_PI;
    complex_t ref_index = std::sqrt(1.0 - prefix * sld);
    WavevectorInfo wv_info(kvector_t(), kvector_t(), wavelength);

    HomogeneousMaterial material("homogMaterial", sld, wavelength);
    VariableWavelengthMaterial vwl_material("homogMaterial", sld, wavelength);
    EXPECT_EQ(false, material == vwl_material);
    EXPECT_EQ(vwl_material.refractiveIndex(), vwl_material.refractiveIndex(wavelength));
    EXPECT_EQ(material.refractiveIndex(), vwl_material.refractiveIndex(wavelength));
    EXPECT_EQ(material.scalarSubstrSLD(wv_info), vwl_material.scalarSubstrSLD(wv_info));

    HomogeneousMaterial material2("homogMaterial", ref_index);
    EXPECT_EQ(material2.refractiveIndex(), vwl_material.refractiveIndex(wavelength));

    VariableWavelengthMaterial vwl_material2("homogMaterial", number_density, scatt_length, cx,
                                            wavelength);
    EXPECT_EQ(material2.refractiveIndex(), vwl_material2.refractiveIndex(wavelength));
}
