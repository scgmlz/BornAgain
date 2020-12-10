//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Specular/SpecularStrategyBuilder.h
//! @brief     Defines class SpecularStrategyBuilder.
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
#ifndef BORNAGAIN_SAMPLE_SPECULAR_SPECULARSTRATEGYBUILDER_H
#define BORNAGAIN_SAMPLE_SPECULAR_SPECULARSTRATEGYBUILDER_H

#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Specular/ISpecularStrategy.h"

class SpecularStrategyBuilder {

public:
    static std::unique_ptr<ISpecularStrategy> build(const MultiLayer& sample, const bool magnetic);
};

#endif // BORNAGAIN_SAMPLE_SPECULAR_SPECULARSTRATEGYBUILDER_H
#endif // USER_API
