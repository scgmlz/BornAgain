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

#ifndef REALSPACEBUILDERUTILS_H
#define REALSPACEBUILDERUTILS_H

#include "WinDllMacros.h"
#include <QVector>
#include <QVector3D>
#include <memory>

class RealSpaceModel;
class SessionItem;
class SceneGeometry;
class RealSpaceBuilder;
class IRotation;
class Particle;
class ParticleComposition;
class ParticleCoreShell;
class ParticleDistribution;
class IInterferenceFunction;
namespace RealSpace{ namespace Particles { class Particle; } }

class BA_CORE_API_ Particle3DType
{
public:
    Particle3DType() {m_cumulative_abundance = 0;}
    Particle3DType(const Particle3DType& p3D);
    Particle3DType& operator=(const Particle3DType& right);
    ~Particle3DType();

    void clear3Dparticles();

    const QVector<RealSpace::Particles::Particle*> get3Dparticles() const {return m_3Dparticles; }
    double getCumulativeAbundance() const {return m_cumulative_abundance; }
    const QString getType() const {return m_type; }

    void add3DParticle(RealSpace::Particles::Particle* particle3D);
    void setCumulativeAbundance(double cumulative_abundance);
    void setType(QString type);

    std::unique_ptr<RealSpace::Particles::Particle> createParticle(const int &index) const;

private:
    QVector<RealSpace::Particles::Particle*> m_3Dparticles;
    double m_cumulative_abundance;
    QString m_type;
};

namespace RealSpaceBuilderUtils
{
// compute cumulative abundances of particles
BA_CORE_API_ QVector<double> computeCumulativeAbundances(const SessionItem& layoutItem);

BA_CORE_API_ void populateParticlesAtLatticePositions(
        QVector<QVector<double>> lattice_positions, const QVector<Particle3DType> &particle3DType_vector,
        RealSpaceModel *model, const SceneGeometry& sceneGeometry, const RealSpaceBuilder *builder3D);

// No interference - random distribution of particles
BA_CORE_API_ void populateRandomDistribution(RealSpaceModel* model,
                                             const SessionItem& layoutItem,
                                             const QVector<Particle3DType> &particle3DType_vector,
                                             const SceneGeometry& sceneGeometry,
                                             const RealSpaceBuilder *builder3D);

BA_CORE_API_ QVector<QVector<double>> computeRandomDistributionLatticePositions(
        const SessionItem& layoutItem, const SceneGeometry &sceneGeometry);

// InterferenceFunction2DLatticeType
BA_CORE_API_ void populateInterference2DLatticeType(
        const IInterferenceFunction* interference, RealSpaceModel* model,
        const QVector<Particle3DType> &particle3DType_vector, const SceneGeometry &sceneGeometry,
        const RealSpaceBuilder *builder3D);

BA_CORE_API_ QVector<QVector<double>> computeInterference2DLatticePositions(
        double l1, double l2, double l_alpha, double l_xi, const SceneGeometry& sceneGeometry);

// InterferenceFunction1DLatticeType
BA_CORE_API_ void populateInterference1DLatticeType(
        const IInterferenceFunction *interference, RealSpaceModel* model,
        const QVector<Particle3DType> &particle3DType_vector, const SceneGeometry &sceneGeometry,
        const RealSpaceBuilder *builder3D);

// Implement Rotation of a 3D particle using parameters from IRotation Object
BA_CORE_API_ QVector3D implementParticleRotationfromIRotation(const IRotation *&rotation);

//! Apply transformations (translation, rotation) to a 3D Particle
//! or to a particle belonging to a ParticleComposition
BA_CORE_API_ void applyParticleTransformations(const Particle *particle,
                                               RealSpace::Particles::Particle *particle3D,
                                               const QVector3D &origin);

//! Apply transformations (translation, rotation) to a particle (core/shell) in a ParticleCoreShell
BA_CORE_API_ void applyParticleCoreShellTransformations(const Particle *particle,
                                                        RealSpace::Particles::Particle *particle3D,
                                                        const ParticleCoreShell *particleCoreShell,
                                                        const QVector3D &origin);

// Apply color to a 3D particle
BA_CORE_API_ void applyParticleColor(const Particle *particle,
                                     RealSpace::Particles::Particle *particle3D,
                                     double alpha = 1);

// Methods to populate different Particle Types
BA_CORE_API_ void populateParticleComposition(RealSpaceModel *model,
                                              const ParticleComposition* particleComposition,
                                              const QVector3D &origin);

BA_CORE_API_ void populateParticleCoreShell(RealSpaceModel *model,
                                            const ParticleCoreShell* particleCoreShell,
                                            const QVector3D &origin);

BA_CORE_API_ void populateParticleDistribution(RealSpaceModel *model,
                                               const ParticleDistribution* particleDistribution,
                                               const QVector3D &origin);

BA_CORE_API_ void populateSingleParticle(RealSpaceModel *model, const Particle* particle,
                                         const QVector3D &origin);

BA_CORE_API_ QVector<Particle3DType> getParticle3DTypeVector(const SessionItem &layoutItem);

BA_CORE_API_ Particle3DType getSingleParticle3DType(const SessionItem* particleItem,
                                                    double total_abundance);

} // namespace RealSpaceBuilderUtils

#endif // REALSPACEBUILDERUTILS_H
