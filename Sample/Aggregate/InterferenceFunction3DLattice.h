//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Aggregate/InterferenceFunction3DLattice.h
//! @brief     Defines class InterferenceFunction3DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTION3DLATTICE_H
#define BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTION3DLATTICE_H

#include "Sample/Aggregate/IInterferenceFunction.h"
#include "Sample/Lattice/Lattice3D.h"

class IPeakShape;

//! Interference function of a 3D lattice.
//! @ingroup interference

class InterferenceFunction3DLattice : public IInterferenceFunction {
public:
    InterferenceFunction3DLattice(const Lattice3D& lattice);
    ~InterferenceFunction3DLattice() override;

    InterferenceFunction3DLattice* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    void setPeakShape(const IPeakShape& peak_shape);

    const Lattice3D& lattice() const;

    bool supportsMultilayer() const override { return false; }

    std::vector<const INode*> getChildren() const override;

    void onChange() override;

private:
    double iff_without_dw(const kvector_t q) const override;
    void initRecRadius();

    Lattice3D m_lattice; // TODO unique_ptr as in other InterferenceFunction%s
    std::unique_ptr<IPeakShape> m_peak_shape;
    double m_rec_radius; //!< radius in reciprocal space defining the nearest q vectors to use
};

#endif // BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTION3DLATTICE_H
