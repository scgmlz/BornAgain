// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/PolyhedralComponents.h
//! @brief     Defines classes PolyhedralEdge, PolyhedralFace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_POLYHEDRALCOMPONENTS_H
#define BORNAGAIN_CORE_HARDPARTICLE_POLYHEDRALCOMPONENTS_H

#include "Core/Basics/Complex.h"
#include "Core/Vector/Vectors3D.h"
#include <vector>

//! One edge of a polygon, for form factor computation.

class PolyhedralEdge
{
public:
    PolyhedralEdge(const kvector_t _Vlow, const kvector_t _Vhig);

    kvector_t E() const { return m_E; }
    kvector_t R() const { return m_R; }
    complex_t qE(cvector_t q) const { return m_E.dot(q); }
    complex_t qR(cvector_t q) const { return m_R.dot(q); }

    complex_t contrib(int m, cvector_t qpa, complex_t qrperp) const;

private:
    kvector_t m_E; //!< vector pointing from mid of edge to upper vertex
    kvector_t m_R; //!< position vector of edge midpoint
};

//! A polygon, for form factor computation.

class PolyhedralFace
{
public:
    static double diameter(const std::vector<kvector_t>& V);
#ifdef POLYHEDRAL_DIAGNOSTIC
    static void setLimits(double _qpa, int _n);
#endif // BORNAGAIN_CORE_HARDPARTICLE_POLYHEDRALCOMPONENTS_H

    PolyhedralFace(const std::vector<kvector_t>& _V = std::vector<kvector_t>(),
                   bool _sym_S2 = false);

    double area() const { return m_area; }
    double pyramidalVolume() const { return m_rperp * m_area / 3; }
    double radius3d() const { return m_radius_3d; }
    //! Returns conj(q)*normal [BasicVector3D::dot is antilinear in 'this' argument]
    complex_t normalProjectionConj(cvector_t q) const { return q.dot(m_normal); }
    complex_t ff_n(int m, cvector_t q) const;
    complex_t ff(cvector_t q, bool sym_Ci) const;
    complex_t ff_2D(cvector_t qpa) const;
    void assert_Ci(const PolyhedralFace& other) const;

private:
    static double qpa_limit_series; //!< determines when use power series
    static int n_limit_series;

    bool sym_S2; //!< if true, then edges obtainable by inversion are not provided
    std::vector<PolyhedralEdge> edges;
    double m_area;
    kvector_t m_normal; //!< normal vector of this polygon's plane
    double m_rperp;     //!< distance of this polygon's plane from the origin, along 'm_normal'
    double m_radius_2d; //!< radius of enclosing cylinder
    double m_radius_3d; //!< radius of enclosing sphere

    void decompose_q(cvector_t q, complex_t& qperp, cvector_t& qpa) const;
    complex_t ff_n_core(int m, cvector_t qpa, complex_t qperp) const;
    complex_t edge_sum_ff(cvector_t q, cvector_t qpa, bool sym_Ci) const;
    complex_t expansion(complex_t fac_even, complex_t fac_odd, cvector_t qpa,
                        double abslevel) const;
};

#endif // BORNAGAIN_CORE_HARDPARTICLE_POLYHEDRALCOMPONENTS_H
