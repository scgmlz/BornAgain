// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorCantellatedCube.h
//! @brief     Defines class FormFactorCantellatedCube.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORCANTELLATEDCUBE_H
#define BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORCANTELLATEDCUBE_H

#include "Core/HardParticle/IFormFactorPolyhedron.h"

//! A cube, with truncation of all edges and corners, as in Croset (2017) Fig 7
//! @ingroup hardParticle

class FormFactorCantellatedCube : public IFormFactorPolyhedron
{
public:
    FormFactorCantellatedCube(const std::vector<double> P);
    FormFactorCantellatedCube(double length, double removed_length);

    FormFactorCantellatedCube* clone() const override final
    {
        return new FormFactorCantellatedCube(m_length, m_removed_length);
    }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double getLength() const { return m_length; }
    double getRemovedLength() const { return m_removed_length; }

protected:
    void onChange() override final;

private:
    static const PolyhedralTopology topology;
    const double& m_length;
    const double& m_removed_length;
};

#endif // BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORCANTELLATEDCUBE_H
