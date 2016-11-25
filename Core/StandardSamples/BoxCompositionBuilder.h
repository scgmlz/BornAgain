// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/BoxCompositionBuilder.h
//! @brief     Defines classes of BoxCompositionBuilder family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BOXCOMPOSITIONBUILDER_H
#define BOXCOMPOSITIONBUILDER_H

#include "IMultiLayerBuilder.h"

class ISample;
class HomogeneousMaterial;
class MultiLayer;
class ParticleComposition;

//! @class BoxCompositionBuilder
//! @ingroup standard_samples
//! @brief Parent class to test all kind of compositions made out of boxes.
//! Reproduces Python functional test transform_BoxComposition.py

class BA_CORE_API_ BoxCompositionBuilder : public IMultiLayerBuilder
{
public:
    BoxCompositionBuilder();
    virtual ~BoxCompositionBuilder();

protected:
    MultiLayer* createMultiLayer(const ParticleComposition& composition) const;
    const HomogeneousMaterial* m_particleMaterial;
    const double m_layer_thickness;
    const double m_length;
    const double m_width;
    const double m_height;
};

//! @class BoxCompositionRotateXBuilder
//! @ingroup standard_samples
//! @brief Two boxes in particle composition rotated in X by 90 degrees.

class BA_CORE_API_ BoxCompositionRotateXBuilder : public BoxCompositionBuilder
{
public:
    BoxCompositionRotateXBuilder() {}
    MultiLayer* buildSample() const;
};

//! @class BoxCompositionRotateYBuilder
//! @ingroup standard_samples
//! @brief Two boxes in particle composition rotated in Y by 90 degrees.

class BA_CORE_API_ BoxCompositionRotateYBuilder : public BoxCompositionBuilder
{
public:
    BoxCompositionRotateYBuilder() {}
    MultiLayer* buildSample() const;
};

//! @class BoxCompositionRotateZBuilder
//! @ingroup standard_samples
//! @brief Two boxes in particle composition rotated in Z by 90 degrees.

class BA_CORE_API_ BoxCompositionRotateZBuilder : public BoxCompositionBuilder
{
public:
    BoxCompositionRotateZBuilder() {}
    MultiLayer* buildSample() const;
};

//! @class BoxCompositionRotateZandYBuilder
//! @ingroup standard_samples
//! @brief Two boxes in particle composition rotated in Z and Y by 90 degrees.

class BA_CORE_API_ BoxCompositionRotateZandYBuilder : public BoxCompositionBuilder
{
public:
    BoxCompositionRotateZandYBuilder() {}
    MultiLayer* buildSample() const;
};

//! @class BoxStackCompositionBuilder
//! @ingroup standard_samples
//! @brief Two different boxes are first rotated and then composed, composition is then rotated.

class BA_CORE_API_ BoxStackCompositionBuilder : public BoxCompositionBuilder
{
public:
    BoxStackCompositionBuilder() {}
    MultiLayer* buildSample() const;
};

#endif // BOXCOMPOSITIONBUILDER_H
