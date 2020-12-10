//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Specular/SpecularStrategyBuilder.cpp
//! @brief     Implements class SpecularStrategyBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Specular/SpecularStrategyBuilder.h"
#include "Sample/Multilayer/MultiLayerUtils.h"
#include "Sample/Specular/SpecularMagneticNCStrategy.h"
#include "Sample/Specular/SpecularMagneticTanhStrategy.h"
#include "Sample/Specular/SpecularScalarNCStrategy.h"
#include "Sample/Specular/SpecularScalarTanhStrategy.h"

std::unique_ptr<ISpecularStrategy> SpecularStrategyBuilder::build(const MultiLayer& sample,
                                                                  const bool magnetic) {
    auto roughnessModel = sample.roughnessModel();

    if (magnetic) {
        if (roughnessModel == RoughnessModel::TANH || roughnessModel == RoughnessModel::DEFAULT) {

            return std::make_unique<SpecularMagneticTanhStrategy>();

        } else if (roughnessModel == RoughnessModel::NEVOT_CROCE) {

            return std::make_unique<SpecularMagneticNCStrategy>();

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
