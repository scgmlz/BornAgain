// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/widget.cpp
//! @brief     Implement Widget class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/ba3d/widget.h"
#include "model/model.h"
#include "view/camera.h"
#include "view/canvas.h"
#include "view/program.h"

#include <QBoxLayout>

namespace RealSpace
{
//------------------------------------------------------------------------------

Widget3D::Widget3D() : canvas(nullptr)
{
    auto box = new QHBoxLayout;
    setLayout(box);
    box->setMargin(0);
    box->addWidget((canvas = new Canvas));
}

Widget3D::~Widget3D() {}

Camera& Widget3D::cam()
{
    return *canvas->cam();
}

void Widget3D::setBackground(QColor const& color)
{
    canvas->setBgColor(color);
}

void Widget3D::setModel(Model* model)
{
    canvas->setModel(model);
}

void Widget3D::defaultView()
{
    canvas->defaultView();
}

void Widget3D::sideView()
{
    canvas->sideView();
}

void Widget3D::topView()
{
    canvas->topView();
}

Model* Widget3D::model()
{
    return canvas->getModel();
}

//------------------------------------------------------------------------------
} // namespace RealSpace
