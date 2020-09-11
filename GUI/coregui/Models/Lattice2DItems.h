// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/Lattice2DItems.h
//! @brief     Defines classes Lattice2DItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_LATTICE2DITEMS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_LATTICE2DITEMS_H

#include "GUI/coregui/Models/SessionItem.h"
class Lattice2D;

class BA_CORE_API_ Lattice2DItem : public SessionItem
{
public:
    static const QString P_LATTICE_ROTATION_ANGLE;
    explicit Lattice2DItem(const QString& modelType);
    virtual std::unique_ptr<Lattice2D> createLattice() const = 0;
    double unitCellArea() const;
};

class BA_CORE_API_ BasicLatticeItem : public Lattice2DItem
{
public:
    static const QString P_LATTICE_LENGTH1;
    static const QString P_LATTICE_LENGTH2;
    static const QString P_LATTICE_ANGLE;
    BasicLatticeItem();
    std::unique_ptr<Lattice2D> createLattice() const;
};

class BA_CORE_API_ SquareLatticeItem : public Lattice2DItem
{
public:
    static const QString P_LATTICE_LENGTH;
    SquareLatticeItem();
    std::unique_ptr<Lattice2D> createLattice() const;
};

class BA_CORE_API_ HexagonalLatticeItem : public Lattice2DItem
{
public:
    static const QString P_LATTICE_LENGTH;
    HexagonalLatticeItem();
    std::unique_ptr<Lattice2D> createLattice() const;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_LATTICE2DITEMS_H
