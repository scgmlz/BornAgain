// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorTruncatedCube.h
//! @brief     Defines class FormFactorTruncatedCube.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORTRUNCATEDCUBE_H
#define BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORTRUNCATEDCUBE_H

#include "Core/HardParticle/FormFactorPolyhedron.h"

//! A cube, with tetrahedral truncation of all corners
//! @ingroup hardParticle

class BA_CORE_API_ FormFactorTruncatedCube : public FormFactorPolyhedron
{
public:
    FormFactorTruncatedCube(const std::vector<double> P);
    FormFactorTruncatedCube(double length, double removed_length);

    FormFactorTruncatedCube* clone() const override final
    {
        return new FormFactorTruncatedCube(m_length, m_removed_length);
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

#endif // BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORTRUNCATEDCUBE_H
