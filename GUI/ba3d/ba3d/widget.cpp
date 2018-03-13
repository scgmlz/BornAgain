// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/Widget.cpp
//! @brief     Implement Widget class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "widget.h"
#include "model/model.h"
#include "view/camera.h"
#include "view/canvas.h"
#include "view/program.h"

#include <QBoxLayout>

namespace RealSpace {
//------------------------------------------------------------------------------

Widget3D::Widget3D() : canvas(nullptr), camera(nullptr), program(nullptr) {
  auto box = new QHBoxLayout;
  setLayout(box);
  box->setMargin(0);
  box->addWidget((canvas = new Canvas));

  canvas->setCamera((camera = new Camera));
  canvas->setProgram((program = new Program));
}

Widget3D::~Widget3D() {
  delete program;
  delete camera;
}

void Widget3D::setBackground(QColor const& color) {
  canvas->setBgColor(color);
}

void Widget3D::setModel(Model* model) {
  canvas->setModel(model);
  connect(camera, &RealSpace::Camera::updated, model, &Model::cameraUpdated);
  camera->set();
}

void Widget3D::defaultView()
{
    canvas->defaultView();
}

void Widget3D::edgeView()
{
    canvas->edgeView();
}

void Widget3D::faceView()
{
    canvas->faceView();
}

Model* Widget3D::model() {
  return canvas->getModel();
}

//------------------------------------------------------------------------------
}
