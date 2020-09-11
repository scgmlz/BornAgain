// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorCone6.h
//! @brief     Defines class FormFactorCone6
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORCONE6_H
#define BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORCONE6_H

#include "Core/HardParticle/FormFactorPolyhedron.h"

//! A frustum (truncated pyramid) with regular hexagonal base.
//! @ingroup hardParticle

class BA_CORE_API_ FormFactorCone6 : public FormFactorPolyhedron
{
public:
    FormFactorCone6(const std::vector<double> P);
    FormFactorCone6(double base_edge, double height, double alpha);

    FormFactorCone6* clone() const override final
    {
        return new FormFactorCone6(m_base_edge, m_height, m_alpha);
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

#endif // BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORCONE6_H
