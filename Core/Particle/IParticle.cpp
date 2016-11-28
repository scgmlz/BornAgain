// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/IParticle.cpp
//! @brief     Implements interface IParticle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IParticle.h"
#include "BornAgainNamespace.h"
#include "FormFactorDecoratorPositionFactor.h"
#include "RealParameter.h"

IFormFactor* IParticle::createFormFactor() const
{
    return createTransformedFormFactor(nullptr, kvector_t());
}

void IParticle::setRotation(const IRotation& rotation)
{
    if (mP_rotation)
        deregisterChild(mP_rotation.get());
    mP_rotation.reset(rotation.clone());
    registerChild(mP_rotation.get());
}

void IParticle::applyRotation(const IRotation& rotation)
{
    if (mP_rotation) {
        deregisterChild(mP_rotation.get());
        mP_rotation.reset(createProduct(rotation, *mP_rotation));
    } else {
        mP_rotation.reset(rotation.clone());
    }
    m_position = rotation.getTransform3D().transformed(m_position);
    registerChild(mP_rotation.get());
}

void IParticle::applyTranslation(kvector_t displacement)
{
    m_position += displacement;
}

IRotation* IParticle::createComposedRotation(const IRotation* p_rotation) const
{
    if (p_rotation) {
        if (mP_rotation)
            return createProduct(*p_rotation, *mP_rotation);
        else
            return p_rotation->clone();
    } else {
        if (mP_rotation)
            return mP_rotation->clone();
        else
            return nullptr;
    }
}

kvector_t IParticle::getComposedTranslation(
    const IRotation* p_rotation, kvector_t translation) const
{
    if (p_rotation) {
        Transform3D transform = p_rotation->getTransform3D();
        return translation + transform.transformed(m_position);
    } else {
        return translation + m_position;
    }
}

void IParticle::registerPosition()
{
    registerParameter(BornAgain::PositionX, &m_position[0]).setUnit("nm");
    registerParameter(BornAgain::PositionY, &m_position[1]).setUnit("nm");
    registerParameter(BornAgain::PositionZ, &m_position[2]).setUnit("nm");
}

const IRotation* IParticle::getRotation() const
{
    return mP_rotation.get();
}
