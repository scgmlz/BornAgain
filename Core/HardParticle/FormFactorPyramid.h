// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorPyramid.h
//! @brief     Defines class FormFactorPyramid
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORPYRAMID_H
#define BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORPYRAMID_H

#include "Core/HardParticle/IFormFactorPolyhedron.h"

//! A frustum with a quadratic base.
//! @ingroup hardParticle

class FormFactorPyramid : public IFormFactorPolyhedron
{
public:
    FormFactorPyramid(const std::vector<double> P);
    FormFactorPyramid(double base_edge, double height, double alpha);

    FormFactorPyramid* clone() const override final
    {
        return new FormFactorPyramid(m_base_edge, m_height, m_alpha);
    }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double getHeight() const { return m_height; }
    double getBaseEdge() const { return m_base_edge; }
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

#endif // BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORPYRAMID_H
