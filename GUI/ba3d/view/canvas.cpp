// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/view/canvas.cpp
//! @brief     Implements Canvas class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/ba3d/view/canvas.h"
#include "../model/geometry.h"
#include "../model/model.h"
#include "Core/Basics/Assert.h"
#include "GUI/ba3d/view/buffer.h"
#include "GUI/ba3d/view/camera.h"
#include "GUI/ba3d/view/program.h"

#include <QMouseEvent>
#include <QSysInfo>
#include <cmath>
#include <cstdlib>

namespace
{
float ZoomInScale()
{
    if (QSysInfo::productType() == "osx")
        return 1.02f;
    return 1.25f;
}
float ZoomOutScale()
{
    if (QSysInfo::productType() == "osx")
        return 0.98f;
    return 0.8f;
}

const float rot_speed_h = 0.4f; // camera rotation speed in horizontal direction
const float rot_speed_v = 0.4f; // camera rotation speed in vertical direction

// Default camera position in accordance with RealSpaceBuilder.h
const float cameraDefaultPosY = -200.0f; // default camera position on Y axis
const float cameraDefaultPosZ = 120.0f;  // default camera position on Z axis
} // namespace

namespace RealSpace
{

Canvas::Canvas()
    : aspectRatio(1), colorBgR(1), colorBgG(1), colorBgB(1), currentZoomLevel(0), camera(nullptr),
      program(nullptr), model(nullptr), m_isInitializedGL(false)
{
    connect(&geometryStore(), &GeometryStore::deletingGeometry, this, &Canvas::releaseBuffer);
}

Canvas::~Canvas()
{
    cleanup();
}

void Canvas::setBgColor(QColor const& c)
{
    colorBgR = float(c.redF());
    colorBgG = float(c.greenF());
    colorBgB = float(c.blueF());
    update();
}

void Canvas::setCamera(Camera* c)
{
    camera = c;
    setCamera();
}

void Canvas::setProgram(Program* p)
{
    program = p;
    if (program)
        program->needsInit();
    update();
}

void Canvas::setModel(Model* m)
{
    releaseBuffers();

    disconnect(modelUpdated);
    model = m;
    modelUpdated = connect(model, &Model::updated, [this](bool withEye) {
        if (withEye)
            setCamera();
        else
            update();
    });

    setCamera();
    // connect(camera, &RealSpace::Camera::updated, model, &Model::cameraUpdated);
    camera->set();
}

Model* Canvas::getModel()
{
    return model;
}

void Canvas::setCamera(bool full)
{
    if (camera) {
        camera->setAspectRatio(aspectRatio);
        if (full && model)
            camera->lookAt(model->defCamPos);
    }

    update();
}

void Canvas::initializeGL()
{
    setCamera((camera = new Camera));
    setProgram((program = new Program));

    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &Canvas::cleanup);

    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    m_isInitializedGL = true;
}

void Canvas::resizeGL(int w, int h)
{
    int w1 = qMax(1, w), h1 = qMax(1, h);
    viewport.setRect(0, 0, w1, h1);
    aspectRatio = float(w1) / float(h1);
    setCamera(false);
}

void Canvas::paintGL()
{
    glClearColor(colorBgR, colorBgG, colorBgB, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (camera && program && model) {
        program->init();
        program->bind();
        program->set(*camera);
        program->setAxis(false);

        // opaque objects
        model->draw(*this);

        // transparent objects
        glEnable(GL_BLEND);
        glDepthMask(false);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        model->drawBlend(*this);
        glDisable(GL_BLEND);
        glDepthMask(true);

        if (!model->modelIsEmpty()) {
            // Draw 3D coordinate axes in lower left corner
            glViewport(0, 0, viewport.width() / 9, viewport.height() / 5);
            QMatrix4x4 matObject3DAxes;
            matObject3DAxes.setToIdentity(); // 3D axes transformation matrix is Identity
            program->set(matObject3DAxes);
            program->setMatModel(camera->matModel3DAxes);
            program->setAxis(true);
            std::unique_ptr<Buffer3DAxes> buf3DAxes(new Buffer3DAxes());
            buf3DAxes->draw3DAxes();
        }

        program->release();
    }
}

QVector3D Canvas::unproject(QPoint const& p)
{
    float x = p.x(), y = viewport.height() - p.y();
    return QVector3D(x, y, 1).unproject(matModel, matProj, viewport);
}

void Canvas::mousePressEvent(QMouseEvent* e)
{
    switch (e->button()) {
    case Qt::LeftButton:
        mouseButton = btnTURN;
        break;
    case Qt::RightButton:
        mouseButton = btnZOOM;
        break;
    default:
        mouseButton = btnNONE;
        break;
    }

    if (camera) {
        matModel = camera->matModel;
        matProj = camera->matProj;
        e_last = e->pos();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent* e)
{
    if (camera) {
        float delta_x = e->pos().x() - e_last.x();
        float delta_y = e->pos().y() - e_last.y();

        switch (mouseButton) {
        case btnTURN: {
            if (delta_x != 0)
                horizontalCameraTurn(-delta_x * rot_speed_h); // -ve for consistency with Blender

            if (delta_y != 0)
                verticalCameraTurn(-delta_y * rot_speed_v); // -ve for consistency with Blender

            e_last = e->pos();
            break;
        }
        case btnZOOM: {
            float d = (e->y() - e_last.y()) / float(viewport.height());
            camera->zoomBy(1 + d);
            break;
        }
        default:
            break;
        }

        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent*)
{
    if (camera) {
        camera->endTransform(true);
        update();
    }
}

void Canvas::wheelEvent(QWheelEvent* e)
{
    if (camera) {
        if (e->delta() < 0) {
            // Zoom in
            camera->zoomBy(ZoomInScale());
            currentZoomLevel += 1;
        } else {
            // Zoom out
            camera->zoomBy(ZoomOutScale());
            currentZoomLevel -= 1;
        }
        camera->endTransform(true);
        update();
    }
    e->accept(); // disabling the event from propagating further to the parent widgets
}

void Canvas::releaseBuffer(Geometry const* g)
{
    delete buffers.take(g);
}

void Canvas::releaseBuffers()
{
    for (auto b : buffers.values())
        delete b;
    buffers.clear();
}

void Canvas::draw(QColor const& color, QMatrix4x4 const& mat, Geometry const& geo)
{
    auto it = buffers.find(&geo);
    Buffer* buf;
    if (buffers.end() == it)
        buffers.insert(&geo, buf = new Buffer(geo)); // created on demand
    else
        buf = *it;

    ASSERT(program);
    program->set(color);
    program->set(mat);
    buf->draw();
}

void Canvas::cleanup()
{
    makeCurrent();

    releaseBuffers();

    delete camera;
    camera = nullptr;
    delete program;
    program = nullptr;

    m_isInitializedGL = false;
    doneCurrent();
}

bool Canvas::isInitialized() const
{
    return m_isInitializedGL && model != nullptr;
}

void Canvas::defaultView()
{
    // Default view
    if (isInitialized()) {
        RealSpace::Camera::Position defPos(
            RealSpace::Vector3D(0, cameraDefaultPosY, cameraDefaultPosZ), // eye
            RealSpace::Vector3D(0, 0, 0),                                 // center
            RealSpace::Vector3D::_z);                                     // up

        // Default position of camera for 3D axes and object are the same
        camera->lookAt3DAxes(defPos);
        camera->lookAt(defPos);
        camera->endTransform(true);

        currentZoomLevel = 0; // reset zoom level to default value
        update();
    }
}

void Canvas::sideView()
{
    // Side view at current zoom level
    if (isInitialized()) {
        RealSpace::Vector3D eye(0, cameraDefaultPosY, 0);

        // Side view 3D axes is zoom scale independent
        camera->lookAt3DAxes(RealSpace::Camera::Position(eye,                          // eye
                                                         RealSpace::Vector3D(0, 0, 0), // center
                                                         RealSpace::Vector3D::_z));    // up

        // Side view 3D object is zoom scale dependent
        if (currentZoomLevel >= 0)
            eye.y *= std::pow(ZoomInScale(), std::abs(currentZoomLevel));
        else
            eye.y *= std::pow(ZoomOutScale(), std::abs(currentZoomLevel));

        camera->lookAt(RealSpace::Camera::Position(eye,                          // eye
                                                   RealSpace::Vector3D(0, 0, 0), // center
                                                   RealSpace::Vector3D::_z));    // up

        camera->endTransform(true);
        update();
    }
}

void Canvas::topView()
{
    // Top view at current zoom level
    if (isInitialized()) {
        // Setting a tiny offset in y value of eye such that eye and up vectors are not parallel
        RealSpace::Vector3D eye(0, -0.5, -cameraDefaultPosY);

        // Top view 3D axes is zoom scale independent
        camera->lookAt3DAxes(RealSpace::Camera::Position(eye,                          // eye
                                                         RealSpace::Vector3D(0, 0, 0), // center
                                                         RealSpace::Vector3D::_z));    // up

        // Top view 3D object is zoom scale dependent
        if (currentZoomLevel >= 0)
            eye.z *= std::pow(ZoomInScale(), std::abs(currentZoomLevel));
        else
            eye.z *= std::pow(ZoomOutScale(), std::abs(currentZoomLevel));

        camera->lookAt(RealSpace::Camera::Position(eye,                          // eye
                                                   RealSpace::Vector3D(0, 0, 0), // center
                                                   RealSpace::Vector3D::_z));    // up

        camera->endTransform(true);
        update();
    }
}

void Canvas::horizontalCameraTurn(float angle)
{
    if (isInitialized()) {

        float theta = angle * static_cast<float>(M_PI / 180.0); // in radians

        // Horizontal camera turn for 3D axes
        Camera::Position initial_pos3DAxes = camera->getPos3DAxes();

        RealSpace::Vector3D v_eye3DAxes = initial_pos3DAxes.eye; // camera's position vector
        RealSpace::Vector3D v_ctr3DAxes = initial_pos3DAxes.ctr;
        RealSpace::Vector3D v_up3DAxes = initial_pos3DAxes.up;

        RealSpace::Vector3D v_axis3DAxes = v_up3DAxes.normalized(); // normalized rotation axis

        // Rotating camera's position (eye) about up vector
        RealSpace::Vector3D v_rot_eye3DAxes =
            v_up3DAxes * (1 - std::cos(theta)) * dot(v_axis3DAxes, v_eye3DAxes)
            + v_eye3DAxes * std::cos(theta) + cross(v_axis3DAxes, v_eye3DAxes) * std::sin(theta);

        Camera::Position rotated_pos3DAxes(v_rot_eye3DAxes, v_ctr3DAxes, v_up3DAxes);

        camera->lookAt3DAxes(rotated_pos3DAxes);

        // Horizontal camera turn for 3D object
        Camera::Position initial_pos = camera->getPos();

        RealSpace::Vector3D v_eye = initial_pos.eye; // camera's position vector
        RealSpace::Vector3D v_ctr = initial_pos.ctr;
        RealSpace::Vector3D v_up = initial_pos.up;

        RealSpace::Vector3D v_axis = v_up.normalized(); // normalized rotation axis

        // Rotating camera's position (eye) about up vector
        RealSpace::Vector3D v_rot_eye = v_up * (1 - std::cos(theta)) * dot(v_axis, v_eye)
                                        + v_eye * std::cos(theta)
                                        + cross(v_axis, v_eye) * std::sin(theta);

        Camera::Position rotated_pos(v_rot_eye, v_ctr, v_up);

        camera->lookAt(rotated_pos);

        camera->endTransform(true);
    }
}

void Canvas::verticalCameraTurn(float angle)
{
    if (isInitialized()) {

        float theta = angle * static_cast<float>(M_PI / 180.0); // in radians

        // Vertical camera turn for 3D axes
        Camera::Position initial_pos3DAxes = camera->getPos3DAxes();

        RealSpace::Vector3D v_eye3DAxes = initial_pos3DAxes.eye; // camera's position vector
        RealSpace::Vector3D v_ctr3DAxes = initial_pos3DAxes.ctr;
        RealSpace::Vector3D v_up3DAxes = initial_pos3DAxes.up;

        RealSpace::Vector3D v_axis3DAxes =
            cross(v_up3DAxes, v_eye3DAxes).normalized(); // normalized rotation axis

        // Rotating camera's position (eye) about an axis perpendicular to up and eye vectors
        RealSpace::Vector3D v_rot_eye3DAxes =
            v_up3DAxes * (1 - std::cos(theta)) * dot(v_axis3DAxes, v_eye3DAxes)
            + v_eye3DAxes * std::cos(theta) + cross(v_axis3DAxes, v_eye3DAxes) * std::sin(theta);

        Camera::Position rotated_pos3DAxes(v_rot_eye3DAxes, v_ctr3DAxes, v_up3DAxes);

        camera->lookAt3DAxes(rotated_pos3DAxes);

        // Vertical camera turn for 3D object
        Camera::Position initial_pos = camera->getPos();

        RealSpace::Vector3D v_eye = initial_pos.eye; // camera's position vector
        RealSpace::Vector3D v_ctr = initial_pos.ctr;
        RealSpace::Vector3D v_up = initial_pos.up;

        RealSpace::Vector3D v_axis = cross(v_up, v_eye).normalized(); // normalized rotation axis

        // Rotating camera's position (eye) about an axis perpendicular to up and eye vectors
        RealSpace::Vector3D v_rot_eye = v_up * (1 - std::cos(theta)) * dot(v_axis, v_eye)
                                        + v_eye * std::cos(theta)
                                        + cross(v_axis, v_eye) * std::sin(theta);

        Camera::Position rotated_pos(v_rot_eye, v_ctr, v_up);

        camera->lookAt(rotated_pos);

        camera->endTransform(true);
    }
}

} // namespace RealSpace
