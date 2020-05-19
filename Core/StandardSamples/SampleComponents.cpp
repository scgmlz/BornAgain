// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/SampleComponents.cpp
//! @brief     Implements sample components for complex sample builders.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SampleComponents.h"
#include "BornAgainNamespace.h"
#include "HardParticles.h"
#include "Units.h"

// ************************************************************************** //
FTDistribution2DComponents::FTDistribution2DComponents()
// ************************************************************************** //
{
    add(BornAgain::FTDistribution2DCauchyType, new FTDistribution2DCauchy(0.5, 1.0));
    add(BornAgain::FTDistribution2DGaussType, new FTDistribution2DGauss(0.5, 1.0));
    add(BornAgain::FTDistribution2DGateType, new FTDistribution2DGate(0.5, 1.0));
    add(BornAgain::FTDistribution2DConeType, new FTDistribution2DCone(0.5, 1.0));
    add(BornAgain::FTDistribution2DVoigtType, new FTDistribution2DVoigt(0.5, 1.0, 0.2));
}

// ************************************************************************** //
FormFactorComponents::FormFactorComponents()
// ************************************************************************** //
{
    add(BornAgain::FFAnisoPyramidType,
        new FormFactorAnisoPyramid(10.0, 20.0, 5.0, Units::deg2rad(54.73)));

    add(BornAgain::FFBoxType, new FormFactorBox(10.0, 20.0, 5.0));

    add(BornAgain::FFConeType, new FormFactorCone(5.0, 6.0, Units::deg2rad(54.73)));

    add(BornAgain::FFCone6Type,
        new FormFactorCone6(2. / sqrt(3.) * 5.0, 5.0, Units::deg2rad(54.73)));

    add(BornAgain::FFCuboctahedronType,
        new FormFactorCuboctahedron(10.0, 5.0, 1.0, Units::deg2rad(54.73)));

    add(BornAgain::FFCylinderType, new FormFactorCylinder(5.0, 10.0));

    add(BornAgain::FFDodecahedronType, new FormFactorDodecahedron(5.0));

    add(BornAgain::FFDotType, new FormFactorDot(5.0));

    add(BornAgain::FFEllipsoidalCylinderType, new FormFactorEllipsoidalCylinder(5.0, 10.0, 15.0));

    add(BornAgain::FFFullSphereType, new FormFactorFullSphere(5.0));

    add(BornAgain::FFFullSpheroidType, new FormFactorFullSpheroid(5.0, 10.0));

    add(BornAgain::FFHemiEllipsoidType, new FormFactorHemiEllipsoid(5.0, 10.0, 15.0));

    add(BornAgain::FFIcosahedronType, new FormFactorIcosahedron(10.0));

    add(BornAgain::FFPrism3Type, new FormFactorPrism3(10.0, 5.0));

    add(BornAgain::FFPrism6Type, new FormFactorPrism6(2. / sqrt(3.) * 5.0, 5.0));

    add(BornAgain::FFPyramidType, new FormFactorPyramid(10.0, 5.0, Units::deg2rad(54.73)));

    add(BornAgain::FFRipple1BoxType, new FormFactorRipple1Box(100.0, 20.0, 4.0));

    add(BornAgain::FFRipple2Type, new FormFactorRipple2(100.0, 20.0, 4.0, 0.0));

    add(BornAgain::FFTetrahedronType, new FormFactorTetrahedron(10.0, 4.0, Units::deg2rad(54.73)));

    add(BornAgain::FFTruncatedCubeType, new FormFactorTruncatedCube(15.0, 6.0));

    add(BornAgain::FFTruncatedSphereType, new FormFactorTruncatedSphere(5.0, 7.0));

    add(BornAgain::FFTruncatedSpheroidType, new FormFactorTruncatedSpheroid(5.0, 7.0, 1.0));
}
