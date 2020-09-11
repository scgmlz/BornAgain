// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      dev-tools/sandboxes/realSpace/demo2/modelShowcase.h
//! @brief     Defines ModelShowcase class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BA3D_MODEL_SHOWCASE_H
#define BA3D_MODEL_SHOWCASE_H

#include "GUI/ba3d/model/model.h"
#include "GUI/ba3d/model/particles.h"

//------------------------------------------------------------------------------

class ModelShowcase : public RealSpace::Model
{
public:
    using Particle = RealSpace::Particles::Particle;
    using kind = RealSpace::Particles::EShape;

    ModelShowcase();
    void showKind(kind);

private:
    Particle* p;
};

//------------------------------------------------------------------------------
#endif
