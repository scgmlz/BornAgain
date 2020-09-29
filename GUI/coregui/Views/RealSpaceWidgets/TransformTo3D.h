// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/TransformTo3D.h
//! @brief     Defines namespace TransformTo3D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_TRANSFORMTO3D_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_TRANSFORMTO3D_H

#include "Core/Vector/Vectors3D.h"
#include "GUI/ba3d/model/layer.h"
#include "GUI/ba3d/model/particles.h"
#include <memory>

class SessionItem;
class SceneGeometry;
class IFormFactor;

//! Collection of utility functions to build 3D objects from session items.

namespace TransformTo3D
{

double visualLayerThickness(const SessionItem& layerItem, const SceneGeometry& sceneGeometry);

std::unique_ptr<RealSpace::Layer> createLayer(const SessionItem& layerItem,
                                              const SceneGeometry& sceneGeometry,
                                              const QVector3D& origin = {});

std::unique_ptr<RealSpace::Particles::Particle> createParticle3D(const SessionItem& particleItem);

std::unique_ptr<RealSpace::Particles::Particle>
createParticlefromIFormFactor(const IFormFactor* ff);

} // namespace TransformTo3D

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_TRANSFORMTO3D_H
