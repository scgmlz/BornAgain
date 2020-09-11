// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Lattice/Lattice2D.h
//! @brief     Defines classes of Lattice2D family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_LATTICE_LATTICE2D_H
#define BORNAGAIN_CORE_LATTICE_LATTICE2D_H

#include "Core/Basics/ICloneable.h"
#include "Core/Parametrization/INode.h"

class BA_CORE_API_ Lattice2D : public ICloneable, public INode
{
public:
    Lattice2D(const NodeMeta& meta, const std::vector<double>& PValues);
    explicit Lattice2D(double xi);

    virtual Lattice2D* clone() const = 0;

    struct ReciprocalBases {
        double m_asx, m_asy; //!< x,y coordinates of a*
        double m_bsx, m_bsy; //!< x,y coordinates of b*
    };

    virtual double length1() const = 0;
    virtual double length2() const = 0;
    virtual double latticeAngle() const = 0;
    virtual double unitCellArea() const = 0;

    double rotationAngle() const { return m_xi; }

    ReciprocalBases reciprocalBases() const;

    void setRotationEnabled(bool enabled);

protected:
    virtual void onChange();
    double m_xi;
};

class BA_CORE_API_ BasicLattice : public Lattice2D
{
public:
    BasicLattice(double length1, double length2, double angle, double xi);

    BasicLattice* clone() const;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    virtual double length1() const { return m_length1; }
    virtual double length2() const { return m_length2; }
    virtual double latticeAngle() const { return m_angle; }
    virtual double unitCellArea() const;

private:
    double m_length1, m_length2;
    double m_angle;
};

class BA_CORE_API_ SquareLattice : public Lattice2D
{
public:
    SquareLattice(double length, double xi = 0.0);

    SquareLattice* clone() const;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    virtual double length1() const { return m_length; }
    virtual double length2() const { return m_length; }
    virtual double latticeAngle() const;
    virtual double unitCellArea() const;

private:
    double m_length;
};

class BA_CORE_API_ HexagonalLattice : public Lattice2D
{
public:
    HexagonalLattice(double length, double xi);

    HexagonalLattice* clone() const;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    virtual double length1() const { return m_length; }
    virtual double length2() const { return m_length; }
    virtual double latticeAngle() const;
    virtual double unitCellArea() const;

private:
    double m_length;
};

#endif // BORNAGAIN_CORE_LATTICE_LATTICE2D_H
