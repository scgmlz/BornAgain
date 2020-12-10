//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Aggregate/InterferenceFunctionFinite3DLattice.h
//! @brief     Defines class InterferenceFunctionFinite3DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTIONFINITE3DLATTICE_H
#define BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTIONFINITE3DLATTICE_H

#include "Sample/Aggregate/IInterferenceFunction.h"
#include "Sample/Lattice/Lattice3D.h"

//! Interference function of a finite 3D lattice.
//! @ingroup interference

class InterferenceFunctionFinite3DLattice : public IInterferenceFunction {
public:
    InterferenceFunctionFinite3DLattice(const Lattice3D& lattice, unsigned N_1, unsigned N_2,
                                        unsigned N_3);
    ~InterferenceFunctionFinite3DLattice() override;

    InterferenceFunctionFinite3DLattice* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    unsigned numberUnitCells1() const { return m_N_1; }
    unsigned numberUnitCells2() const { return m_N_2; }
    unsigned numberUnitCells3() const { return m_N_3; }

    const Lattice3D& lattice() const;

    bool supportsMultilayer() const override { return false; }

    std::vector<const INode*> getChildren() const override;

private:
    double iff_without_dw(const kvector_t q) const override;
    void setLattice(const Lattice3D& lattice);

    std::unique_ptr<Lattice3D> m_lattice;
    unsigned m_N_1, m_N_2, m_N_3; //!< Size of the finite lattice in lattice units
};

#endif // BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTIONFINITE3DLATTICE_H
