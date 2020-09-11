// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilderUtils.h
//! @brief     Defines RealSpaceBuilderUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_REALSPACEBUILDERUTILS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_REALSPACEBUILDERUTILS_H

#include "Core/Scattering/Rotations.h"
#include "Core/Vector/Vectors3D.h"
#include "Wrap/WinDllMacros.h"
#include <QVector3D>
#include <memory>
#include <utility>

class RealSpaceModel;
class SessionItem;
class SceneGeometry;
class RealSpaceBuilder;
class IRotation;
class MesoCrystalItem;
class Particle;
class ParticleComposition;
class ParticleCoreShell;
class ParticleDistribution;
class IInterferenceFunction;
class Particle3DContainer;
class InterferenceFunction2DParaCrystal;
namespace RealSpace
{
struct Vector3D;
namespace Particles
{
class Particle;
}
} // namespace RealSpace

namespace RealSpaceBuilderUtils
{
// compute cumulative abundances of particles
BA_CORE_API_ QVector<double> computeCumulativeAbundances(const SessionItem& layoutItem);

BA_CORE_API_ void populateParticlesAtLatticePositions(
    const std::vector<std::vector<double>>& lattice_positions,
    const std::vector<Particle3DContainer>& particle3DContainer_vector, RealSpaceModel* model,
    const SceneGeometry& sceneGeometry, const RealSpaceBuilder* builder3D);

// Implement Rotation of a 3D particle using parameters from IRotation Object
BA_CORE_API_ RealSpace::Vector3D implementParticleRotationfromIRotation(const IRotation*& rotation);

//! Apply transformations (translation, rotation) to a 3D Particle
//! or to a particle belonging to a ParticleComposition
BA_CORE_API_ void applyParticleTransformations(const Particle& particle,
                                               RealSpace::Particles::Particle& particle3D,
                                               const kvector_t& origin = kvector_t(0, 0, 0));

//! Apply transformations (translation, rotation) to a particle (core/shell) in a ParticleCoreShell
BA_CORE_API_ void applyParticleCoreShellTransformations(
    const Particle& particle, RealSpace::Particles::Particle& particle3D,
    const ParticleCoreShell& particleCoreShell, const kvector_t& origin = kvector_t(0, 0, 0));

// Apply color to a 3D particle
BA_CORE_API_ void applyParticleColor(const Particle& particle,
                                     RealSpace::Particles::Particle& particle3D, double alpha = 1);

BA_CORE_API_ std::vector<Particle3DContainer>
particle3DContainerVector(const SessionItem& layoutItem, const QVector3D& origin = {});

BA_CORE_API_ Particle3DContainer singleParticle3DContainer(const Particle& particle,
                                                           double total_abundance = 1.0,
                                                           const QVector3D& origin = {});

BA_CORE_API_ Particle3DContainer
particleCoreShell3DContainer(const ParticleCoreShell& particleCoreShell,
                             double total_abundance = 1.0, const QVector3D& origin = {});

BA_CORE_API_ Particle3DContainer
particleComposition3DContainer(const ParticleComposition& particleComposition3DContainer,
                               double total_abundance = 1.0, const QVector3D& origin = {});

BA_CORE_API_ std::vector<Particle3DContainer>
particleDistribution3DContainer(const ParticleDistribution& particleDistribution,
                                double total_abundance = 1.0, const QVector3D& origin = {});

BA_CORE_API_ Particle3DContainer mesoCrystal3DContainer(const MesoCrystalItem& mesoCrystalItem,
                                                        double total_abundance = 1.0,
                                                        const QVector3D& origin = {});

} // namespace RealSpaceBuilderUtils

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_REALSPACEBUILDERUTILS_H
