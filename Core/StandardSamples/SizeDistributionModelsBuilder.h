// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/SizeDistributionModelsBuilder.h
//! @brief     Defines various sample builder classes to test DA, LMA, SSCA approximations
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_SIZEDISTRIBUTIONMODELSBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_SIZEDISTRIBUTIONMODELSBUILDER_H

#include "Core/Multilayer/IMultiLayerBuilder.h"

//! Creates the sample demonstrating size distribution model in decoupling approximation.
//! Equivalent of Examples/python/simulation/ex03_InterferenceFunctions/ApproximationDA.py
//! @ingroup standard_samples

class BA_CORE_API_ SizeDistributionDAModelBuilder : public IMultiLayerBuilder
{
public:
    SizeDistributionDAModelBuilder() {}
    MultiLayer* buildSample() const;
};

//! Creates the sample demonstrating size distribution model in local monodisperse approximation.
//! Equivalent of Examples/python/simulation/ex03_InterferenceFunctions/ApproximationLMA.py
//! @ingroup standard_samples

class BA_CORE_API_ SizeDistributionLMAModelBuilder : public IMultiLayerBuilder
{
public:
    SizeDistributionLMAModelBuilder() {}
    MultiLayer* buildSample() const;
};

//! Creates the sample demonstrating size distribution model in size space coupling approximation.
//! Equivalent of Examples/python/simulation/ex03_InterferenceFunctions/ApproximationSSCA.py
//! @ingroup standard_samples

class BA_CORE_API_ SizeDistributionSSCAModelBuilder : public IMultiLayerBuilder
{
public:
    SizeDistributionSSCAModelBuilder() {}
    MultiLayer* buildSample() const;
};

//! Builds sample: size spacing correlation approximation (IsGISAXS example #15).
//! @ingroup standard_samples

class BA_CORE_API_ CylindersInSSCABuilder : public IMultiLayerBuilder
{
public:
    CylindersInSSCABuilder() {}
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_SIZEDISTRIBUTIONMODELSBUILDER_H
