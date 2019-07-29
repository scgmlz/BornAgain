// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/IParticle.h
//! @brief     Defines interface IParticle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IPARTICLE_H
#define IPARTICLE_H

#include "IAbstractParticle.h"
#include "Rotations.h"
#include "SafePointerVector.h"
#include "SlicedParticle.h"
#include "Vectors3D.h"
#include "ZLimits.h"
#include <memory>

//! Vertical extension of a particle, specified by bottom and top z coordinate.
struct ParticleLimits
{
    double m_bottom;
    double m_top;
};

//! Pure virtual base class for Particle, ParticleComposition, ParticleCoreShell, MesoCrystal.
//! Provides position/rotation and form factor. Abundance is inherited from IAbstractParticle.
//!
//! @ingroup samples

class BA_CORE_API_ IParticle : public IAbstractParticle
{
public:
    ~IParticle() {}
    IParticle* clone() const  override=0;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    //! Create a form factor for this particle
    virtual IFormFactor* createFormFactor() const;

    //! Create a sliced form factor for this particle
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
    void translate(kvector_t translation) override final;

    //! Returns rotation object
    const IRotation* rotation() const;

    //! Sets transformation.
    void setRotation(const IRotation& rotation);

    //! Rotates the particle
    void rotate(const IRotation& rotation) override final;

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
    std::unique_ptr<IRotation> mP_rotation;
};

#endif // IPARTICLE_H
