// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/MesoCrystal.cpp
//! @brief     Implements class MesoCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MesoCrystal.h"
#include "BornAgainNamespace.h"
#include "FormFactorDecoratorPositionFactor.h"
#include "FormFactorDecoratorRotation.h"
#include "IClusteredParticles.h"

MesoCrystal::MesoCrystal(IClusteredParticles* p_particle_structure, IFormFactor* p_form_factor)
    : mp_particle_structure(p_particle_structure), mp_meso_form_factor(p_form_factor)
{
    initialize();
}

MesoCrystal::MesoCrystal(const IClusteredParticles& particle_structure, IFormFactor& form_factor)
    : mp_particle_structure(particle_structure.clone()), mp_meso_form_factor(form_factor.clone())
{
    initialize();
}

MesoCrystal::~MesoCrystal()
{
    delete mp_meso_form_factor;
    delete mp_particle_structure;
}

MesoCrystal* MesoCrystal::clone() const
{
    MesoCrystal* p_result =
        new MesoCrystal(mp_particle_structure->clone(), mp_meso_form_factor->clone());
    p_result->setAbundance(m_abundance);
    if (mP_rotation)
        p_result->setRotation(*mP_rotation);
    p_result->setPosition(m_position);
    return p_result;
}

MesoCrystal* MesoCrystal::cloneInvertB() const
{
    MesoCrystal* p_result =
        new MesoCrystal(mp_particle_structure->cloneInvertB(), mp_meso_form_factor->clone());
    p_result->setAbundance(m_abundance);
    if (mP_rotation)
        p_result->setRotation(*mP_rotation);
    p_result->setPosition(m_position);
    return p_result;
}

void MesoCrystal::accept(ISampleVisitor* visitor) const { visitor->visit(this); }

void MesoCrystal::setAmbientMaterial(const IMaterial& material)
{
    mp_particle_structure->setAmbientMaterial(material);
}

const IMaterial* MesoCrystal::getAmbientMaterial() const
{
    return mp_particle_structure ? mp_particle_structure->getAmbientMaterial() : nullptr;
}

IFormFactor*
MesoCrystal::createTransformedFormFactor(const IRotation* p_rotation, kvector_t translation) const
{
    if (!mp_particle_structure || !mp_meso_form_factor)
        return 0;
    std::unique_ptr<IRotation> P_total_rotation(createComposedRotation(p_rotation));
    kvector_t total_position = getComposedTranslation(p_rotation, translation);
    std::unique_ptr<IFormFactor> P_transformed_meso(createTransformationDecoratedFormFactor(
        *mp_meso_form_factor, P_total_rotation.get(), total_position));
    IFormFactor* p_result = mp_particle_structure->createTotalFormFactor(
        *P_transformed_meso, P_total_rotation.get(), total_position);
    return p_result;
}

IFormFactor* MesoCrystal::createTransformationDecoratedFormFactor(
    const IFormFactor& bare_ff, const IRotation* p_rotation, kvector_t translation) const
{
    IFormFactor* p_intermediate;
    if (p_rotation) {
        p_intermediate = new FormFactorDecoratorRotation(bare_ff, *p_rotation);
    } else {
        p_intermediate = bare_ff.clone();
    }
    IFormFactor* p_result;
    if (translation != kvector_t()) {
        p_result = new FormFactorDecoratorPositionFactor(*p_intermediate, translation);
        delete p_intermediate;
    } else {
        p_result = p_intermediate;
    }
    return p_result;
}

void MesoCrystal::initialize()
{
    setName(BornAgain::MesoCrystalType);
    registerPosition();
    registerChild(mp_particle_structure);
    registerChild(mp_meso_form_factor);
}
