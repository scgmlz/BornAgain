// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/Polyhedron.h
//! @brief     Defines class Polyhedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_POLYHEDRON_H
#define BORNAGAIN_CORE_HARDPARTICLE_POLYHEDRON_H

#include "Core/HardParticle/PolyhedralComponents.h"
#include "Core/HardParticle/PolyhedralTopology.h"
#include <memory>

//! A polyhedron, implementation class for use in IFormFactorPolyhedron

class Polyhedron
{
public:
    Polyhedron() = delete;
    Polyhedron(const Polyhedron&) = delete;
    Polyhedron(const PolyhedralTopology& topology, double z_bottom,
               const std::vector<kvector_t>& vertices);
    ~Polyhedron();
    void assert_platonic() const;
    double volume() const;
    double radius() const;
    const std::vector<kvector_t>& vertices(); //! needed for topZ, bottomZ computation
    complex_t evaluate_for_q(const cvector_t& q) const;
    complex_t evaluate_centered(const cvector_t& q) const;

private:
    double m_z_bottom;
    bool m_sym_Ci; //!< if true, then faces obtainable by inversion are not provided

    std::vector<PolyhedralFace> m_faces;
    double m_radius;
    double m_volume;
    std::vector<kvector_t> m_vertices; //! for topZ, bottomZ computation only
};

#endif // BORNAGAIN_CORE_HARDPARTICLE_POLYHEDRON_H
