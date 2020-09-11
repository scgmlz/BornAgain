// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunctionFinite3DLattice.h
//! @brief     Defines class InterferenceFunctionFinite3DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTIONFINITE3DLATTICE_H
#define BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTIONFINITE3DLATTICE_H

#include "Core/Aggregate/IInterferenceFunction.h"
#include "Core/Lattice/Lattice.h"

//! Interference function of a finite 3D lattice.
//! @ingroup interference

class BA_CORE_API_ InterferenceFunctionFinite3DLattice : public IInterferenceFunction
{
public:
    InterferenceFunctionFinite3DLattice(const Lattice& lattice, unsigned N_1, unsigned N_2,
                                        unsigned N_3);
    ~InterferenceFunctionFinite3DLattice() final;

    InterferenceFunctionFinite3DLattice* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    unsigned numberUnitCells1() const { return m_N_1; }
    unsigned numberUnitCells2() const { return m_N_2; }
    unsigned numberUnitCells3() const { return m_N_3; }

    const Lattice& lattice() const;

    bool supportsMultilayer() const override final { return false; }

    std::vector<const INode*> getChildren() const override final;

private:
    double iff_without_dw(const kvector_t q) const override final;
    void setLattice(const Lattice& lattice);

    std::unique_ptr<Lattice> mP_lattice;
    unsigned m_N_1, m_N_2, m_N_3; //!< Size of the finite lattice in lattice units
};

#endif // BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTIONFINITE3DLATTICE_H
