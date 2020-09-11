// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/RoughnessModels.cpp
//! @brief     Implements RoughnessModels enumerator and Python wrapper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/RoughnessModels.h"

#include <map>

namespace
{
const std::map<RoughnessModel, std::string> roughnessModelNames = {
    {RoughnessModel::DEFAULT, "RoughnessModel::DEFAULT"},
    {RoughnessModel::TANH, "RoughnessModel::TANH"},
    {RoughnessModel::NEVOT_CROCE, "RoughnessModel::NEVOT_CROCE"}};
}

std::string RoughnessModelWrap::roughnessModelName(RoughnessModel model)
{
    return roughnessModelNames.at(model);
}
