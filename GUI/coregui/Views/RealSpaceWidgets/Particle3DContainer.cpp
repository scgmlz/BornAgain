// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/Particle3DContainer.cpp
//! @brief     Implements namespace TransformTo3D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/RealSpaceWidgets/Particle3DContainer.h"
#include "GUI/ba3d/model/particles.h"

// copy constructor
Particle3DContainer::Particle3DContainer(const Particle3DContainer& other)
    : m_cumulativeAbundance(other.m_cumulativeAbundance), m_containerType(other.m_containerType)
{
    m_containerParticles.resize(other.m_containerParticles.size());
    for (size_t i = 0; i < m_containerParticles.size(); ++i)
        m_containerParticles[i] =
            new RealSpace::Particles::Particle(*other.m_containerParticles[i]);

    m_containerParticlesBlend.resize(other.m_containerParticlesBlend.size());
    for (size_t i = 0; i < m_containerParticlesBlend.size(); ++i)
        m_containerParticlesBlend[i] = other.m_containerParticlesBlend[i];
}

// copy assignment
Particle3DContainer& Particle3DContainer::operator=(const Particle3DContainer& rhs)
{
    if (this != &rhs) {
        clearContainer();
        m_containerParticles.resize(rhs.containerSize());
        for (size_t i = 0; i < m_containerParticles.size(); ++i)
            m_containerParticles[i] =
                new RealSpace::Particles::Particle(*rhs.m_containerParticles[i]);

        m_cumulativeAbundance = rhs.m_cumulativeAbundance;
        m_containerType = rhs.m_containerType;

        m_containerParticlesBlend.resize(rhs.m_containerParticlesBlend.size());
        for (size_t i = 0; i < m_containerParticlesBlend.size(); ++i)
            m_containerParticlesBlend[i] = rhs.m_containerParticlesBlend[i];
    }
    return *this;
}

// destructor
Particle3DContainer::~Particle3DContainer() noexcept
{
    clearContainer();
}

// move constructor
Particle3DContainer::Particle3DContainer(Particle3DContainer&& other) noexcept
    : m_containerParticles(std::move(other.m_containerParticles)),
      m_cumulativeAbundance(std::move(other.m_cumulativeAbundance)),
      m_containerType(std::move(other.m_containerType)),
      m_containerParticlesBlend(std::move(other.m_containerParticlesBlend))
{
}

// move assignment
Particle3DContainer& Particle3DContainer::operator=(Particle3DContainer&& rhs) noexcept
{
    if (this != &rhs) {
        clearContainer();
        m_containerParticles = std::move(rhs.m_containerParticles);
        m_cumulativeAbundance = std::move(rhs.m_cumulativeAbundance);
        m_containerType = std::move(rhs.m_containerType);
        m_containerParticlesBlend = std::move(rhs.m_containerParticlesBlend);
    }
    return *this;
}

void Particle3DContainer::clearContainer()
{
    for (auto it = m_containerParticles.begin(); it != m_containerParticles.end(); ++it)
        delete (*it);

    m_containerParticles.clear();
    m_containerParticlesBlend.clear();
}

void Particle3DContainer::addParticle(RealSpace::Particles::Particle* particle3D, bool blend)
{
    m_containerParticles.emplace_back(particle3D);
    m_containerParticlesBlend.emplace_back(blend);
}

void Particle3DContainer::setCumulativeAbundance(double cumulativeAbundance)
{
    m_cumulativeAbundance = cumulativeAbundance;
}

void Particle3DContainer::setParticleType(QString particleType)
{
    m_containerType = particleType;
}

std::unique_ptr<RealSpace::Particles::Particle>
Particle3DContainer::createParticle(const size_t& index) const
{
    auto particle = new RealSpace::Particles::Particle(*m_containerParticles.at(index));
    return std::unique_ptr<RealSpace::Particles::Particle>(particle);
}
