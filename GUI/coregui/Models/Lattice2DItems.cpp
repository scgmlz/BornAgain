// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/Lattice2DItems.cpp
//! @brief     Implements classes Lattice2DItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/Lattice2DItems.h"
#include "Core/Basics/Units.h"
#include "Core/Lattice/Lattice2D.h"

namespace
{
const QString axis_rotation_tooltip =
    "Rotation of lattice with respect to x-axis of reference frame \n"
    "(beam direction) in degrees";
}

const QString Lattice2DItem::P_LATTICE_ROTATION_ANGLE = QString::fromStdString("Xi");

Lattice2DItem::Lattice2DItem(const QString& modelType) : SessionItem(modelType) {}

double Lattice2DItem::unitCellArea() const
{
    return createLattice()->unitCellArea();
}

const QString BasicLatticeItem::P_LATTICE_LENGTH1 = QString::fromStdString("LatticeLength1");
const QString BasicLatticeItem::P_LATTICE_LENGTH2 = QString::fromStdString("LatticeLength2");
const QString BasicLatticeItem::P_LATTICE_ANGLE = QString::fromStdString("Alpha");

BasicLatticeItem::BasicLatticeItem() : Lattice2DItem("BasicLattice")
{
    setToolTip("Two dimensional lattice");
    addProperty(P_LATTICE_LENGTH1, 20.0)
        ->setToolTip("Length of first lattice vector in nanometers");
    addProperty(P_LATTICE_LENGTH2, 20.0)
        ->setToolTip("Length of second lattice vector in nanometers");
    addProperty(P_LATTICE_ANGLE, 90.0)->setToolTip("Angle between lattice vectors in degrees");
    addProperty(Lattice2DItem::P_LATTICE_ROTATION_ANGLE, 0.0)->setToolTip(axis_rotation_tooltip);
}

std::unique_ptr<Lattice2D> BasicLatticeItem::createLattice() const
{
    return std::make_unique<BasicLattice>(
        getItemValue(P_LATTICE_LENGTH1).toDouble(), getItemValue(P_LATTICE_LENGTH2).toDouble(),
        Units::deg2rad(getItemValue(P_LATTICE_ANGLE).toDouble()),
        Units::deg2rad(getItemValue(Lattice2DItem::P_LATTICE_ROTATION_ANGLE).toDouble()));
}

// --------------------------------------------------------------------------------------------- //

const QString SquareLatticeItem::P_LATTICE_LENGTH = QString::fromStdString("LatticeLength");

SquareLatticeItem::SquareLatticeItem() : Lattice2DItem("SquareLattice")
{
    addProperty(P_LATTICE_LENGTH, 20.0)
        ->setToolTip("Length of first and second lattice vectors in nanometers");
    addProperty(Lattice2DItem::P_LATTICE_ROTATION_ANGLE, 0.0)->setToolTip(axis_rotation_tooltip);
}

std::unique_ptr<Lattice2D> SquareLatticeItem::createLattice() const
{
    return std::make_unique<SquareLattice>(
        getItemValue(P_LATTICE_LENGTH).toDouble(),
        Units::deg2rad(getItemValue(Lattice2DItem::P_LATTICE_ROTATION_ANGLE).toDouble()));
}

// --------------------------------------------------------------------------------------------- //

const QString HexagonalLatticeItem::P_LATTICE_LENGTH = QString::fromStdString("LatticeLength");

HexagonalLatticeItem::HexagonalLatticeItem() : Lattice2DItem("HexagonalLattice")
{
    addProperty(P_LATTICE_LENGTH, 20.0)
        ->setToolTip("Length of first and second lattice vectors in nanometers");
    addProperty(Lattice2DItem::P_LATTICE_ROTATION_ANGLE, 0.0)->setToolTip(axis_rotation_tooltip);
}

std::unique_ptr<Lattice2D> HexagonalLatticeItem::createLattice() const
{
    return std::make_unique<HexagonalLattice>(
        getItemValue(P_LATTICE_LENGTH).toDouble(),
        Units::deg2rad(getItemValue(Lattice2DItem::P_LATTICE_ROTATION_ANGLE).toDouble()));
}
