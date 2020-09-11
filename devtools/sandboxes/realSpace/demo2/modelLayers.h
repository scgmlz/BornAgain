// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      dev-tools/sandboxes/realSpace/demo2/modelLayers.h
//! @brief     Defines ModelLayers class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BA3D_MODEL_LAYERS_H
#define BA3D_MODEL_LAYERS_H

#include "GUI/ba3d/model/model.h"
#include "GUI/ba3d/model/particles.h"

//------------------------------------------------------------------------------

class ModelLayers : public RealSpace::Model
{
public:
    ModelLayers();
    void showKind(RealSpace::Particles::EShape);

private:
    QVector<RealSpace::Particles::Particle*> ps;
};

//------------------------------------------------------------------------------
#endif
