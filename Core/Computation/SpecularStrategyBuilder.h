// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SpecularStrategyBuilder.h
//! @brief     Defines class SpecularStrategyBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_COMPUTATION_SPECULARSTRATEGYBUILDER_H
#define BORNAGAIN_CORE_COMPUTATION_SPECULARSTRATEGYBUILDER_H

#include "Core/Multilayer/ISpecularStrategy.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Multilayer/RoughnessModels.h"

class SpecularStrategyBuilder
{

public:
    static std::unique_ptr<ISpecularStrategy> build(const MultiLayer& sample, const bool magnetic);
};

#endif // BORNAGAIN_CORE_COMPUTATION_SPECULARSTRATEGYBUILDER_H
