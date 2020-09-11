#include "Core/Basics/Units.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/includeIncludes/FormFactors.h"
#include "Core/includeIncludes/InterferenceFunctions.h"
#include "GUI/coregui/Models/FormFactorItems.h"
#include "GUI/coregui/Models/InterferenceFunctionItems.h"
#include "Tests/GTestWrapper/google_test.h"

class TestGUICoreObjectCorrespondence : public ::testing::Test
{
public:
    void GUICoreObjectCorrespondence(const SessionItem& gui_object,
                                     const IParameterized& core_object)
    {
        // First check if names correspond:
        EXPECT_EQ(gui_object.displayName(), QString::fromStdString(core_object.getName()));

        auto core_parameter_names = core_object.parameterPool()->parameterNames();
        for (auto name : core_parameter_names) {
            QString gui_name = QString::fromStdString(name);
            EXPECT_TRUE(gui_object.isTag(gui_name));
        }
    }
};

TEST_F(TestGUICoreObjectCorrespondence, test_AnisoPyramid)
{
    AnisoPyramidItem gui_anisopyramid;
    FormFactorAnisoPyramid core_anisopyramid(1.0, 2.0, 0.1, 45.0 * Units::degree);
    GUICoreObjectCorrespondence(gui_anisopyramid, core_anisopyramid);
}

TEST_F(TestGUICoreObjectCorrespondence, test_Box)
{
    BoxItem gui_box;
    FormFactorBox core_box(1.0, 1.5, 3.0);
    GUICoreObjectCorrespondence(gui_box, core_box);
}

TEST_F(TestGUICoreObjectCorrespondence, test_Cone)
{
    ConeItem gui_cone;
    FormFactorCone core_cone(1.0, 0.2, 45.0 * Units::degree);
    GUICoreObjectCorrespondence(gui_cone, core_cone);
}

TEST_F(TestGUICoreObjectCorrespondence, test_Cone6)
{
    Cone6Item gui_cone6;
    FormFactorCone6 core_cone6(1.0, 0.2, 45.0 * Units::degree);
    GUICoreObjectCorrespondence(gui_cone6, core_cone6);
}

TEST_F(TestGUICoreObjectCorrespondence, test_Cuboctahedron)
{
    CuboctahedronItem gui_cuboctahedron;
    FormFactorCuboctahedron core_cuboctahedron(1.0, 0.4, 1.0, 45.0 * Units::degree);
    GUICoreObjectCorrespondence(gui_cuboctahedron, core_cuboctahedron);
}

TEST_F(TestGUICoreObjectCorrespondence, test_Cylinder)
{
    CylinderItem gui_cylinder;
    FormFactorCylinder core_cylinder(1.0, 3.0);
    GUICoreObjectCorrespondence(gui_cylinder, core_cylinder);
}

TEST_F(TestGUICoreObjectCorrespondence, test_Dodecahedron)
{
    DodecahedronItem gui_dodecahedron;
    FormFactorDodecahedron core_dodecahedron(3.0);
    GUICoreObjectCorrespondence(gui_dodecahedron, core_dodecahedron);
}

TEST_F(TestGUICoreObjectCorrespondence, test_Dot)
{
    DotItem gui_dot;
    FormFactorDot core_dot(5.0);
    GUICoreObjectCorrespondence(gui_dot, core_dot);
}

TEST_F(TestGUICoreObjectCorrespondence, test_EllipsoidalCylinder)
{
    EllipsoidalCylinderItem gui_ellcylinder;
    FormFactorEllipsoidalCylinder core_ellcylinder(2.0, 1.0, 1.0);
    GUICoreObjectCorrespondence(gui_ellcylinder, core_ellcylinder);
}

TEST_F(TestGUICoreObjectCorrespondence, test_FullSphere)
{
    FullSphereItem gui_sphere;
    FormFactorFullSphere core_sphere(1.0);
    GUICoreObjectCorrespondence(gui_sphere, core_sphere);
}

TEST_F(TestGUICoreObjectCorrespondence, test_FullSpheroid)
{
    FullSpheroidItem gui_spheroid;
    FormFactorFullSpheroid core_spheroid(1.0, 2.0);
    GUICoreObjectCorrespondence(gui_spheroid, core_spheroid);
}

TEST_F(TestGUICoreObjectCorrespondence, test_HemiEllipsoid)
{
    HemiEllipsoidItem gui_hemiellipsoid;
    FormFactorHemiEllipsoid core_hemiellipsoid(2.0, 1.0, 0.5);
    GUICoreObjectCorrespondence(gui_hemiellipsoid, core_hemiellipsoid);
}

TEST_F(TestGUICoreObjectCorrespondence, test_Icosahedron)
{
    IcosahedronItem gui_icosahedron;
    FormFactorIcosahedron core_icosahedron(8.0);
    GUICoreObjectCorrespondence(gui_icosahedron, core_icosahedron);
}

TEST_F(TestGUICoreObjectCorrespondence, test_Prism3)
{
    Prism3Item gui_prism3;
    FormFactorPrism3 core_prism3(1.0, 2.0);
    GUICoreObjectCorrespondence(gui_prism3, core_prism3);
}

TEST_F(TestGUICoreObjectCorrespondence, test_Prism6)
{
    Prism6Item gui_prism6;
    FormFactorPrism6 core_prism6(1.0, 2.0);
    GUICoreObjectCorrespondence(gui_prism6, core_prism6);
}

TEST_F(TestGUICoreObjectCorrespondence, test_Pyramid)
{
    PyramidItem gui_pyramid;
    FormFactorPyramid core_pyramid(1.0, 0.2, 45.0 * Units::degree);
    GUICoreObjectCorrespondence(gui_pyramid, core_pyramid);
}

TEST_F(TestGUICoreObjectCorrespondence, test_CosineRippleBox)
{
    CosineRippleBoxItem gui_ripple1;
    FormFactorCosineRippleBox core_ripple1(10.0, 2.0, 1.0);
    GUICoreObjectCorrespondence(gui_ripple1, core_ripple1);
}

TEST_F(TestGUICoreObjectCorrespondence, test_SawtoothRippleBox)
{
    SawtoothRippleBoxItem gui_ripple2;
    FormFactorSawtoothRippleBox core_ripple2(10.0, 2.0, 1.0, 0.1);
    GUICoreObjectCorrespondence(gui_ripple2, core_ripple2);
}

TEST_F(TestGUICoreObjectCorrespondence, test_Tetrahedron)
{
    TetrahedronItem gui_tetrahedron;
    FormFactorTetrahedron core_tetrahedron(1.0, 0.1, 45.0 * Units::degree);
    GUICoreObjectCorrespondence(gui_tetrahedron, core_tetrahedron);
}

TEST_F(TestGUICoreObjectCorrespondence, test_TruncatedCube)
{
    TruncatedCubeItem gui_trunccube;
    FormFactorTruncatedCube core_trunccube(2.0, 0.2);
    GUICoreObjectCorrespondence(gui_trunccube, core_trunccube);
}

TEST_F(TestGUICoreObjectCorrespondence, test_TruncatedSphere)
{
    TruncatedSphereItem gui_truncsphere;
    FormFactorTruncatedSphere core_truncsphere(1.0, 0.5, 0);
    GUICoreObjectCorrespondence(gui_truncsphere, core_truncsphere);
}

TEST_F(TestGUICoreObjectCorrespondence, test_TruncatedSpheroid)
{
    TruncatedSpheroidItem gui_truncspheroid;
    FormFactorTruncatedSpheroid core_truncspheroid(1.0, 1.5, 1.5, 0);
    GUICoreObjectCorrespondence(gui_truncspheroid, core_truncspheroid);
}

TEST_F(TestGUICoreObjectCorrespondence, test_RadialParacrystal)
{
    InterferenceFunctionRadialParaCrystalItem gui_radialparacrystal;
    InterferenceFunctionRadialParaCrystal core_radialparacrystal(10.0, 1e-6);
    GUICoreObjectCorrespondence(gui_radialparacrystal, core_radialparacrystal);
}

TEST_F(TestGUICoreObjectCorrespondence, test_1DLattice)
{
    InterferenceFunction1DLatticeItem gui_1d_lattice;
    InterferenceFunction1DLattice core_1d_lattice(20.0, 0.0);
    GUICoreObjectCorrespondence(gui_1d_lattice, core_1d_lattice);
}
