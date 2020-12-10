//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/IFormFactorPolyhedron.h
//! @brief     Defines interface IFormFactorPolyhedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_HARDPARTICLE_IFORMFACTORPOLYHEDRON_H
#define BORNAGAIN_SAMPLE_HARDPARTICLE_IFORMFACTORPOLYHEDRON_H

#include "Sample/HardParticle/PolyhedralTopology.h"
#include "Sample/Scattering/IBornFF.h"
#include <memory>

class Polyhedron;

//! A polyhedron, for form factor computation.

class IFormFactorPolyhedron : public IBornFF {
public:
#ifdef POLYHEDRAL_DIAGNOSTIC
    static void setLimits(double _q, int _n);
#endif

    IFormFactorPolyhedron() = delete;
    IFormFactorPolyhedron(const NodeMeta& meta, const std::vector<double>& PValues);
    ~IFormFactorPolyhedron();

    double bottomZ(const IRotation& rotation) const final;
    double topZ(const IRotation& rotation) const final;

    complex_t evaluate_for_q(cvector_t q) const final;
    complex_t evaluate_centered(cvector_t q) const;

    double volume() const final;
    double radialExtension() const final;
    void assert_platonic() const;

protected:
    void setPolyhedron(const PolyhedralTopology& topology, double z_bottom,
                       const std::vector<kvector_t>& vertices);

private:
    std::unique_ptr<Polyhedron> pimpl;
};

#endif // BORNAGAIN_SAMPLE_HARDPARTICLE_IFORMFACTORPOLYHEDRON_H
#endif // USER_API
