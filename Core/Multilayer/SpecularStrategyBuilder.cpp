// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMatrix.cpp
//! @brief     Implements class SpecularMatrix.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SpecularStrategyBuilder.h"

std::unique_ptr<ISpecularStrategy> SpecularStrategyBuilder::build(const MultiLayer& sample,
                                                                  const bool magnetic)
{

    auto roughnessModel = sample.roughnessModel();

    if (magnetic) {
        if (MultiLayerUtils::hasRoughness(sample))
            throw std::runtime_error("Magnetic roughness not implemented");

        return std::make_unique<SpecularMagneticStrategy>();

    } else {
        if (roughnessModel == "") {
            return std::make_unique<SpecularScalarStrategy>();

        } else if (roughnessModel == "nc" or roughnessModel == "nevot-croce") {

            throw std::runtime_error("Nevot-Croce not yet implemented");

        } else if (roughnessModel == "tanh") {
            return std::make_unique<SpecularScalarStrategy>();

        } else
            throw std::logic_error("Invalid roughness model");
    }
}
