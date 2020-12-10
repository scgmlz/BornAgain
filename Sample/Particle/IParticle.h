//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Particle/IParticle.h
//! @brief     Defines interface IParticle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_PARTICLE_IPARTICLE_H
#define BORNAGAIN_SAMPLE_PARTICLE_IPARTICLE_H

#include "Base/Types/SafePointerVector.h"
#include "Sample/Particle/IAbstractParticle.h"
#include <memory>

struct SlicedParticle;
struct ParticleLimits;
class Rotations;
class ZLimits;

//! Abstract base class for Particle, ParticleComposition, ParticleCoreShell, MesoCrystal.
//! Provides position/rotation and form factor. Abundance is inherited from IAbstractParticle.
//!
//! @ingroup samples

class IParticle : public IAbstractParticle {
public:
    ~IParticle();
    IParticle* clone() const override = 0;

    //! Creates a form factor for this particle
    virtual IFormFactor* createFormFactor() const;

    //! Creates a sliced form factor for this particle
    virtual SlicedParticle createSlicedParticle(ZLimits limits) const;

    //! Returns particle position.
    kvector_t position() const { return m_position; }

    //! Sets relative position of the particle's reference point in the
    //! coordinate system of parent.
    //! @param position: relative position vector (components are in nanometers)
    void setPosition(kvector_t position) { m_position = position; }

    //! Sets relative position of the particle's reference point in the
    //! coordinate system of parent.
    //! @param x: x-coordinate in nanometers
    //! @param y: y-coordinate in nanometers
    //! @param z: z-coordinate in nanometers
    void setPosition(double x, double y, double z) { m_position = kvector_t(x, y, z); }

    //! Translates the particle
    void translate(kvector_t translation) final;

    //! Returns rotation object
    const IRotation* rotation() const;

    //! Sets transformation.
    void setRotation(const IRotation& rotation);

    //! Rotates the particle
    void rotate(const IRotation& rotation) final;

    std::vector<const INode*> getChildren() const override;

    void registerAbundance(bool make_registered = true);

    //! Registers the three components of its position
    void registerPosition(bool make_registered = true);

    //! Decompose in constituent IParticle objects
    virtual SafePointerVector<IParticle> decompose() const;

    //! Top and bottom z-coordinate
    virtual ParticleLimits bottomTopZ() const;

protected:
    //! Creates a composed IRotation object
    IRotation* createComposedRotation(const IRotation* p_rotation) const;

    //! Gets a composed translation vector
    kvector_t composedTranslation(const IRotation* p_rotation, kvector_t translation) const;

    //! Registers abundance and position
    void registerParticleProperties();

    kvector_t m_position;
    std::unique_ptr<IRotation> m_rotation;
};

#endif // BORNAGAIN_SAMPLE_PARTICLE_IPARTICLE_H
#endif // USER_API
