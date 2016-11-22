// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/RipplesBuilder.h
//! @brief     Defines classes to build various ripples.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef RIPPLESBUILDER_H
#define RIPPLESBUILDER_H

#include "IMultiLayerBuilder.h"

//! Builds sample: cosine ripple within the 1D-paracrystal model.
//! @ingroup standard_samples

class BA_CORE_API_ CosineRippleBuilder : public IMultiLayerBuilder
{
public:
    CosineRippleBuilder();
    MultiLayer* buildSample() const;

protected:
    void init_parameters();

private:
    double m_w; //width
    double m_h; //heigth
    double m_l; //length

    double m_interf_distance;
    double m_interf_width;
};


//! Builds sample: triangular ripple within the 1D-paracrystal model (from PRB 85, 235415, 2012).
//! @ingroup standard_samples

class BA_CORE_API_ TriangularRippleBuilder : public IMultiLayerBuilder
{
public:
    TriangularRippleBuilder();
    MultiLayer* buildSample() const;

protected:
    void init_parameters();

private:
    double m_w; //width
    double m_h; //heigth
    double m_l; //length
    double m_d; //asymetry
    double m_interf_distance;
    double m_interf_width;
};

#endif // RIPPLESBUILDER_H
