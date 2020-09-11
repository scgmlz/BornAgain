// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/geometry.cpp
//! @brief     Implements Geometry class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/ba3d/model/geometry.h"
#include "Core/Basics/Assert.h"
#include "GUI/ba3d/model/model.h"

namespace RealSpace
{
//------------------------------------------------------------------------------

Geometry::Vert_Normal::Vert_Normal(const Vector3D& v_, const Vector3D& n_) : v(v_), n(n_) {}

void Geometry::Vertices::addVertex(const Vector3D& v, int n)
{
    for (int i = 0; i < n; ++i)
        append(v);
}

void Geometry::Vertices::addTriangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3)
{
    append(v1);
    append(v2);
    append(v3);
}

void Geometry::Vertices::addQuad(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3,
                                 const Vector3D& v4)
{
    addTriangle(v1, v2, v3);
    addTriangle(v3, v4, v1);
}

void Geometry::Vertices::addQuad(const Vertices& vs, unsigned i1, unsigned i2, unsigned i3,
                                 unsigned i4)
{
    addQuad(vs.at(i1), vs.at(i2), vs.at(i3), vs.at(i4));
}

void Geometry::Vertices::addStrip(const Vertices& vs, const Indices& is)
{
    ASSERT(is.size() >= 3); // at least one triangle
    for (unsigned i = 0; i + 2 < is.size(); ++i)
        if (i % 2)
            addTriangle(vs.at(is.at(i)), vs.at(is.at(1 + i)), vs.at(is.at(2 + i)));
        else
            addTriangle(vs.at(is.at(i)), vs.at(is.at(2 + i)), vs.at(is.at(1 + i)));
}

void Geometry::Vertices::addFan(const Vertices& vs, const Indices& is)
{
    ASSERT(is.size() >= 3); // at least one triangle
    auto& ctr = vs.at(is.at(0));
    for (unsigned i = 0; i + 2 < is.size(); ++i)
        addTriangle(ctr, vs.at(is.at(1 + i)), vs.at(is.at(2 + i)));
}

//------------------------------------------------------------------------------

Geometry::Geometry(GeometricID::Key key_) : m_key(key_)
{
    using namespace GeometricID;

    switch (m_key.id) {
    case BaseShape::Plane:
        m_mesh = meshPlane();
        break;
    case BaseShape::Box:
        m_mesh = meshBox();
        break;
    case BaseShape::Sphere:
        m_mesh = meshSphere(m_key.p1, m_key.p2, m_key.p3);
        break;
    case BaseShape::Column:
        m_mesh = meshColumn(m_key.p1, m_key.p2);
        break;
    case BaseShape::Icosahedron:
        m_mesh = meshIcosahedron();
        break;
    case BaseShape::Dodecahedron:
        m_mesh = meshDodecahedron();
        break;
    case BaseShape::TruncatedBox:
        m_mesh = meshTruncBox(m_key.p1);
        break;
    case BaseShape::Cuboctahedron:
        m_mesh = meshCuboctahedron(m_key.p1, m_key.p2, m_key.p3);
        break;
    case BaseShape::Ripple:
        m_mesh = meshRipple(m_key.p1, m_key.p2);
        break;
    }
}

Geometry::~Geometry()
{
    // remove self from the store
    geometryStore().geometryDeleted(*this);
}

Geometry::Mesh Geometry::makeMesh(const Vertices& vs, Vertices const* ns)
{
    int nv = vs.count();
    ASSERT(0 == nv % 3);
    ASSERT(!ns || nv == ns->count()); // if normals not given, will be computed

    Mesh mesh(nv);

    for (int i = 0; i < nv; i += 3) {
        const Vector3D &v0 = vs.at(0 + i), v1 = vs.at(1 + i), v2 = vs.at(2 + i);
        const Vector3D *n0, *n1, *n2;
        Vector3D nm;

        if (ns) {
            n0 = &ns->at(0 + i);
            n1 = &ns->at(1 + i);
            n2 = &ns->at(2 + i);
        } else {
            nm = cross((v1 - v0), (v2 - v0));
            n0 = n1 = n2 = &nm;
        }

        mesh.append(Vert_Normal(v0, *n0));
        mesh.append(Vert_Normal(v1, *n1));
        mesh.append(Vert_Normal(v2, *n2));
    }

    return mesh;
}

Geometry::Mesh Geometry::makeMesh(const Vertices& vs, const Vertices& ns)
{
    return makeMesh(vs, &ns);
}

//------------------------------------------------------------------------------

GeometryHandle GeometryStore::getGeometry(GeometricID::Key key)
{
    auto it = m_geometries.find(key);
    if (m_geometries.end() != it) {
        if (auto g = it->second.lock())
            return g;
    }
    GeometryHandle g = GeometryHandle(new Geometry(key));
    m_geometries[key] = GeometryRef(g);
    return g;
}

void GeometryStore::geometryDeleted(Geometry const& g)
{
    emit deletingGeometry(&g);
    m_geometries.erase(g.m_key);
}

GeometryStore& geometryStore()
{
    static GeometryStore gs;
    return gs;
}

//------------------------------------------------------------------------------
} // namespace RealSpace
