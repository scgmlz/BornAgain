// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularStrategyBuilder.h
//! @brief     Defines class SpecularStrategyBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARSTRATEGYBUILDER_H
#define SPECULARSTRATEGYBUILDER_H

#include "ISpecularStrategy.h"
#include "MultiLayer.h"
#include "RoughnessModels.h"

class SpecularStrategyBuilder
{

public:
    static std::unique_ptr<ISpecularStrategy> build(const MultiLayer& sample, const bool magnetic);
};

#endif // SPECULARSTRATEGYBUILDER_H
