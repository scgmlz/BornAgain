// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      dev-tools/sandboxes/realSpace/demo2/modelLayers.cpp
//! @brief     Implements ModelLayers class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "modelLayers.h"
#include "modelShowcase.h"
#include "GUI/ba3d/model/layer.h"

//------------------------------------------------------------------------------

using namespace RealSpace;

static float const sz = 100; // half sz

ModelLayers::ModelLayers()
{
    defCamPos = Camera::Position(Vector3D(-10, -140, 20), Vector3D(0, 0, -30), Vector3D::_z);

    auto layer = [&](int z1, int z2, QColor color) {
        float s2 = sz / 2;
        auto l = new Layer(VectorRange(Range(-s2, +s2), Range(-s2, +s2), Range(z1, z2)));
        color.setAlphaF(.3);
        l->color = color;

        addBlend(l);
    };

    layer(0, -10, Qt::blue);
    layer(-10, -30, Qt::green);
    layer(-30, -45, Qt::red);
    layer(-45, -55, Qt::gray);
}

void ModelLayers::showKind(Particles::EShape k)
{
    for (auto p : ps)
        delete p;
    ps.clear();

    if (Particles::EShape::None == k)
        return;

    float z[] = {-10, -30, -45};
    ps.reserve(3 * 9 * 9);
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            for (int zi = 0; zi < 3; ++zi) {
                auto p = ModelShowcase::newParticle(k, 3);
                add(p);
                ps.append(p);
                p->transform(Vector3D::_0,
                             Vector3D((i - 4) * sz / 10, (j - 4) * sz / 10, z[zi] + .001f));
            }

    emit updated(false);
}

//------------------------------------------------------------------------------
