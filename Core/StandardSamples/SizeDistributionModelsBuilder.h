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

#include "Core/SampleBuilderEngine/ISampleBuilder.h"

//! Creates the sample demonstrating size distribution model in decoupling approximation.
//! Equivalent of Examples/python/simulation/ex03_InterferenceFunctions/ApproximationDA.py
//! @ingroup standard_samples

class SizeDistributionDAModelBuilder : public ISampleBuilder
{
public:
    MultiLayer* buildSample() const;
};

//! Creates the sample demonstrating size distribution model in local monodisperse approximation.
//! Equivalent of Examples/python/simulation/ex03_InterferenceFunctions/ApproximationLMA.py
//! @ingroup standard_samples

class SizeDistributionLMAModelBuilder : public ISampleBuilder
{
public:
    MultiLayer* buildSample() const;
};

//! Creates the sample demonstrating size distribution model in size space coupling approximation.
//! Equivalent of Examples/python/simulation/ex03_InterferenceFunctions/ApproximationSSCA.py
//! @ingroup standard_samples

class SizeDistributionSSCAModelBuilder : public ISampleBuilder
{
public:
    MultiLayer* buildSample() const;
};

//! Builds sample: size spacing correlation approximation (IsGISAXS example #15).
//! @ingroup standard_samples

class CylindersInSSCABuilder : public ISampleBuilder
{
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_SIZEDISTRIBUTIONMODELSBUILDER_H
