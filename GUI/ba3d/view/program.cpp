// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/view/program.cpp
//! @brief     Implements Program class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/ba3d/view/program.h"
#include "GUI/ba3d/view/camera.h"
#include <QMatrix4x4>
#include <stdexcept>

// The macro call has to be in the global namespace
inline void InitShaderResources()
{
    Q_INIT_RESOURCE(shaders);
}

static constexpr float AMBIENT = 0.4f;

namespace RealSpace
{

Program::Program()
{
    // make sure our resource file gets initialized
    InitShaderResources();

    needsInit();
}

void Program::needsInit()
{
    doInit = true;
}

void Program::init()
{
    if (!doInit)
        return;
    doInit = false;

    auto shader_found =
        addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertex_shader.vert");
    if (!shader_found)
        throw std::runtime_error("Vertex shader not loaded");

    shader_found =
        addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragment_shader.frag");
    if (!shader_found)
        throw std::runtime_error("Fragment shader not loaded");

    bindAttributeLocation("vertex", 0);
    bindAttributeLocation("normal", 1);
    bindAttributeLocation("axiscolor", 2);

    link();

    bind();
    locMatProj = uniformLocation("matProj");
    locMatModel = uniformLocation("matModel");
    locMatObject = uniformLocation("matObject");
    locLightPos1 = uniformLocation("lightPos1");
    locColor = uniformLocation("color");
    ambient = uniformLocation("ambient");
    eye = uniformLocation("eye");
    locAxis = uniformLocation("axis");
    release();
}

void Program::set(Camera const& camera)
{
    setUniformValue(ambient, AMBIENT);
    setUniformValue(locMatProj, camera.matProj);
    setUniformValue(locMatModel, camera.matModel);
    setUniformValue(locLightPos1, camera.lightPosRotated1);
    setUniformValue(eye, camera.getPos().eye);
}

void Program::set(QColor const& color)
{
    setUniformValue(locColor, color);
}

void Program::set(QMatrix4x4 const& mat)
{
    setUniformValue(locMatObject, mat);
}

void Program::setMatModel(QMatrix4x4 const& mat)
{
    setUniformValue(locMatModel, mat);
}

void Program::setAxis(bool const& axis_)
{
    setUniformValue(locAxis, axis_);
}

} // namespace RealSpace
