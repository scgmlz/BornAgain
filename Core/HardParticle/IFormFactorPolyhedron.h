// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/IFormFactorPolyhedron.h
//! @brief     Defines class IFormFactorPolyhedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_IFORMFACTORPOLYHEDRON_H
#define BORNAGAIN_CORE_HARDPARTICLE_IFORMFACTORPOLYHEDRON_H

#include "Core/HardParticle/PolyhedralTopology.h"
#include "Core/Scattering/IFormFactorBorn.h"
#include <memory>

class Polyhedron;

//! A polyhedron, for form factor computation.

class IFormFactorPolyhedron : public IFormFactorBorn
{
public:
#ifdef POLYHEDRAL_DIAGNOSTIC
    static void setLimits(double _q, int _n);
#endif

    IFormFactorPolyhedron() = delete;
    IFormFactorPolyhedron(const NodeMeta& meta, const std::vector<double>& PValues);
    ~IFormFactorPolyhedron();

    double bottomZ(const IRotation& rotation) const override final;
    double topZ(const IRotation& rotation) const override final;

    complex_t evaluate_for_q(cvector_t q) const override final;
    complex_t evaluate_centered(cvector_t q) const;

    double volume() const override final;
    double radialExtension() const override final;
    void assert_platonic() const;

protected:
    void setPolyhedron(const PolyhedralTopology& topology, double z_bottom,
                       const std::vector<kvector_t>& vertices);

private:
    std::unique_ptr<Polyhedron> pimpl;
};

#endif // BORNAGAIN_CORE_HARDPARTICLE_IFORMFACTORPOLYHEDRON_H
