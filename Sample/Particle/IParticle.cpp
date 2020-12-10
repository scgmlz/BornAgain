//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Particle/IParticle.cpp
//! @brief     Implements interface IParticle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Particle/IParticle.h"
#include "Param/Base/RealParameter.h"
#include "Sample/Particle/SlicedParticle.h"
#include "Sample/Scattering/FormFactorDecoratorPositionFactor.h"
#include "Sample/Scattering/Rotations.h"

IParticle::~IParticle() = default;

IFormFactor* IParticle::createFormFactor() const {
    return createSlicedParticle(ZLimits{}).m_slicedff.release();
}

SlicedParticle IParticle::createSlicedParticle(ZLimits) const {
    throw std::runtime_error("IParticle::createSlicedParticle error: "
                             "not implemented!");
}

void IParticle::translate(kvector_t translation) {
    m_position += translation;
}

const IRotation* IParticle::rotation() const {
    return m_rotation.get();
}

void IParticle::setRotation(const IRotation& rotation) {
    m_rotation.reset(rotation.clone());
    registerChild(m_rotation.get());
}

void IParticle::rotate(const IRotation& rotation) {
    if (m_rotation) {
        m_rotation.reset(createProduct(rotation, *m_rotation));
    } else {
        m_rotation.reset(rotation.clone());
    }
    m_position = rotation.transformed(m_position);
    registerChild(m_rotation.get());
}

std::vector<const INode*> IParticle::getChildren() const {
    return std::vector<const INode*>() << m_rotation;
}

void IParticle::registerAbundance(bool make_registered) {
    if (make_registered) {
        if (!parameter("Abundance"))
            registerParameter("Abundance", &m_abundance);
    } else {
        removeParameter("Abundance");
    }
}

void IParticle::registerPosition(bool make_registered) {
    if (make_registered) {
        if (!parameter(XComponentName("Position"))) {
            registerVector("Position", &m_position, "nm");
        }
    } else {
        removeVector("Position");
    }
}

SafePointerVector<IParticle> IParticle::decompose() const {
    SafePointerVector<IParticle> result;
    result.push_back(this->clone());
    return result;
}

ParticleLimits IParticle::bottomTopZ() const {
    std::unique_ptr<IFormFactor> P_ff(createFormFactor());
    std::unique_ptr<IRotation> P_rot(new IdentityRotation);
    return {P_ff->bottomZ(*P_rot), P_ff->topZ(*P_rot)};
}

IRotation* IParticle::createComposedRotation(const IRotation* p_rotation) const {
    if (p_rotation) {
        if (m_rotation)
            return createProduct(*p_rotation, *m_rotation);
        else
            return p_rotation->clone();
    } else {
        if (m_rotation)
            return m_rotation->clone();
        else
            return nullptr;
    }
}

kvector_t IParticle::composedTranslation(const IRotation* p_rotation, kvector_t translation) const {
    if (p_rotation) {
        return translation + p_rotation->transformed(m_position);
    } else {
        return translation + m_position;
    }
}

void IParticle::registerParticleProperties() {
    registerAbundance();
    registerPosition();
}
