//  ************************************************************************************************
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
//  ************************************************************************************************

#include "GUI/coregui/Models/Lattice2DItems.h"
#include "Base/Const/Units.h"
#include "Sample/Lattice/Lattice2D.h"

namespace {
const QString axis_rotation_tooltip =
    "Rotation of lattice with respect to x-axis of reference frame \n"
    "(beam direction) in degrees";
}

const QString Lattice2DItem::P_LATTICE_ROTATION_ANGLE = QString::fromStdString("Xi");

Lattice2DItem::Lattice2DItem(const QString& modelType) : SessionItem(modelType) {}

double Lattice2DItem::unitCellArea() const {
    return createLattice()->unitCellArea();
}

const QString BasicLattice2DItem::P_LATTICE_LENGTH1 = QString::fromStdString("LatticeLength1");
const QString BasicLattice2DItem::P_LATTICE_LENGTH2 = QString::fromStdString("LatticeLength2");
const QString BasicLattice2DItem::P_LATTICE_ANGLE = QString::fromStdString("Alpha");

BasicLattice2DItem::BasicLattice2DItem() : Lattice2DItem("BasicLattice2D") {
    setToolTip("Two dimensional lattice");
    addProperty(P_LATTICE_LENGTH1, 20.0)
        ->setToolTip("Length of first lattice vector in nanometers");
    addProperty(P_LATTICE_LENGTH2, 20.0)
        ->setToolTip("Length of second lattice vector in nanometers");
    addProperty(P_LATTICE_ANGLE, 90.0)->setToolTip("Angle between lattice vectors in degrees");
    addProperty(Lattice2DItem::P_LATTICE_ROTATION_ANGLE, 0.0)->setToolTip(axis_rotation_tooltip);
}

std::unique_ptr<Lattice2D> BasicLattice2DItem::createLattice() const {
    return std::make_unique<BasicLattice2D>(
        getItemValue(P_LATTICE_LENGTH1).toDouble(), getItemValue(P_LATTICE_LENGTH2).toDouble(),
        Units::deg2rad(getItemValue(P_LATTICE_ANGLE).toDouble()),
        Units::deg2rad(getItemValue(Lattice2DItem::P_LATTICE_ROTATION_ANGLE).toDouble()));
}

// --------------------------------------------------------------------------------------------- //

const QString SquareLattice2DItem::P_LATTICE_LENGTH = QString::fromStdString("LatticeLength");

SquareLattice2DItem::SquareLattice2DItem() : Lattice2DItem("SquareLattice2D") {
    addProperty(P_LATTICE_LENGTH, 20.0)
        ->setToolTip("Length of first and second lattice vectors in nanometers");
    addProperty(Lattice2DItem::P_LATTICE_ROTATION_ANGLE, 0.0)->setToolTip(axis_rotation_tooltip);
}

std::unique_ptr<Lattice2D> SquareLattice2DItem::createLattice() const {
    return std::make_unique<SquareLattice2D>(
        getItemValue(P_LATTICE_LENGTH).toDouble(),
        Units::deg2rad(getItemValue(Lattice2DItem::P_LATTICE_ROTATION_ANGLE).toDouble()));
}

// --------------------------------------------------------------------------------------------- //

const QString HexagonalLattice2DItem::P_LATTICE_LENGTH = QString::fromStdString("LatticeLength");

HexagonalLattice2DItem::HexagonalLattice2DItem() : Lattice2DItem("HexagonalLattice2D") {
    addProperty(P_LATTICE_LENGTH, 20.0)
        ->setToolTip("Length of first and second lattice vectors in nanometers");
    addProperty(Lattice2DItem::P_LATTICE_ROTATION_ANGLE, 0.0)->setToolTip(axis_rotation_tooltip);
}

std::unique_ptr<Lattice2D> HexagonalLattice2DItem::createLattice() const {
    return std::make_unique<HexagonalLattice2D>(
        getItemValue(P_LATTICE_LENGTH).toDouble(),
        Units::deg2rad(getItemValue(Lattice2DItem::P_LATTICE_ROTATION_ANGLE).toDouble()));
}
