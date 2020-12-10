//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/PlainMultiLayerBySLDBuilder.h
//! @brief     Declares the class PlainMultiLayerBySLDBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_PLAINMULTILAYERBYSLDBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_PLAINMULTILAYERBYSLDBUILDER_H

#include "Sample/SampleBuilderEngine/ISampleBuilder.h"

//! Builds a sample with 10 interchanging homogeneous layers of Ti and Ni on silicone substrate.
//! Ti is 70 angstroms thick, Ni is 30 angstroms thick.
//! @ingroup standard_samples

class PlainMultiLayerBySLDBuilder : public ISampleBuilder {
public:
    PlainMultiLayerBySLDBuilder(int n_layers = 10);
    MultiLayer* buildSample() const override; // passes ownership

protected:
    struct MaterialData {
        double sld_real; //!< real part of sld in AA^{-2}
        double sld_imag; //!< imaginary part of sld in AA^{-2}
    };
    int m_number_of_layers;
    MaterialData m_si;
    MaterialData m_ti;
    MaterialData m_ni;
    double m_thick_ti; //!< thickness of titanium layer
    double m_thick_ni; //!< thickness of Ni layer
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_PLAINMULTILAYERBYSLDBUILDER_H
#endif // USER_API
