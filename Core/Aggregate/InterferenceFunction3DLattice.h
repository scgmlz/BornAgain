// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction3DLattice.h
//! @brief     Defines class InterferenceFunction3DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTION3DLATTICE_H
#define INTERFERENCEFUNCTION3DLATTICE_H

#include "IInterferenceFunction.h"
#include "Lattice.h"

class IPeakShape;

//! Interference function of 3D lattice.
//! @ingroup interference

class BA_CORE_API_ InterferenceFunction3DLattice : public IInterferenceFunction
{
public:
    InterferenceFunction3DLattice(const Lattice& lattice);
    ~InterferenceFunction3DLattice() final;

    InterferenceFunction3DLattice* clone() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    void setPeakShape(const IPeakShape& peak_shape);

    void setDebyeWallerFactor(double dw_length);

    double evaluate(const kvector_t q) const final;

    const Lattice& lattice() const;

    bool supportsMultilayer() const override { return false; }

    std::vector<const INode*> getChildren() const override;

    void onChange() override final;
private:
    void initRecRadius();
    Lattice m_lattice;
    std::unique_ptr<IPeakShape> mP_peak_shape;
    double m_rec_radius;  //!< radius in reciprocal space defining the nearest q vectors to use
    double m_dw_length;   //!< standard deviation of lattice position perturbations for Debye Waller
};

#endif // INTERFERENCEFUNCTION3DLATTICE_H
