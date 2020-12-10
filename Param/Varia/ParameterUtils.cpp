//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Param/Varia/ParameterUtils.cpp
//! @brief     Implements namespace ParameterUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Param/Varia/ParameterUtils.h"
#include "Param/Base/IParametricComponent.h"
#include "Param/Base/ParameterPool.h"
#include "Param/Base/RealParameter.h"
#include <memory>

namespace {
//! Returns list of all angle related parameters used in Core library.
std::vector<std::string> angleRelatedParameters() {
    std::vector<std::string> result{
        "InclinationAngle", "AzimuthalAngle", "Alpha", "Beta", "Gamma", "Angle"};
    return result;
}
} // namespace

bool ParameterUtils::isAngleRelated(const std::string& par_name) {
    static std::vector<std::string> angleRelated = angleRelatedParameters();

    for (const auto& par : angleRelated) {
        if (par_name.find(par) != std::string::npos)
            return true;
    }
    return false;
}

std::string ParameterUtils::poolParameterUnits(const IParametricComponent& node,
                                               const std::string& parName) {
    std::unique_ptr<ParameterPool> pool{node.createParameterTree()};
    return pool->getUniqueMatch(parName)->unit();
}
