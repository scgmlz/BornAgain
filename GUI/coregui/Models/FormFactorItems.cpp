// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FormFactorItems.cpp
//! @brief     Implements FormFactorItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/FormFactorItems.h"
#include "Core/Basics/Units.h"
#include "Core/includeIncludes/FormFactors.h"

/* ------------------------------------------------ */

const QString AnisoPyramidItem::P_LENGTH("Length");
const QString AnisoPyramidItem::P_WIDTH("Width");
const QString AnisoPyramidItem::P_HEIGHT("Height");
const QString AnisoPyramidItem::P_ALPHA("Alpha");

AnisoPyramidItem::AnisoPyramidItem() : FormFactorItem("AnisoPyramid")
{
    setToolTip("A truncated pyramid with a rectangular base");
    addProperty(P_LENGTH, 20.0)->setToolTip("Length of the rectangular base in nanometers");
    addProperty(P_WIDTH, 16.0)->setToolTip("Width of the rectangular base in nanometers");
    addProperty(P_HEIGHT, 13.0)->setToolTip("Height of pyramid in nanometers");
    addProperty(P_ALPHA, 60.0)->setToolTip("Dihedral angle in degrees between base and facet");
}

std::unique_ptr<IFormFactor> AnisoPyramidItem::createFormFactor() const
{
    return std::make_unique<FormFactorAnisoPyramid>(
        getItemValue(P_LENGTH).toDouble(), getItemValue(P_WIDTH).toDouble(),
        getItemValue(P_HEIGHT).toDouble(), getItemValue(P_ALPHA).toDouble() * Units::degree);
}

/* ------------------------------------------------ */

const QString BarGaussItem::P_LENGTH("Length");
const QString BarGaussItem::P_WIDTH("Width");
const QString BarGaussItem::P_HEIGHT("Height");

BarGaussItem::BarGaussItem() : FormFactorItem("BarGauss")
{
    setToolTip("Rectangular cuboid");
    addProperty(P_LENGTH, 20.0)->setToolTip("Length of the base in nanometers");
    addProperty(P_WIDTH, 16.0)->setToolTip("Width of the base in nanometers");
    addProperty(P_HEIGHT, 13.0)->setToolTip("Height of the box in nanometers");
}

std::unique_ptr<IFormFactor> BarGaussItem::createFormFactor() const
{
    return std::make_unique<FormFactorBarGauss>(getItemValue(P_LENGTH).toDouble(),
                                                getItemValue(P_WIDTH).toDouble(),
                                                getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString BarLorentzItem::P_LENGTH("Length");
const QString BarLorentzItem::P_WIDTH("Width");
const QString BarLorentzItem::P_HEIGHT("Height");

BarLorentzItem::BarLorentzItem() : FormFactorItem("BarLorentz")
{
    setToolTip("Rectangular cuboid");
    addProperty(P_LENGTH, 20.0)->setToolTip("Length of the base in nanometers");
    addProperty(P_WIDTH, 16.0)->setToolTip("Width of the base in nanometers");
    addProperty(P_HEIGHT, 13.0)->setToolTip("Height of the box in nanometers");
}

std::unique_ptr<IFormFactor> BarLorentzItem::createFormFactor() const
{
    return std::make_unique<FormFactorBarLorentz>(getItemValue(P_LENGTH).toDouble(),
                                                  getItemValue(P_WIDTH).toDouble(),
                                                  getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString BoxItem::P_LENGTH("Length");
const QString BoxItem::P_WIDTH("Width");
const QString BoxItem::P_HEIGHT("Height");

BoxItem::BoxItem() : FormFactorItem("Box")
{
    setToolTip("Rectangular cuboid");
    addProperty(P_LENGTH, 20.0)->setToolTip("Length of the base in nanometers");
    addProperty(P_WIDTH, 16.0)->setToolTip("Width of the base in nanometers");
    addProperty(P_HEIGHT, 13.0)->setToolTip("Height of the box in nanometers");
}

std::unique_ptr<IFormFactor> BoxItem::createFormFactor() const
{
    return std::make_unique<FormFactorBox>(getItemValue(P_LENGTH).toDouble(),
                                           getItemValue(P_WIDTH).toDouble(),
                                           getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString ConeItem::P_RADIUS("Radius");
const QString ConeItem::P_HEIGHT("Height");
const QString ConeItem::P_ALPHA("Alpha");

ConeItem::ConeItem() : FormFactorItem("Cone")
{
    setToolTip("Truncated cone with circular base");
    addProperty(P_RADIUS, 10.0)->setToolTip("Radius of the base in nanometers");
    addProperty(P_HEIGHT, 13.0)->setToolTip("Height of the cone in nanometers");
    addProperty(P_ALPHA, 60.0)
        ->setToolTip("Angle between the base and the side surface in degrees");
}

std::unique_ptr<IFormFactor> ConeItem::createFormFactor() const
{
    return std::make_unique<FormFactorCone>(getItemValue(P_RADIUS).toDouble(),
                                            getItemValue(P_HEIGHT).toDouble(),
                                            getItemValue(P_ALPHA).toDouble() * Units::degree);
}

/* ------------------------------------------------ */

const QString Cone6Item::P_BASEEDGE("BaseEdge");
const QString Cone6Item::P_HEIGHT("Height");
const QString Cone6Item::P_ALPHA("Alpha");

Cone6Item::Cone6Item() : FormFactorItem("Cone6")
{
    setToolTip("A truncated pyramid, based on a regular hexagon");
    addProperty(P_BASEEDGE, 10.0)->setToolTip("Edge of the regular hexagonal base in nanometers");
    addProperty(P_HEIGHT, 13.0)->setToolTip("Height of a truncated pyramid in nanometers");
    addProperty(P_ALPHA, 60.0)->setToolTip("Dihedral angle in degrees between base and facet");
}

std::unique_ptr<IFormFactor> Cone6Item::createFormFactor() const
{
    return std::make_unique<FormFactorCone6>(getItemValue(P_BASEEDGE).toDouble(),
                                             getItemValue(P_HEIGHT).toDouble(),
                                             getItemValue(P_ALPHA).toDouble() * Units::degree);
}

/* ------------------------------------------------ */

const QString CuboctahedronItem::P_LENGTH("Length");
const QString CuboctahedronItem::P_HEIGHT("Height");
const QString CuboctahedronItem::P_HEIGHT_RATIO("HeightRatio");
const QString CuboctahedronItem::P_ALPHA("Alpha");

CuboctahedronItem::CuboctahedronItem() : FormFactorItem("Cuboctahedron")
{
    setToolTip("Compound of two truncated pyramids with a common square base \n"
               "and opposite orientations");
    addProperty(P_LENGTH, 20.0)->setToolTip("Side length of the common square base in nanometers");
    addProperty(P_HEIGHT, 13.0)->setToolTip("Height of the lower pyramid in nanometers");
    addProperty(P_HEIGHT_RATIO, 0.7)
        ->setLimits(RealLimits::lowerLimited(0.0))
        .setToolTip("Ratio of heights of top to bottom pyramids");
    addProperty(P_ALPHA, 60.0)->setToolTip("Dihedral angle in degrees between base and facets");
}

std::unique_ptr<IFormFactor> CuboctahedronItem::createFormFactor() const
{
    return std::make_unique<FormFactorCuboctahedron>(
        getItemValue(P_LENGTH).toDouble(), getItemValue(P_HEIGHT).toDouble(),
        getItemValue(P_HEIGHT_RATIO).toDouble(), getItemValue(P_ALPHA).toDouble() * Units::degree);
}

/* ------------------------------------------------ */

const QString CylinderItem::P_RADIUS("Radius");
const QString CylinderItem::P_HEIGHT("Height");

CylinderItem::CylinderItem() : FormFactorItem("Cylinder")
{
    setToolTip("Cylinder with a circular base");
    addProperty(P_RADIUS, 8.0)->setToolTip("Radius of the circular base in nanometers");
    addProperty(P_HEIGHT, 16.0)->setToolTip("Height of the cylinder in nanometers");
}

std::unique_ptr<IFormFactor> CylinderItem::createFormFactor() const
{
    return std::make_unique<FormFactorCylinder>(getItemValue(P_RADIUS).toDouble(),
                                                getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString DodecahedronItem::P_EDGE("Edge");

DodecahedronItem::DodecahedronItem() : FormFactorItem("Dodecahedron")
{
    setToolTip("Dodecahedron");
    addProperty(P_EDGE, 10.0)->setToolTip("Length of the edge in nanometers");
}

std::unique_ptr<IFormFactor> DodecahedronItem::createFormFactor() const
{
    return std::make_unique<FormFactorDodecahedron>(getItemValue(P_EDGE).toDouble());
}

/* ------------------------------------------------ */

const QString DotItem::P_RADIUS("Radius");

DotItem::DotItem() : FormFactorItem("Dot")
{
    setToolTip("A dot, with constant formfactor F(q)=4pi/3 R^3");
    addProperty(P_RADIUS, 8.0)->setToolTip("Radius of reference sphere in nanometers");
}

std::unique_ptr<IFormFactor> DotItem::createFormFactor() const
{
    return std::make_unique<FormFactorDot>(getItemValue(P_RADIUS).toDouble());
}

/* ------------------------------------------------ */

const QString EllipsoidalCylinderItem::P_RADIUS_X("RadiusX");
const QString EllipsoidalCylinderItem::P_RADIUS_Y("RadiusY");
const QString EllipsoidalCylinderItem::P_HEIGHT("Height");

EllipsoidalCylinderItem::EllipsoidalCylinderItem() : FormFactorItem("EllipsoidalCylinder")
{
    setToolTip("Cylinder with an ellipse cross section");
    addProperty(P_RADIUS_X, 8.0)
        ->setToolTip("Radius of the ellipse base in the x-direction, in nanometers");
    addProperty(P_RADIUS_Y, 13.0)
        ->setToolTip("Radius of the ellipse base in the y-direction, in nanometers");
    addProperty(P_HEIGHT, 16.0)->setToolTip("Height of the ellipsoidal cylinder in nanometers");
}

std::unique_ptr<IFormFactor> EllipsoidalCylinderItem::createFormFactor() const
{
    return std::make_unique<FormFactorEllipsoidalCylinder>(getItemValue(P_RADIUS_X).toDouble(),
                                                           getItemValue(P_RADIUS_Y).toDouble(),
                                                           getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString FullSphereItem::P_RADIUS("Radius");

FullSphereItem::FullSphereItem() : FormFactorItem("FullSphere")
{
    setToolTip("Full sphere");
    addProperty(P_RADIUS, 8.0)->setToolTip("Radius of the sphere in nanometers");
}

std::unique_ptr<IFormFactor> FullSphereItem::createFormFactor() const
{
    return std::make_unique<FormFactorFullSphere>(getItemValue(P_RADIUS).toDouble());
}

/* ------------------------------------------------ */

const QString FullSpheroidItem::P_RADIUS("Radius");
const QString FullSpheroidItem::P_HEIGHT("Height");

FullSpheroidItem::FullSpheroidItem() : FormFactorItem("FullSpheroid")
{
    setToolTip("Full spheroid, generated by rotating an ellipse around the vertical axis");
    addProperty(P_RADIUS, 10.0)->setToolTip("Radius of the circular cross section in nanometers");
    addProperty(P_HEIGHT, 13.0)->setToolTip("Height of the full spheroid in nanometers");
}

std::unique_ptr<IFormFactor> FullSpheroidItem::createFormFactor() const
{
    return std::make_unique<FormFactorFullSpheroid>(getItemValue(P_RADIUS).toDouble(),
                                                    getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString HemiEllipsoidItem::P_RADIUS_X("RadiusX");
const QString HemiEllipsoidItem::P_RADIUS_Y("RadiusY");
const QString HemiEllipsoidItem::P_HEIGHT("Height");

HemiEllipsoidItem::HemiEllipsoidItem() : FormFactorItem("HemiEllipsoid")
{
    setToolTip("An horizontally oriented ellipsoid, truncated at the central plane");
    addProperty(P_RADIUS_X, 10.0)
        ->setToolTip("Radius of the ellipse base in the x-direction, in nanometers");
    addProperty(P_RADIUS_Y, 6.0)
        ->setToolTip("Radius of the ellipse base in the y-direction, in nanometers");
    addProperty(P_HEIGHT, 8.0)->setToolTip("Height of the hemi ellipsoid in nanometers");
}

std::unique_ptr<IFormFactor> HemiEllipsoidItem::createFormFactor() const
{
    return std::make_unique<FormFactorHemiEllipsoid>(getItemValue(P_RADIUS_X).toDouble(),
                                                     getItemValue(P_RADIUS_Y).toDouble(),
                                                     getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString IcosahedronItem::P_EDGE("Edge");

IcosahedronItem::IcosahedronItem() : FormFactorItem("Icosahedron")
{
    setToolTip("Icosahedron");
    addProperty(P_EDGE, 10.0)->setToolTip("Length of the edge in nanometers");
}

std::unique_ptr<IFormFactor> IcosahedronItem::createFormFactor() const
{
    return std::make_unique<FormFactorIcosahedron>(getItemValue(P_EDGE).toDouble());
}

/* ------------------------------------------------ */

const QString Prism3Item::P_BASEEDGE("BaseEdge");
const QString Prism3Item::P_HEIGHT("Height");

Prism3Item::Prism3Item() : FormFactorItem("Prism3")
{
    setToolTip("Prism with an equilaterial triangle base");
    addProperty(P_BASEEDGE, 10.0)->setToolTip("Length of the base edge in nanometers");
    addProperty(P_HEIGHT, 13.0)->setToolTip("Height in nanometers");
}

std::unique_ptr<IFormFactor> Prism3Item::createFormFactor() const
{
    return std::make_unique<FormFactorPrism3>(getItemValue(P_BASEEDGE).toDouble(),
                                              getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString Prism6Item::P_BASEEDGE("BaseEdge");
const QString Prism6Item::P_HEIGHT("Height");

Prism6Item::Prism6Item() : FormFactorItem("Prism6")
{
    setToolTip("Prism with a regular hexagonal base");
    addProperty(P_BASEEDGE, 5.0)->setToolTip("Length of the hexagonal base in nanometers");
    addProperty(P_HEIGHT, 11.0)->setToolTip("Height in nanometers");
}

std::unique_ptr<IFormFactor> Prism6Item::createFormFactor() const
{
    return std::make_unique<FormFactorPrism6>(getItemValue(P_BASEEDGE).toDouble(),
                                              getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString PyramidItem::P_BASEEDGE("BaseEdge");
const QString PyramidItem::P_HEIGHT("Height");
const QString PyramidItem::P_ALPHA("Alpha");

PyramidItem::PyramidItem() : FormFactorItem("Pyramid")
{
    setToolTip("Truncated pyramid with a square base");
    addProperty(P_BASEEDGE, 18.0)->setToolTip("Length of the square base in nanometers");
    addProperty(P_HEIGHT, 13.0)->setToolTip("Height of the pyramid in nanometers");
    addProperty(P_ALPHA, 60.0)
        ->setToolTip("Dihedral angle between the base and a side face in degrees");
}

std::unique_ptr<IFormFactor> PyramidItem::createFormFactor() const
{
    return std::make_unique<FormFactorPyramid>(getItemValue(P_BASEEDGE).toDouble(),
                                               getItemValue(P_HEIGHT).toDouble(),
                                               getItemValue(P_ALPHA).toDouble() * Units::degree);
}

/* ------------------------------------------------ */

const QString CosineRippleBoxItem::P_LENGTH("Length");
const QString CosineRippleBoxItem::P_WIDTH("Width");
const QString CosineRippleBoxItem::P_HEIGHT("Height");

CosineRippleBoxItem::CosineRippleBoxItem() : FormFactorItem("CosineRippleBox")
{
    setToolTip("Particle with a cosine profile and a rectangular base");
    addProperty(P_LENGTH, 27.0)->setToolTip("Length of the rectangular base in nanometers");
    addProperty(P_WIDTH, 20.0)->setToolTip("Width of the rectangular base in nanometers");
    addProperty(P_HEIGHT, 14.0)->setToolTip("Height of the ripple in nanometers");
}

std::unique_ptr<IFormFactor> CosineRippleBoxItem::createFormFactor() const
{
    return std::make_unique<FormFactorCosineRippleBox>(getItemValue(P_LENGTH).toDouble(),
                                                       getItemValue(P_WIDTH).toDouble(),
                                                       getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString CosineRippleGaussItem::P_LENGTH("Length");
const QString CosineRippleGaussItem::P_WIDTH("Width");
const QString CosineRippleGaussItem::P_HEIGHT("Height");

CosineRippleGaussItem::CosineRippleGaussItem() : FormFactorItem("CosineRippleGauss")
{
    setToolTip("Particle with a cosine profile and a rectangular base");
    addProperty(P_LENGTH, 27.0)->setToolTip("Length of the rectangular base in nanometers");
    addProperty(P_WIDTH, 20.0)->setToolTip("Width of the rectangular base in nanometers");
    addProperty(P_HEIGHT, 14.0)->setToolTip("Height of the ripple in nanometers");
}

std::unique_ptr<IFormFactor> CosineRippleGaussItem::createFormFactor() const
{
    return std::make_unique<FormFactorCosineRippleGauss>(getItemValue(P_LENGTH).toDouble(),
                                                         getItemValue(P_WIDTH).toDouble(),
                                                         getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString CosineRippleLorentzItem::P_LENGTH("Length");
const QString CosineRippleLorentzItem::P_WIDTH("Width");
const QString CosineRippleLorentzItem::P_HEIGHT("Height");

CosineRippleLorentzItem::CosineRippleLorentzItem() : FormFactorItem("CosineRippleLorentz")
{
    setToolTip("Particle with a cosine profile and a rectangular base");
    addProperty(P_LENGTH, 27.0)->setToolTip("Length of the rectangular base in nanometers");
    addProperty(P_WIDTH, 20.0)->setToolTip("Width of the rectangular base in nanometers");
    addProperty(P_HEIGHT, 14.0)->setToolTip("Height of the ripple in nanometers");
}

std::unique_ptr<IFormFactor> CosineRippleLorentzItem::createFormFactor() const
{
    return std::make_unique<FormFactorCosineRippleLorentz>(getItemValue(P_LENGTH).toDouble(),
                                                           getItemValue(P_WIDTH).toDouble(),
                                                           getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString SawtoothRippleBoxItem::P_LENGTH("Length");
const QString SawtoothRippleBoxItem::P_WIDTH("Width");
const QString SawtoothRippleBoxItem::P_HEIGHT("Height");
const QString SawtoothRippleBoxItem::P_ASYMMETRY("AsymmetryLength");

SawtoothRippleBoxItem::SawtoothRippleBoxItem() : FormFactorItem("SawtoothRippleBox")
{
    setToolTip("Particle with an asymmetric triangle profile and a rectangular base");
    addProperty(P_LENGTH, 36.0)->setToolTip("Length of the rectangular base in nanometers");
    addProperty(P_WIDTH, 25.0)->setToolTip("Width of the rectangular base in nanometers");
    addProperty(P_HEIGHT, 14.0)->setToolTip("Height of the ripple in nanometers");
    addProperty(P_ASYMMETRY, 3.0)
        ->setToolTip("Asymmetry length of the triangular profile in nanometers");
}

std::unique_ptr<IFormFactor> SawtoothRippleBoxItem::createFormFactor() const
{
    return std::make_unique<FormFactorSawtoothRippleBox>(
        getItemValue(P_LENGTH).toDouble(), getItemValue(P_WIDTH).toDouble(),
        getItemValue(P_HEIGHT).toDouble(), getItemValue(P_ASYMMETRY).toDouble());
}

/* ------------------------------------------------ */

const QString SawtoothRippleGaussItem::P_LENGTH("Length");
const QString SawtoothRippleGaussItem::P_WIDTH("Width");
const QString SawtoothRippleGaussItem::P_HEIGHT("Height");
const QString SawtoothRippleGaussItem::P_ASYMMETRY("AsymmetryLength");

SawtoothRippleGaussItem::SawtoothRippleGaussItem() : FormFactorItem("SawtoothRippleGauss")
{
    setToolTip("Particle with an asymmetric triangle profile and a rectangular base");
    addProperty(P_LENGTH, 36.0)->setToolTip("Length of the rectangular base in nanometers");
    addProperty(P_WIDTH, 25.0)->setToolTip("Width of the rectangular base in nanometers");
    addProperty(P_HEIGHT, 14.0)->setToolTip("Height of the ripple in nanometers");
    addProperty(P_ASYMMETRY, 3.0)
        ->setToolTip("Asymmetry length of the triangular profile in nanometers");
}

std::unique_ptr<IFormFactor> SawtoothRippleGaussItem::createFormFactor() const
{
    return std::make_unique<FormFactorSawtoothRippleGauss>(
        getItemValue(P_LENGTH).toDouble(), getItemValue(P_WIDTH).toDouble(),
        getItemValue(P_HEIGHT).toDouble(), getItemValue(P_ASYMMETRY).toDouble());
}

/* ------------------------------------------------ */

const QString SawtoothRippleLorentzItem::P_LENGTH("Length");
const QString SawtoothRippleLorentzItem::P_WIDTH("Width");
const QString SawtoothRippleLorentzItem::P_HEIGHT("Height");
const QString SawtoothRippleLorentzItem::P_ASYMMETRY("AsymmetryLength");

SawtoothRippleLorentzItem::SawtoothRippleLorentzItem() : FormFactorItem("SawtoothRippleLorentz")
{
    setToolTip("Particle with an asymmetric triangle profile and a rectangular base");
    addProperty(P_LENGTH, 36.0)->setToolTip("Length of the rectangular base in nanometers");
    addProperty(P_WIDTH, 25.0)->setToolTip("Width of the rectangular base in nanometers");
    addProperty(P_HEIGHT, 14.0)->setToolTip("Height of the ripple in nanometers");
    addProperty(P_ASYMMETRY, 3.0)
        ->setToolTip("Asymmetry length of the triangular profile in nanometers");
}

std::unique_ptr<IFormFactor> SawtoothRippleLorentzItem::createFormFactor() const
{
    return std::make_unique<FormFactorSawtoothRippleLorentz>(
        getItemValue(P_LENGTH).toDouble(), getItemValue(P_WIDTH).toDouble(),
        getItemValue(P_HEIGHT).toDouble(), getItemValue(P_ASYMMETRY).toDouble());
}

/* ------------------------------------------------ */

const QString TetrahedronItem::P_BASEEDGE("BaseEdge");
const QString TetrahedronItem::P_HEIGHT("Height");
const QString TetrahedronItem::P_ALPHA("Alpha");

TetrahedronItem::TetrahedronItem() : FormFactorItem("Tetrahedron")
{
    setToolTip("A truncated tethrahedron");
    addProperty(P_BASEEDGE, 15.0)
        ->setToolTip("Length of one edge of the equilateral triangular base in nanometers");
    addProperty(P_HEIGHT, 6.0)->setToolTip("Height of the tetrahedron in nanometers");
    addProperty(P_ALPHA, 60.0)->setToolTip("Dihedral angle in degrees between base and facet");
}

std::unique_ptr<IFormFactor> TetrahedronItem::createFormFactor() const
{
    return std::make_unique<FormFactorTetrahedron>(
        getItemValue(P_BASEEDGE).toDouble(), getItemValue(P_HEIGHT).toDouble(),
        getItemValue(P_ALPHA).toDouble() * Units::degree);
}

/* ------------------------------------------------ */

const QString TruncatedCubeItem::P_LENGTH("Length");
const QString TruncatedCubeItem::P_REMOVED_LENGTH("RemovedLength");

TruncatedCubeItem::TruncatedCubeItem() : FormFactorItem("TruncatedCube")
{
    setToolTip("A cube whose eight vertices have been removed");
    addProperty(P_LENGTH, 15.0)->setToolTip("Length of the full cube's edge in nanometers");
    addProperty(P_REMOVED_LENGTH, 6.0)
        ->setToolTip("Removed length from each edge of the cube in nanometers");
}

std::unique_ptr<IFormFactor> TruncatedCubeItem::createFormFactor() const
{
    return std::make_unique<FormFactorTruncatedCube>(getItemValue(P_LENGTH).toDouble(),
                                                     getItemValue(P_REMOVED_LENGTH).toDouble());
}

/* ------------------------------------------------ */

const QString TruncatedSphereItem::P_RADIUS("Radius");
const QString TruncatedSphereItem::P_HEIGHT("Height");
const QString TruncatedSphereItem::P_REMOVED_TOP("DeltaHeight");

TruncatedSphereItem::TruncatedSphereItem() : FormFactorItem("TruncatedSphere")
{
    setToolTip("Spherical dome");
    addProperty(P_RADIUS, 5.0)->setToolTip("Radius of the truncated sphere in nanometers");
    addProperty(P_HEIGHT, 7.0)->setToolTip("Height of the truncated sphere in nanometers");
    addProperty(P_REMOVED_TOP, 0.0)->setToolTip("Height of the removed top cap in nanometers");
}

std::unique_ptr<IFormFactor> TruncatedSphereItem::createFormFactor() const
{
    return std::make_unique<FormFactorTruncatedSphere>(getItemValue(P_RADIUS).toDouble(),
                                                       getItemValue(P_HEIGHT).toDouble(),
                                                       getItemValue(P_REMOVED_TOP).toDouble());
}

/* ------------------------------------------------ */

const QString TruncatedSpheroidItem::P_RADIUS("Radius");
const QString TruncatedSpheroidItem::P_HEIGHT("Height");
const QString TruncatedSpheroidItem::P_HFC("HeightFlattening");
const QString TruncatedSpheroidItem::P_REMOVED_TOP("DeltaHeight");

TruncatedSpheroidItem::TruncatedSpheroidItem() : FormFactorItem("TruncatedSpheroid")
{
    setToolTip("Spheroidal dome");
    addProperty(P_RADIUS, 7.5)->setToolTip("Radius of the truncated spheroid in nanometers");
    addProperty(P_HEIGHT, 9.0)->setToolTip("Height of the truncated spheroid in nanometers");
    addProperty(P_HFC, 1.2)
        ->setToolTip("Ratio of the height of the corresponding full spheroid to its diameter");
    addProperty(P_REMOVED_TOP, 0.0)->setToolTip("Height of the removed top cap in nanometers");
}

std::unique_ptr<IFormFactor> TruncatedSpheroidItem::createFormFactor() const
{
    return std::make_unique<FormFactorTruncatedSpheroid>(
        getItemValue(P_RADIUS).toDouble(), getItemValue(P_HEIGHT).toDouble(),
        getItemValue(P_HFC).toDouble(), getItemValue(P_REMOVED_TOP).toDouble());
}
