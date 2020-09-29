// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorCuboctahedron.h
//! @brief     Defines class FormFactorCuboctahedron
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORCUBOCTAHEDRON_H
#define BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORCUBOCTAHEDRON_H

#include "Core/HardParticle/IFormFactorPolyhedron.h"

//! A truncated bifrustum with quadratic base.
//! @ingroup hardParticle

class FormFactorCuboctahedron : public IFormFactorPolyhedron
{
public:
    FormFactorCuboctahedron(const std::vector<double> P);
    FormFactorCuboctahedron(double length, double height, double height_ratio, double alpha);

    FormFactorCuboctahedron* clone() const override final
    {
        return new FormFactorCuboctahedron(m_length, m_height, m_height_ratio, m_alpha);
    }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double getLength() const { return m_length; }
    double getHeight() const { return m_height; }
    double getHeightRatio() const { return m_height_ratio; }
    double getAlpha() const { return m_alpha; }

protected:
    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const override final;

    void onChange() override final;

private:
    static const PolyhedralTopology topology;

    const double& m_length;
    const double& m_height;
    const double& m_height_ratio;
    const double& m_alpha;
};

#endif // BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORCUBOCTAHEDRON_H
