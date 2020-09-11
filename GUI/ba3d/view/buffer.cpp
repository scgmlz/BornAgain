// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/view/buffer.cpp
//! @brief     Implements Buffer class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/ba3d/view/buffer.h"
#include "../model/geometry.h"

namespace
{
const float cx = 120; // multiplication scale for controlling how long the axes shall be in xy
const float cz = 100; // multiplication scale for controlling how long the axes shall be in z
} // namespace

namespace RealSpace
{

Buffer::Buffer(Geometry const& geometry)
{
    initializeOpenGLFunctions();

    auto& mesh = geometry.m_mesh;
    m_vertexCount = mesh.count();

    QOpenGLVertexArrayObject::Binder __(&m_vao);

    m_glBuffer.create();
    m_glBuffer.bind();
    m_glBuffer.allocate(mesh.constData(), m_vertexCount * int(sizeof(Geometry::Vert_Normal)));

    glEnableVertexAttribArray(0); // vertices
    glEnableVertexAttribArray(1); // normals

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(Vector3D), nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(Vector3D),
                          reinterpret_cast<void*>(sizeof(Vector3D)));
}

void Buffer::draw()
{
    QOpenGLVertexArrayObject::Binder __(&m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
}

Buffer3DAxes::Buffer3DAxes()
{
    initializeOpenGLFunctions();

    QOpenGLVertexArrayObject::Binder __(&m_vao3DAxes);

    // vertices (xyz) and colors (rgb) for drawing each line (also arrows) in the 3D axes
    const GLfloat vertices3DAxes[] = {
        0.00f,       0.00f,       0.00f,       1.0f,       0.0f,        0.0f, // x-axis
        cx * 1.00f,  0.00f,       0.00f,       1.0f,       0.0f,        0.0f,        cx * 1.00f,
        0.00f,       0.00f,       1.0f,        0.0f,       0.0f,        cx * 0.95f,  cz * 0.05f,
        cz * 0.05f,  1.0f,        0.0f,        0.0f,       cx * 1.00f,  0.00f,       0.00f,
        1.0f,        0.0f,        0.0f,        cx * 0.95f, cz * 0.05f,  cz * -0.05f, 1.0f,
        0.0f,        0.0f,        cx * 1.00f,  0.00f,      0.00f,       1.0f,        0.0f,
        0.0f,        cx * 0.95f,  cz * -0.05f, cz * 0.05f, 1.0f,        0.0f,        0.0f,
        cx * 1.00f,  0.00f,       0.00f,       1.0f,       0.0f,        0.0f,        cx * 0.95f,
        cz * -0.05f, cz * -0.05f, 1.0f,        0.0f,       0.0f,

        0.00f,       0.00f,       0.00f,       0.0f,       1.0f,        0.0f, // y-axis
        0.00f,       cx * 1.00f,  0.00f,       0.0f,       1.0f,        0.0f,        0.00f,
        cx * 1.00f,  0.00f,       0.0f,        1.0f,       0.0f,        cz * 0.05f,  cx * 0.95f,
        cz * 0.05f,  0.0f,        1.0f,        0.0f,       0.00f,       cx * 1.00f,  0.00f,
        0.0f,        1.0f,        0.0f,        cz * 0.05f, cx * 0.95f,  cz * -0.05f, 0.0f,
        1.0f,        0.0f,        0.00f,       cx * 1.00f, 0.00f,       0.0f,        1.0f,
        0.0f,        cz * -0.05f, cx * 0.95f,  cz * 0.05f, 0.0f,        1.0f,        0.0f,
        0.00f,       cx * 1.00f,  0.00f,       0.0f,       1.0f,        0.0f,        cz * -0.05f,
        cx * 0.95f,  cz * -0.05f, 0.0f,        1.0f,       0.0f,

        0.00f,       0.00f,       0.00f,       0.0f,       0.0f,        1.0f, // z-axis
        0.00f,       0.00f,       cz * 1.00f,  0.0f,       0.0f,        1.0f,        0.00f,
        0.00f,       cz * 1.00f,  0.0f,        0.0f,       1.0f,        cz * 0.05f,  cz * 0.05f,
        cz * 0.95f,  0.0f,        0.0f,        1.0f,       0.00f,       0.00f,       cz * 1.00f,
        0.0f,        0.0f,        1.0f,        cz * 0.05f, cz * -0.05f, cz * 0.95f,  0.0f,
        0.0f,        1.0f,        0.00f,       0.00f,      cz * 1.00f,  0.0f,        0.0f,
        1.0f,        cz * -0.05f, cz * 0.05f,  cz * 0.95f, 0.0f,        0.0f,        1.0f,
        0.00f,       0.00f,       cz * 1.00f,  0.0f,       0.0f,        1.0f,        cz * -0.05f,
        cz * -0.05f, cz * 0.95f,  0.0f,        0.0f,       1.0f,
    };

    m_vertexCount3DAxes = 30;

    m_glBuffer3DAxes.create();
    m_glBuffer3DAxes.bind();
    m_glBuffer3DAxes.allocate(vertices3DAxes, int(sizeof(vertices3DAxes)));

    glEnableVertexAttribArray(0); // 3D axes vertices
    glEnableVertexAttribArray(2); // 3D axes colors

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          reinterpret_cast<void*>(3 * sizeof(float)));
}

void Buffer3DAxes::draw3DAxes()
{
    QOpenGLVertexArrayObject::Binder __(&m_vao3DAxes);
    glLineWidth(1.4f);
    glDrawArrays(GL_LINES, 0, m_vertexCount3DAxes);
}

} // namespace RealSpace
