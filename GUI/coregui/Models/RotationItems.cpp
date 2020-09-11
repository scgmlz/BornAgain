// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/RotationItems.cpp
//! @brief     Implements class RotationItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/RotationItems.h"
#include "Core/Basics/Units.h"
#include "Core/Scattering/Rotations.h"

// ----------------------------------------------------------------------------

const QString XRotationItem::P_ANGLE = "Angle";

XRotationItem::XRotationItem() : RotationItem("XRotation")
{
    setToolTip("Particle rotation around x-axis");
    addProperty(P_ANGLE, 0.0)->setToolTip("Rotation angle around x-axis in degrees");
}

std::unique_ptr<IRotation> XRotationItem::createRotation() const
{
    double alpha = Units::deg2rad(getItemValue(P_ANGLE).toDouble());
    return std::make_unique<RotationX>(alpha);
}

// ----------------------------------------------------------------------------

const QString YRotationItem::P_ANGLE = "Angle";

YRotationItem::YRotationItem() : RotationItem("YRotation")
{
    setToolTip("Particle rotation around y-axis");
    addProperty(P_ANGLE, 0.0)->setToolTip("Rotation angle around y-axis in degrees");
}

std::unique_ptr<IRotation> YRotationItem::createRotation() const
{
    double alpha = Units::deg2rad(getItemValue(P_ANGLE).toDouble());
    return std::make_unique<RotationY>(alpha);
}

// ----------------------------------------------------------------------------

const QString ZRotationItem::P_ANGLE = "Angle";

ZRotationItem::ZRotationItem() : RotationItem("ZRotation")
{
    setToolTip("Particle rotation around z-axis");
    addProperty(P_ANGLE, 0.0)->setToolTip("Rotation angle around z-axis in degrees");
}

std::unique_ptr<IRotation> ZRotationItem::createRotation() const
{
    double alpha = Units::deg2rad(getItemValue(P_ANGLE).toDouble());
    return std::make_unique<RotationZ>(alpha);
}

// ----------------------------------------------------------------------------

const QString EulerRotationItem::P_ALPHA = "Alpha";
const QString EulerRotationItem::P_BETA = "Beta";
const QString EulerRotationItem::P_GAMMA = "Gamma";

EulerRotationItem::EulerRotationItem() : RotationItem("EulerRotation")
{
    setToolTip("Sequence of three rotations following Euler angles \n"
               "notation z-x'-z'");
    addProperty(P_ALPHA, 0.0)->setToolTip("First Euler anle in z-x'-z' sequence in degrees");
    addProperty(P_BETA, 0.0)->setToolTip("Second Euler anle in z-x'-z' sequence in degrees");
    addProperty(P_GAMMA, 0.0)->setToolTip("Third Euler anle in z-x'-z' sequence in degrees");
}

std::unique_ptr<IRotation> EulerRotationItem::createRotation() const
{
    double alpha = Units::deg2rad(getItemValue(P_ALPHA).toDouble());
    double beta = Units::deg2rad(getItemValue(P_BETA).toDouble());
    double gamma = Units::deg2rad(getItemValue(P_GAMMA).toDouble());
    return std::make_unique<RotationEuler>(alpha, beta, gamma);
}
