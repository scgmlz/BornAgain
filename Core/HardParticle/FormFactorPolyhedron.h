// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorPolyhedron.h
//! @brief     Defines class FormFactorPolyhedron, FormFactorPrism, and auxiliary classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FORMFACTORPOLYHEDRON_H
#define FORMFACTORPOLYHEDRON_H

#include "IFormFactorBorn.h"
#include <memory>

//! For internal use in PolyhedralFace.
class PolygonalTopology
{
public:
    std::vector<int> vertexIndices;
    bool symmetry_S2;
};

//! For internal use in FormFactorPolyhedron.
class PolyhedralTopology
{
public:
    std::vector<PolygonalTopology> faces;
    bool symmetry_Ci;
};

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
#endif

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

//! A polyhedron, for form factor computation.

class BA_CORE_API_ FormFactorPolyhedron : public IFormFactorBorn
{
public:
#ifdef POLYHEDRAL_DIAGNOSTIC
    static void setLimits(double _q, int _n);
#endif

    FormFactorPolyhedron() {}

    complex_t evaluate_for_q(cvector_t q) const override final;
    complex_t evaluate_centered(cvector_t q) const;

    double volume() const override final { return m_volume; }
    double radialExtension() const override final { return m_radius; }
    void assert_platonic() const;

protected:
    double m_z_bottom;
    bool m_sym_Ci; //!< if true, then faces obtainable by inversion are not provided

    void setPolyhedron(const PolyhedralTopology& topology, double z_bottom,
                       const std::vector<kvector_t>& vertices);

private:
    static double q_limit_series; //!< determines when to use power series
    static int n_limit_series;

    std::vector<PolyhedralFace> m_faces;
    double m_radius;
    double m_volume;
};

//! A prism with a polygonal base, for form factor computation.

class BA_CORE_API_ FormFactorPolygonalPrism : public IFormFactorBorn
{
public:
    FormFactorPolygonalPrism(double height) : m_height(height) {}

    complex_t evaluate_for_q(cvector_t q) const override final;
    double volume() const override final;
    double getHeight() const { return m_height; }
    double radialExtension() const override final { return std::sqrt(m_base->area()); }

protected:
    std::unique_ptr<PolyhedralFace> m_base;
    double m_height;
    void setPrism(bool symmetry_Ci, const std::vector<kvector_t>& vertices);
};

//! A polygonal surface, for testing form factor computations.

class BA_CORE_API_ FormFactorPolygonalSurface : public IFormFactorBorn
{
public:
    FormFactorPolygonalSurface() {}

    complex_t evaluate_for_q(cvector_t q) const override final;
    double volume() const override { return 0; }
    double radialExtension() const override final { return std::sqrt(m_base->area()); }

protected:
    std::unique_ptr<PolyhedralFace> m_base;
};

#endif // FORMFACTORPOLYHEDRON_H
