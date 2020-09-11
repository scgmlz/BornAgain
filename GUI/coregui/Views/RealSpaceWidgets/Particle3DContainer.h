// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/Particle3DContainer.h
//! @brief     Implements namespace TransformTo3D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_PARTICLE3DCONTAINER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_PARTICLE3DCONTAINER_H

#include "Wrap/WinDllMacros.h"
#include <QString>
#include <memory>
#include <vector>

namespace RealSpace
{
namespace Particles
{
class Particle;
}
} // namespace RealSpace

class BA_CORE_API_ Particle3DContainer
{
public:
    Particle3DContainer() : m_cumulativeAbundance(0) {}
    Particle3DContainer(const Particle3DContainer& other);          // copy constructor
    Particle3DContainer& operator=(const Particle3DContainer& rhs); // copy assignment
    ~Particle3DContainer() noexcept;

    Particle3DContainer(Particle3DContainer&& other) noexcept;            // move constructor
    Particle3DContainer& operator=(Particle3DContainer&& other) noexcept; // move assignment

    void clearContainer();

    size_t containerSize() const { return m_containerParticles.size(); }
    double cumulativeAbundance() const { return m_cumulativeAbundance; }
    const QString particleType() const { return m_containerType; }
    bool particle3DBlend(const size_t& index) const { return m_containerParticlesBlend.at(index); }

    void addParticle(RealSpace::Particles::Particle* particle3D, bool blend);
    void setCumulativeAbundance(double cumulativeAbundance);
    void setParticleType(QString particleType);

    std::unique_ptr<RealSpace::Particles::Particle> createParticle(const size_t& index) const;

private:
    std::vector<RealSpace::Particles::Particle*> m_containerParticles;
    // Contains the constituents of the 3D Particle (e.g. core and shell of a ParticleCoreShell)
    double m_cumulativeAbundance;
    QString m_containerType; // type of 3D Particle e.g. ParticleType, ParticleCompositionType etc.
    std::vector<bool> m_containerParticlesBlend;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_PARTICLE3DCONTAINER_H
