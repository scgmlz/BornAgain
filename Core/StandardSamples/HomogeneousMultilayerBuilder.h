// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/HomogeneousMultilayerBuilder.h
//! @brief     Defines class HomogeneousMultilayerBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef HOMOGENEOUSMULTILAYERBUILDER_H_
#define HOMOGENEOUSMULTILAYERBUILDER_H_

#include "IMultiLayerBuilder.h"

//! Builds a sample with 10 interchanging homogeneous layers of Ti and Ni on silicone substrate.
//! Ti is 70 angstroms thick, Ni is 30 angstroms thick.
//! No absorption, no roughness, target wavelength is 1.54 angstroms.
//! @ingroup standard_samples

class BA_CORE_API_ HomogeneousMultilayerBuilder : public IMultiLayerBuilder
{
public:
    HomogeneousMultilayerBuilder();
    MultiLayer* buildSample() const;

private:
    size_t m_number_of_layers;
    double m_delta_ti;
    double m_delta_ni;
    double m_delta_si;
    double m_thick_ti;
    double m_thick_ni;
};

#endif /* HOMOGENEOUSMULTILAYERBUILDER_H_ */
