// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/canvas.h
//! @brief     Defines Canvas class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BA3D_CANVAS_H
#define BA3D_CANVAS_H

#include "../def.h"
#include <QHash>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

namespace RealSpace {

class Camera; class Program; class Model;
class Geometry; class Buffer; class Object;

class Canvas: public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
    friend class Object;
public:
    Canvas();
    ~Canvas();

    void setBgColor(QColor const&);

    // active things, owned elsewhere, may be nullptr
    void setCamera(Camera*);
    void setProgram(Program*);
    void setModel(Model*);
    Model* getModel();

    // ToolBar Actions
    void defaultView();
    void edgeView();
    void faceView();

    void canvasHintMessageBox();

private:
    QRect viewport;
    float aspectRatio, colorBgR, colorBgG, colorBgB;

    void setCamera(bool full = true);

    void initializeGL();
    void resizeGL(int, int);
    void paintGL();

    QVector3D lastV;    // unprojected vector
    float     lastY;    // screen coordinate
    QMatrix4x4 matModel, matProj;
    QVector3D  unproject(QPoint const&);

    enum {btnNONE, btnTURN, btnZOOM} mouseButton;
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent*);

    Camera  *camera;
    Program *program;
    Model   *model;

    QMetaObject::Connection modelUpdated;

    QHash<Geometry const*, Buffer*> buffers;
    void releaseBuffer(Geometry const*);
    void releaseBuffers();

    void draw(QColor const&, QMatrix4x4 const&, Geometry const&);
};

}  // namespace RealSpace
#endif  // BA3D_CANVAS_H
