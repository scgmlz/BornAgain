// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Lattice/ILatticeOrientation.h
//! @brief     Defines interface ILatticeOrientation and subclasses.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ILATTICEORIENTATION_H
#define ILATTICEORIENTATION_H

#include "Lattice.h"
#include "Transform3D.h"

class BA_CORE_API_ ILatticeOrientation
{
public:
    virtual ~ILatticeOrientation();

    virtual ILatticeOrientation* clone() const=0;

    virtual void usePrimitiveLattice(const Lattice& lattice) =0;

    virtual Transform3D transformationMatrix() const=0;
};

//! MillerIndex represents arbitrary directions in reciprocal space by allowing floating point
//! index values
struct BA_CORE_API_ MillerIndex {
    MillerIndex(double h_, double k_, double l_);
    double h, k, l;
};

class BA_CORE_API_ MillerIndexOrientation : public ILatticeOrientation
{
public:
    enum QComponent { QX, QY, QZ };

    MillerIndexOrientation(QComponent q1, MillerIndex index1,
                           QComponent q2, MillerIndex index2);
    ~MillerIndexOrientation() override;

    MillerIndexOrientation* clone() const override;

    void usePrimitiveLattice(const Lattice& lattice) override;

    Transform3D transformationMatrix() const override;
private:
    bool checkAlignment() const;
    Lattice m_prim_lattice;
    QComponent m_q1, m_q2;
    MillerIndex m_ind1, m_ind2;
};

#endif // ILATTICEORIENTATION_H
