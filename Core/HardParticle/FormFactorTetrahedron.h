// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorTetrahedron.h
//! @brief     Defines class FormFactorTetrahedron
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORTETRAHEDRON_H
#define BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORTETRAHEDRON_H

#include "Core/HardParticle/IFormFactorPolyhedron.h"

//! A frustum with equilateral trigonal base.
//! @ingroup hardParticle

class FormFactorTetrahedron : public IFormFactorPolyhedron
{
public:
    FormFactorTetrahedron(const std::vector<double> P);
    FormFactorTetrahedron(double base_edge, double height, double alpha);

    FormFactorTetrahedron* clone() const override final
    {
        return new FormFactorTetrahedron(m_base_edge, m_height, m_alpha);
    }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double getBaseEdge() const { return m_base_edge; }
    double getHeight() const { return m_height; }
    double getAlpha() const { return m_alpha; }

protected:
    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const override final;

    void onChange() override final;

private:
    static const PolyhedralTopology topology;
    const double& m_base_edge;
    const double& m_height;
    const double& m_alpha;
};

#endif // BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORTETRAHEDRON_H
