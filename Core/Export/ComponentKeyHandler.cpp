//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/ComponentKeyHandler.cpp
//! @brief     Implement class ComponentKeyHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Export/ComponentKeyHandler.h"
#include <algorithm>
#include <set>
#include <stdexcept>

void ComponentKeyHandler::insertModel(const std::string& tag, const IComponent* s) {
    m_objects[tag].emplace_back(s);
}

std::string ComponentKeyHandler::obj2key(const IComponent* s) const {
    for (auto it : m_objects) {
        const std::vector<const IComponent*>& v = it.second;
        const auto vpos = std::find(v.begin(), v.end(), s);
        if (vpos == std::end(v))
            continue;
        const std::string& tag = it.first;
        if (v.size() == 1)
            return tag;
        return tag + "_" + std::to_string(vpos - v.begin() + 1);
    }
    throw std::runtime_error("BUG: object not found in ComponentKeyHandler");
}
