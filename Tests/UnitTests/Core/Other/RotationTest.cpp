#include "Core/Scattering/Rotations.h"
#include "Core/Vector/Transform3D.h"
#include "Tests/GTestWrapper/google_test.h"

#include <memory>

class RotationTest : public ::testing::Test
{
};

TEST_F(RotationTest, XRotations)
{
    double angle = 1.0;
    RotationX rot(angle);
    auto rot_matrix = rot.getTransform3D();
    auto P_rot = std::unique_ptr<IRotation>(IRotation::createRotation(rot_matrix));
    auto p_rot_cast = dynamic_cast<RotationX*>(P_rot.get());
    ASSERT_NE(p_rot_cast, nullptr);
    EXPECT_DOUBLE_EQ(p_rot_cast->getAngle(), angle);
}

TEST_F(RotationTest, YRotations)
{
    double angle = 1.0;
    RotationY rot(angle);
    auto rot_matrix = rot.getTransform3D();
    auto P_rot = std::unique_ptr<IRotation>(IRotation::createRotation(rot_matrix));
    auto p_rot_cast = dynamic_cast<RotationY*>(P_rot.get());
    ASSERT_NE(p_rot_cast, nullptr);
    EXPECT_DOUBLE_EQ(p_rot_cast->getAngle(), angle);
}

TEST_F(RotationTest, ZRotations)
{
    double angle = 1.0;
    RotationZ rot(angle);
    auto rot_matrix = rot.getTransform3D();
    auto P_rot = std::unique_ptr<IRotation>(IRotation::createRotation(rot_matrix));
    auto p_rot_cast = dynamic_cast<RotationZ*>(P_rot.get());
    ASSERT_NE(p_rot_cast, nullptr);
    EXPECT_DOUBLE_EQ(p_rot_cast->getAngle(), angle);
}

TEST_F(RotationTest, EulerRotations)
{
    double alpha = 1.0;
    double beta = 0.2;
    double gamma = -0.5;
    RotationEuler rot(alpha, beta, gamma);
    auto rot_matrix = rot.getTransform3D();
    auto P_rot = std::unique_ptr<IRotation>(IRotation::createRotation(rot_matrix));
    auto p_rot_cast = dynamic_cast<RotationEuler*>(P_rot.get());
    ASSERT_NE(p_rot_cast, nullptr);
    EXPECT_DOUBLE_EQ(p_rot_cast->getAlpha(), alpha);
    EXPECT_DOUBLE_EQ(p_rot_cast->getBeta(), beta);
    EXPECT_DOUBLE_EQ(p_rot_cast->getGamma(), gamma);
}
