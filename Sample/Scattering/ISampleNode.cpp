//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Scattering/ISampleNode.cpp
//! @brief     Implements interface ISampleNode.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Scattering/ISampleNode.h"
#include "Param/Base/ParameterPool.h"
#include "Sample/Material/Material.h"
#include <algorithm>
#include <sstream>

ISampleNode::ISampleNode(const NodeMeta& meta, const std::vector<double>& PValues)
    : INode(meta, PValues) {}

std::vector<const Material*> ISampleNode::containedMaterials() const {
    std::vector<const Material*> result;
    if (const Material* p_material = material())
        result.push_back(p_material);
    for (const auto* child : getChildren()) {
        if (const ISampleNode* sample = dynamic_cast<const ISampleNode*>(child)) {
            for (const Material* p_material : sample->containedMaterials())
                result.push_back(p_material);
        }
    }
    return result;
}

bool ISampleNode::isMagnetic() const {
    const auto materials = containedMaterials();
    return std::any_of(materials.cbegin(), materials.cend(),
                       [](const Material* mat) { return mat->isMagneticMaterial(); });
}
