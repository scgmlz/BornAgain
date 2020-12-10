//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Scattering/ISampleNode.h
//! @brief     Defines interface class ISampleNode.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_SCATTERING_ISAMPLENODE_H
#define BORNAGAIN_SAMPLE_SCATTERING_ISAMPLENODE_H

#include "Base/Types/ICloneable.h"
#include "Param/Node/INode.h"
#include <vector>

class Material;

//! Abstract base class for sample components and properties related to scattering.
//! @ingroup samples_internal

class ISampleNode : public ICloneable, public INode {
public:
    ISampleNode() = default;
    ISampleNode(const NodeMeta& meta, const std::vector<double>& PValues);

    //! Returns a clone of this ISampleNode object.
    ISampleNode* clone() const override = 0;

    //! Returns nullptr, unless overwritten to return a specific material.
    virtual const Material* material() const { return nullptr; }

    //! Returns set of unique materials contained in this ISampleNode.
    std::vector<const Material*> containedMaterials() const;

    //! Returns true if there is any magnetic material in this ISampleNode.
    bool isMagnetic() const;
};

#endif // BORNAGAIN_SAMPLE_SCATTERING_ISAMPLENODE_H
#endif // USER_API
