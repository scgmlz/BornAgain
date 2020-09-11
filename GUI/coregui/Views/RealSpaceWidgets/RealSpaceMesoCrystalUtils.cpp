// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceMesoCrystalUtils.cpp
//! @brief     Defines RealSpaceBuilderUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceMesoCrystalUtils.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/Units.h"
#include "Core/Particle/IParticle.h"
#include "Core/Particle/MesoCrystal.h"
#include "Core/Particle/Particle.h"
#include "Core/Particle/ParticleCoreShell.h"
#include "Core/Particle/ParticleDistribution.h"
#include "Core/Scattering/IFormFactor.h"
#include "Core/includeIncludes/HardParticles.h"
#include "GUI/ba3d/model/particles.h"
#include "GUI/coregui/Models/Lattice2DItems.h"
#include "GUI/coregui/Models/MesoCrystalItem.h"
#include "GUI/coregui/Models/ParticleCompositionItem.h"
#include "GUI/coregui/Models/ParticleCoreShellItem.h"
#include "GUI/coregui/Models/ParticleDistributionItem.h"
#include "GUI/coregui/Views/RealSpaceWidgets/Particle3DContainer.h"
#include "GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilderUtils.h"
#include "GUI/coregui/Views/RealSpaceWidgets/TransformTo3D.h"

namespace
{
const int n = 10; // TODO: Adjust this parameter based on the size of the mesocrystal

bool isPositionInsideMesoCrystal(const IFormFactor* outerShape, kvector_t positionInside)
{
    bool check(false);
    if (auto ff_AnisoPyramid = dynamic_cast<const FormFactorAnisoPyramid*>(outerShape)) {
        double L = ff_AnisoPyramid->getLength();
        double W = ff_AnisoPyramid->getWidth();
        double H = ff_AnisoPyramid->getHeight();
        double alpha = ff_AnisoPyramid->getAlpha();

        double l_z =
            L / 2
            - positionInside.z() / std::tan(alpha); // half-length of rectangle at a given height
        double w_z =
            W / 2
            - positionInside.z() / std::tan(alpha); // half-width of rectangle at a given height
        if (std::abs(positionInside.x()) <= l_z && std::abs(positionInside.y()) <= w_z
            && (positionInside.z() >= 0 && positionInside.z() <= H))
            check = true;
    } else if (auto ff_BarGauss = dynamic_cast<const FormFactorBarGauss*>(outerShape)) {
        double L = ff_BarGauss->getLength();
        double W = ff_BarGauss->getWidth();
        double H = ff_BarGauss->getHeight();

        if (std::abs(positionInside.x()) <= L / 2 && std::abs(positionInside.y()) <= W / 2
            && (positionInside.z() >= 0 && positionInside.z() <= H))
            check = true;
    } else if (auto ff_BarLorentz = dynamic_cast<const FormFactorBarLorentz*>(outerShape)) {
        double L = ff_BarLorentz->getLength();
        double W = ff_BarLorentz->getWidth();
        double H = ff_BarLorentz->getHeight();

        if (std::abs(positionInside.x()) <= L / 2 && std::abs(positionInside.y()) <= W / 2
            && (positionInside.z() >= 0 && positionInside.z() <= H))
            check = true;
    } else if (auto ff_Box = dynamic_cast<const FormFactorBox*>(outerShape)) {
        double L = ff_Box->getLength();
        double W = ff_Box->getWidth();
        double H = ff_Box->getHeight();

        if (std::abs(positionInside.x()) <= L / 2 && std::abs(positionInside.y()) <= W / 2
            && (positionInside.z() >= 0 && positionInside.z() <= H))
            check = true;
    } else if (auto ff_Cone = dynamic_cast<const FormFactorCone*>(outerShape)) {
        double R = ff_Cone->getRadius();
        double H = ff_Cone->getHeight();
        double alpha = ff_Cone->getAlpha();

        if (std::abs(positionInside.x()) > R || std::abs(positionInside.y()) > R
            || positionInside.z() < 0 || positionInside.z() > H)
            return check;

        double R_z = R - positionInside.z() / std::tan(alpha);
        if (std::pow(positionInside.x() / R_z, 2) + std::pow(positionInside.y() / R_z, 2) <= 1)
            check = true;
    } else if (auto ff_Cone6 = dynamic_cast<const FormFactorCone6*>(outerShape)) {
        double B = ff_Cone6->getBaseEdge();
        double H = ff_Cone6->getHeight();
        double alpha = ff_Cone6->getAlpha();

        if (std::abs(positionInside.x()) > B || std::abs(positionInside.y()) > B
            || positionInside.z() < 0 || positionInside.z() > H)
            return check;

        double l_z = B - positionInside.z() / std::tan(alpha); // edge of hexagon at a given height
        double theta_prime = 0; // angle between positionInside & x-axis in positionInside.z() plane
        if (positionInside.x() != 0 || positionInside.y() != 0)
            theta_prime = Units::rad2deg(std::asin(
                std::abs(positionInside.y())
                / std::sqrt(std::pow(positionInside.x(), 2) + std::pow(positionInside.y(), 2))));
        int c = static_cast<int>(theta_prime / 60); // multiplication constant
        double theta = Units::deg2rad(theta_prime - c * 60);
        double k_z = l_z / (std::cos(theta) + std::sin(theta) / std::tan(M_PI / 3));

        if (std::pow(positionInside.x(), 2) + std::pow(positionInside.y(), 2) <= std::pow(k_z, 2))
            check = true;
    } else if (auto ff_Cuboctahedron = dynamic_cast<const FormFactorCuboctahedron*>(outerShape)) {
        double L = ff_Cuboctahedron->getLength();
        double H = ff_Cuboctahedron->getHeight();
        double rH = ff_Cuboctahedron->getHeightRatio();
        double alpha = ff_Cuboctahedron->getAlpha();

        double total_Height = H + rH * H;

        if (std::abs(positionInside.x()) > L / 2 || std::abs(positionInside.y()) > L / 2
            || positionInside.z() < 0 || positionInside.z() > total_Height)
            return check;

        // half-length of square (i.e. horizontal cross-section of Cuboctahedron) at a given height
        double l_z = L / 2 - std::abs(H - positionInside.z()) / std::tan(alpha);
        if (std::abs(positionInside.x()) <= l_z && std::abs(positionInside.y()) <= l_z)
            check = true;
    } else if (auto ff_Cylinder = dynamic_cast<const FormFactorCylinder*>(outerShape)) {
        double R = ff_Cylinder->getRadius();
        double H = ff_Cylinder->getHeight();

        if (std::abs(positionInside.x()) > R || std::abs(positionInside.y()) > R
            || positionInside.z() < 0 || positionInside.z() > H)
            return check;

        if (std::pow(positionInside.x() / R, 2) + std::pow(positionInside.y() / R, 2) <= 1)
            check = true;
    } else if (dynamic_cast<const FormFactorDodecahedron*>(outerShape)) {
        // TODO: Implement Dodecahedron
        std::ostringstream ostr;
        ostr << "Sorry, outer shape Dodecahedron not yet implemented for Mesocrystal";
        ostr << "\n\nStay tuned!";
        throw Exceptions::ClassInitializationException(ostr.str());
    } else if (dynamic_cast<const FormFactorDot*>(outerShape)) {
        std::ostringstream ostr;
        ostr << "Cannot display particles inside the Mesocrystal!";
        ostr << "\n\nOuter shape is a Dot!";
        throw Exceptions::ClassInitializationException(ostr.str());
    } else if (auto ff_EllipsoidalCylinder =
                   dynamic_cast<const FormFactorEllipsoidalCylinder*>(outerShape)) {
        double a = ff_EllipsoidalCylinder->getRadiusX(); // semi-axis length along x
        double b = ff_EllipsoidalCylinder->getRadiusY(); // semi-axis length along y
        double H = ff_EllipsoidalCylinder->getHeight();

        if (std::abs(positionInside.x()) > a || std::abs(positionInside.y()) > b
            || positionInside.z() < 0 || positionInside.z() > H)
            return check;

        if (std::pow(positionInside.x() / a, 2) + std::pow(positionInside.y() / b, 2) <= 1)
            check = true;
    } else if (auto ff_FullSphere = dynamic_cast<const FormFactorFullSphere*>(outerShape)) {
        double R = ff_FullSphere->getRadius();

        if (std::abs(positionInside.x()) > R || std::abs(positionInside.y()) > R
            || positionInside.z() < 0 || positionInside.z() > 2 * R)
            return check;

        if (std::pow(positionInside.x() / R, 2) + std::pow(positionInside.y() / R, 2)
                + std::pow((positionInside.z() - R) / R, 2)
            <= 1)
            check = true;
    } else if (auto ff_FullSpheroid = dynamic_cast<const FormFactorFullSpheroid*>(outerShape)) {
        double a = ff_FullSpheroid->getRadius(); // semi-axis length along x and y
        double H = ff_FullSpheroid->getHeight();
        double c = H / 2; // semi-axis length along z

        if (std::abs(positionInside.x()) > a || std::abs(positionInside.y()) > a
            || positionInside.z() < 0 || positionInside.z() > H)
            return check;

        if (std::pow(positionInside.x() / a, 2) + std::pow(positionInside.y() / a, 2)
                + std::pow((positionInside.z() - c) / c, 2)
            <= 1)
            check = true;
    } else if (auto ff_HemiEllipsoid = dynamic_cast<const FormFactorHemiEllipsoid*>(outerShape)) {
        double a = ff_HemiEllipsoid->getRadiusX(); // semi-axis length along x
        double b = ff_HemiEllipsoid->getRadiusY(); // semi-axis length along y
        double c = ff_HemiEllipsoid->getHeight();  // semi-axis length along z

        if (std::abs(positionInside.x()) > a || std::abs(positionInside.y()) > b
            || positionInside.z() < 0 || positionInside.z() > c)
            return check;

        if (std::pow(positionInside.x() / a, 2) + std::pow(positionInside.y() / b, 2)
                + std::pow(positionInside.z() / c, 2)
            <= 1)
            check = true;
    } else if (dynamic_cast<const FormFactorIcosahedron*>(outerShape)) {
        // TODO: Implement Icosahedron
        std::ostringstream ostr;
        ostr << "Sorry, outer shape Icosahedron not yet implemented for Mesocrystal";
        ostr << "\n\nStay tuned!";
        throw Exceptions::ClassInitializationException(ostr.str());
    } else if (auto ff_Prism3 = dynamic_cast<const FormFactorPrism3*>(outerShape)) {
        double B = ff_Prism3->getBaseEdge();
        double H = ff_Prism3->getHeight();

        double l = B * std::sin(M_PI / 3);
        double x_shift = B / 2 * std::tan(M_PI / 6);

        if (positionInside.x() + x_shift < 0 || positionInside.x() + x_shift > l
            || std::abs(positionInside.y()) > B / 2 || positionInside.z() < 0
            || positionInside.z() > H)
            return check;

        double theta = 0; // angle between positionInside & x-axis in positionInside.z() plane
        if (positionInside.x() + x_shift != 0 || positionInside.y() != 0)
            theta = std::asin(std::abs(positionInside.y())
                              / std::sqrt(std::pow(positionInside.x() + x_shift, 2)
                                          + std::pow(positionInside.y(), 2)));

        double k = l / (std::sin(theta) / std::tan(M_PI / 6) + std::cos(theta));

        if (std::pow(positionInside.x() + x_shift, 2) + std::pow(positionInside.y(), 2)
            <= std::pow(k, 2))
            check = true;
    } else if (auto ff_Prism6 = dynamic_cast<const FormFactorPrism6*>(outerShape)) {
        double B = ff_Prism6->getBaseEdge();
        double H = ff_Prism6->getHeight();

        if (std::abs(positionInside.x()) > B || std::abs(positionInside.y()) > B
            || positionInside.z() < 0 || positionInside.z() > H)
            return check;

        double theta_prime = 0; // angle between positionInside & x-axis in positionInside.z() plane
        if (positionInside.x() != 0 || positionInside.y() != 0)
            theta_prime = Units::rad2deg(std::asin(
                std::abs(positionInside.y())
                / std::sqrt(std::pow(positionInside.x(), 2) + std::pow(positionInside.y(), 2))));
        int c = static_cast<int>(theta_prime / 60); // multiplicative constant
        double theta = Units::deg2rad(theta_prime - c * 60);
        double k_z = B / (std::cos(theta) + std::sin(theta) / std::tan(M_PI / 3));

        if (std::pow(positionInside.x(), 2) + std::pow(positionInside.y(), 2) <= std::pow(k_z, 2))
            check = true;
    } else if (auto ff_Pyramid = dynamic_cast<const FormFactorPyramid*>(outerShape)) {
        double B = ff_Pyramid->getBaseEdge();
        double H = ff_Pyramid->getHeight();
        double alpha = ff_Pyramid->getAlpha();

        double l_z =
            B / 2 - positionInside.z() / std::tan(alpha); // half-length of square at a given height
        if (std::abs(positionInside.x()) <= l_z && std::abs(positionInside.y()) <= l_z
            && (positionInside.z() >= 0 && positionInside.z() <= H))
            check = true;
    } else if (dynamic_cast<const FormFactorCosineRippleBox*>(outerShape)) {
        // TODO: Implement CosineRippleBox
        std::ostringstream ostr;
        ostr << "Sorry, outer shape CosineRippleBox not yet implemented for Mesocrystal";
        ostr << "\n\nStay tuned!";
        throw Exceptions::ClassInitializationException(ostr.str());
    } else if (dynamic_cast<const FormFactorCosineRippleGauss*>(outerShape)) {
        // TODO: Implement CosineRippleGauss
        std::ostringstream ostr;
        ostr << "Sorry, outer shape CosineRippleGauss not yet implemented for Mesocrystal";
        ostr << "\n\nStay tuned!";
        throw Exceptions::ClassInitializationException(ostr.str());
    } else if (dynamic_cast<const FormFactorCosineRippleLorentz*>(outerShape)) {
        // TODO: Implement CosineRippleLorentz
        std::ostringstream ostr;
        ostr << "Sorry, outer shape CosineRippleLorentz not yet implemented for Mesocrystal";
        ostr << "\n\nStay tuned!";
        throw Exceptions::ClassInitializationException(ostr.str());
    } else if (dynamic_cast<const FormFactorSawtoothRippleBox*>(outerShape)) {
        // TODO: Implement SawtoothRippleBox
        std::ostringstream ostr;
        ostr << "Sorry, outer shape SawtoothRippleBox not yet implemented for Mesocrystal";
        ostr << "\n\nStay tuned!";
        throw Exceptions::ClassInitializationException(ostr.str());
    } else if (dynamic_cast<const FormFactorSawtoothRippleGauss*>(outerShape)) {
        // TODO: Implement SawtoothRippleGauss
        std::ostringstream ostr;
        ostr << "Sorry, outer shape SawtoothRippleGauss not yet implemented for Mesocrystal";
        ostr << "\n\nStay tuned!";
        throw Exceptions::ClassInitializationException(ostr.str());
    } else if (dynamic_cast<const FormFactorSawtoothRippleLorentz*>(outerShape)) {
        // TODO: Implement SawtoothRippleLorentz
        std::ostringstream ostr;
        ostr << "Sorry, outer shape SawtoothRippleLorentz not yet implemented for Mesocrystal";
        ostr << "\n\nStay tuned!";
        throw Exceptions::ClassInitializationException(ostr.str());
    } else if (auto ff_Tetrahedron = dynamic_cast<const FormFactorTetrahedron*>(outerShape)) {
        double B = ff_Tetrahedron->getBaseEdge();
        double H = ff_Tetrahedron->getHeight();
        double alpha = ff_Tetrahedron->getAlpha();

        double B_z =
            B - positionInside.z() * 2 / std::tan(alpha); // edge of triangle at a given height

        double l = B_z * std::sin(M_PI / 3);
        double x_shift = B_z / 2 * std::tan(M_PI / 6);

        if (positionInside.x() + x_shift < 0 || positionInside.x() + x_shift > l
            || std::abs(positionInside.y()) > B_z / 2 || positionInside.z() < 0
            || positionInside.z() > H)
            return check;

        double theta = 0; // angle between positionInside & x-axis in positionInside.z() plane
        if (positionInside.x() + x_shift != 0 || positionInside.y() != 0)
            theta = std::asin(std::abs(positionInside.y())
                              / std::sqrt(std::pow(positionInside.x() + x_shift, 2)
                                          + std::pow(positionInside.y(), 2)));

        double k = l / (std::sin(theta) / std::tan(M_PI / 6) + std::cos(theta));

        if (std::pow(positionInside.x() + x_shift, 2) + std::pow(positionInside.y(), 2)
            <= std::pow(k, 2))
            check = true;
    } else if (dynamic_cast<const FormFactorTruncatedCube*>(outerShape)) {
        // TODO: Implement Truncated cube
        std::ostringstream ostr;
        ostr << "Sorry, outer shape Truncated cube not yet implemented for Mesocrystal";
        ostr << "\n\nStay tuned!";
        throw Exceptions::ClassInitializationException(ostr.str());
    } else if (auto ff_TruncatedSphere =
                   dynamic_cast<const FormFactorTruncatedSphere*>(outerShape)) {
        double R = ff_TruncatedSphere->getRadius();
        double H = ff_TruncatedSphere->getHeight();
        double deltaH = ff_TruncatedSphere->getRemovedTop();
        if (std::abs(positionInside.x()) > R || std::abs(positionInside.y()) > R
            || positionInside.z() < 0 || positionInside.z() > (H - deltaH))
            return check;

        if (std::pow(positionInside.x() / R, 2) + std::pow(positionInside.y() / R, 2)
                + std::pow((positionInside.z() - (H - R)) / R, 2)
            <= 1)
            check = true;
    } else if (dynamic_cast<const FormFactorTruncatedSpheroid*>(outerShape)) {
        // TODO: Implement Truncated spheroid
        std::ostringstream ostr;
        ostr << "Sorry, outer shape Truncated spheroid not yet implemented for Mesocrystal";
        ostr << "\n\nStay tuned!";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return check;
}
} // namespace

RealSpaceMesoCrystal::~RealSpaceMesoCrystal() {}

RealSpaceMesoCrystal::RealSpaceMesoCrystal(const MesoCrystalItem* mesoCrystalItem,
                                           double total_abundance, const QVector3D& origin)
{
    m_mesoCrystalItem = mesoCrystalItem;
    m_total_abundance = total_abundance;
    m_origin = origin;
}

Particle3DContainer RealSpaceMesoCrystal::populateMesoCrystal()
{
    auto mesoCrystal = m_mesoCrystalItem->createMesoCrystal();

    std::unique_ptr<MesoCrystal> M_clone(mesoCrystal->clone()); // clone of the mesoCrystal

    // These methods DO NOT add rotation/translation of the mesoCrystal to its children
    // and hence they need to be added manually
    auto lattice = m_mesoCrystalItem->getLattice();
    auto particleBasis = m_mesoCrystalItem->getBasis();
    auto outerShapeff = m_mesoCrystalItem->getOuterShape();

    auto mesoCrystal_rotation = M_clone->rotation();
    auto mesoCrystal_translation = M_clone->position();

    Particle3DContainer mesoCrystalBasis3DContainer;

    if (dynamic_cast<const ParticleComposition*>(particleBasis.get())) {
        auto particleComposition = dynamic_cast<const ParticleComposition*>(particleBasis.get());
        mesoCrystalBasis3DContainer = RealSpaceBuilderUtils::particleComposition3DContainer(
            *particleComposition, 1.0, m_origin);
    } else if (dynamic_cast<const ParticleCoreShell*>(particleBasis.get())) {
        auto particleCoreShell = dynamic_cast<const ParticleCoreShell*>(particleBasis.get());
        mesoCrystalBasis3DContainer =
            RealSpaceBuilderUtils::particleCoreShell3DContainer(*particleCoreShell, 1.0, m_origin);
    } else if (dynamic_cast<const MesoCrystal*>(particleBasis.get())) {
        // TODO: Implement method to populate MesoCrystal from CORE and NOT from MesoCrystalItem
        // as it is done currently in RealSpaceBuilderUtils::mesoCrystal3DContainer
        std::ostringstream ostr;
        ostr << "Sorry, MesoCrystal inside MesoCrystal not yet implemented";
        ostr << "\n\nStay tuned!";
        throw Exceptions::ClassInitializationException(ostr.str());
    } else {
        auto particle = dynamic_cast<const Particle*>(particleBasis.get());
        mesoCrystalBasis3DContainer =
            RealSpaceBuilderUtils::singleParticle3DContainer(*particle, 1.0, m_origin);
    }

    Particle3DContainer mesoCrystal3DContainer;

    for (int k = -n; k <= n; k++) {
        for (int j = -n; j <= n; j++) {
            for (int i = -n; i <= n; i++) {
                auto positionInside = i * lattice.getBasisVectorA() + j * lattice.getBasisVectorB()
                                      + k * lattice.getBasisVectorC();

                if (isPositionInsideMesoCrystal(outerShapeff.get(), positionInside)) {
                    for (size_t it = 0; it < mesoCrystalBasis3DContainer.containerSize(); ++it) {
                        auto particle3D = mesoCrystalBasis3DContainer.createParticle(it);
                        particle3D->addTranslation(
                            QVector3D(static_cast<float>(positionInside.x()),
                                      static_cast<float>(positionInside.y()),
                                      static_cast<float>(positionInside.z())));

                        particle3D->addExtrinsicRotation(
                            RealSpaceBuilderUtils::implementParticleRotationfromIRotation(
                                mesoCrystal_rotation));

                        particle3D->addTranslation(
                            QVector3D(static_cast<float>(mesoCrystal_translation.x()),
                                      static_cast<float>(mesoCrystal_translation.y()),
                                      static_cast<float>(mesoCrystal_translation.z())));

                        mesoCrystal3DContainer.addParticle(
                            particle3D.release(), mesoCrystalBasis3DContainer.particle3DBlend(it));
                    }
                }
            }
        }
    }

    // Add outer shape for visualisation
    auto outerShape3D = TransformTo3D::createParticlefromIFormFactor(outerShapeff.get());
    outerShape3D->addTransform(
        RealSpaceBuilderUtils::implementParticleRotationfromIRotation(mesoCrystal_rotation),
        QVector3D(static_cast<float>(mesoCrystal_translation.x()),
                  static_cast<float>(mesoCrystal_translation.y()),
                  static_cast<float>(mesoCrystal_translation.z())));

    // assign grey (default) color to the outer shape
    QColor color = {};
    color.setAlphaF(0.3);
    outerShape3D->color = color;
    mesoCrystal3DContainer.addParticle(outerShape3D.release(), true);

    // set the correct abundance for the MesoCrystal
    mesoCrystal3DContainer.setCumulativeAbundance(M_clone->abundance() / m_total_abundance);
    mesoCrystal3DContainer.setParticleType("MesoCrystal");

    return mesoCrystal3DContainer;
}
