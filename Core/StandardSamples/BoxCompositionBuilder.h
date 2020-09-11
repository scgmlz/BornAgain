// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/BoxCompositionBuilder.h
//! @brief     Defines classes of BoxCompositionBuilder family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_BOXCOMPOSITIONBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_BOXCOMPOSITIONBUILDER_H

#include "Core/Material/Material.h"
#include "Core/Multilayer/IMultiLayerBuilder.h"

class MultiLayer;
class ParticleComposition;

//! Parent class to test all kind of compositions made out of boxes.
//! Reproduces Python functional test transform_BoxComposition.py
//! @ingroup standard_samples

class BA_CORE_API_ BoxCompositionBuilder : public IMultiLayerBuilder
{
public:
    BoxCompositionBuilder();
    virtual ~BoxCompositionBuilder();

protected:
    MultiLayer* createMultiLayer(const ParticleComposition& composition) const;
    const Material m_particleMaterial;
    const double m_layer_thickness;
    const double m_length;
    const double m_width;
    const double m_height;
};

//! Two boxes in particle composition rotated in X by 90 degrees.
//! @ingroup standard_samples

class BA_CORE_API_ BoxCompositionRotateXBuilder : public BoxCompositionBuilder
{
public:
    BoxCompositionRotateXBuilder() {}
    MultiLayer* buildSample() const;
};

//! Two boxes in particle composition rotated in Y by 90 degrees.
//! @ingroup standard_samples

class BA_CORE_API_ BoxCompositionRotateYBuilder : public BoxCompositionBuilder
{
public:
    BoxCompositionRotateYBuilder() {}
    MultiLayer* buildSample() const;
};

//! Two boxes in particle composition rotated in Z by 90 degrees.
//! @ingroup standard_samples

class BA_CORE_API_ BoxCompositionRotateZBuilder : public BoxCompositionBuilder
{
public:
    BoxCompositionRotateZBuilder() {}
    MultiLayer* buildSample() const;
};

//! Two boxes in particle composition rotated in Z and Y by 90 degrees.
//! @ingroup standard_samples

class BA_CORE_API_ BoxCompositionRotateZandYBuilder : public BoxCompositionBuilder
{
public:
    BoxCompositionRotateZandYBuilder() {}
    MultiLayer* buildSample() const;
};

//! Two different boxes are first rotated and then composed, composition is then rotated.
//! @ingroup standard_samples

class BA_CORE_API_ BoxStackCompositionBuilder : public BoxCompositionBuilder
{
public:
    BoxStackCompositionBuilder() {}
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_BOXCOMPOSITIONBUILDER_H
