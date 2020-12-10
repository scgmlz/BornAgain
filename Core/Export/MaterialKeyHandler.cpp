//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/MaterialKeyHandler.cpp
//! @brief     Implement class MaterialKeyHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Export/MaterialKeyHandler.h"
#include "Base/Utils/Assert.h"
#include "Sample/Material/Material.h"
#include <algorithm>
#include <set>
#include <stdexcept>

void MaterialKeyHandler::insertMaterial(const Material* mat) {
    for (const auto& it : m_Mat2Unique)
        if (*it.second == *mat) {
            m_Mat2Unique.emplace(mat, it.second);
            return;
        }
    m_Mat2Unique.emplace(mat, mat);

    const std::string key = "material_" + mat->getName();
    if (m_Key2Mat.count(key))
        throw std::runtime_error(
            "Material name " + mat->getName()
            + " used more than once, which is not supported by Python exporter");
    m_Key2Mat.emplace(key, mat);
}

const std::string& MaterialKeyHandler::mat2key(const Material* mat) const {
    const Material* unique_mat = m_Mat2Unique.at(mat);
    for (const auto& it : m_Key2Mat)
        if (it.second == unique_mat)
            return it.first;
    ASSERT(0);
}

const std::map<const std::string, const Material*>& MaterialKeyHandler::materialMap() const {
    return m_Key2Mat;
}
