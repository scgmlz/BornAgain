//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Aggregate/InterferenceFunction1DLattice.h
//! @brief     Defines class InterferenceFunction1DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTION1DLATTICE_H
#define BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTION1DLATTICE_H

#include "Sample/Aggregate/IInterferenceFunction.h"

class IFTDecayFunction1D;

//! Interference function of a 1D lattice.
//! @ingroup interference

class InterferenceFunction1DLattice : public IInterferenceFunction {
public:
    InterferenceFunction1DLattice(double length, double xi);
    ~InterferenceFunction1DLattice() override;

    InterferenceFunction1DLattice* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    void setDecayFunction(const IFTDecayFunction1D& decay);

    double getLength() const { return m_length; }
    double getXi() const { return m_xi; }

    std::vector<const INode*> getChildren() const override;

private:
    double iff_without_dw(const kvector_t q) const override;

    double m_length;
    double m_xi;
    std::unique_ptr<IFTDecayFunction1D> m_decay;
    int m_na; //!< determines the number of reciprocal lattice points to use
};

#endif // BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTION1DLATTICE_H
