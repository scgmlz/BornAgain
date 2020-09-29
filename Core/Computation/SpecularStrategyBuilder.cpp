// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SpecularStrategyBuilder.cpp
//! @brief     Implements class SpecularStrategyBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Computation/SpecularStrategyBuilder.h"
#include "Core/Multilayer/MultiLayerUtils.h"
#include "Core/Multilayer/SpecularMagneticNewNCStrategy.h"
#include "Core/Multilayer/SpecularMagneticNewTanhStrategy.h"
#include "Core/Multilayer/SpecularScalarNCStrategy.h"
#include "Core/Multilayer/SpecularScalarTanhStrategy.h"

std::unique_ptr<ISpecularStrategy> SpecularStrategyBuilder::build(const MultiLayer& sample,
                                                                  const bool magnetic)
{
    auto roughnessModel = sample.roughnessModel();

    if (magnetic) {
        if (roughnessModel == RoughnessModel::TANH || roughnessModel == RoughnessModel::DEFAULT) {

            return std::make_unique<SpecularMagneticNewTanhStrategy>();

        } else if (roughnessModel == RoughnessModel::NEVOT_CROCE) {

            return std::make_unique<SpecularMagneticNewNCStrategy>();

        } else
            throw std::logic_error("Invalid roughness model");

    } else {
        if (roughnessModel == RoughnessModel::TANH || roughnessModel == RoughnessModel::DEFAULT) {
            return std::make_unique<SpecularScalarTanhStrategy>();

        } else if (roughnessModel == RoughnessModel::NEVOT_CROCE) {

            return std::make_unique<SpecularScalarNCStrategy>();

        } else
            throw std::logic_error("Invalid roughness model");
    }
}
