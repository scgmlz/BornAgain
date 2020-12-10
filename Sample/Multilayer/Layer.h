//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Multilayer/Layer.h
//! @brief     Defines class Layer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_MULTILAYER_LAYER_H
#define BORNAGAIN_SAMPLE_MULTILAYER_LAYER_H

#include "Base/Types/SafePointerVector.h"
#include "Sample/Material/Material.h"
#include "Sample/Scattering/ISampleNode.h"

class ParticleLayout;

//! A layer in a MultiLayer sample.
//! @ingroup samples

class Layer : public ISampleNode {
public:
    Layer(Material material, double thickness = 0);

    ~Layer() override;

    Layer* clone() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    void setThickness(double thickness);
    double thickness() const { return m_thickness; }

    const Material* material() const final { return &m_material; }
    void setMaterial(Material material);

    void addLayout(const ParticleLayout& decoration);
    size_t numberOfLayouts() const { return m_layouts.size(); }
    std::vector<const ParticleLayout*> layouts() const;

    std::vector<const INode*> getChildren() const final;

    void registerThickness(bool make_registered = true);

    void setNumberOfSlices(unsigned int n_slices) { m_n_slices = n_slices; }
    unsigned int numberOfSlices() const { return m_n_slices; }

private:
    Material m_material;                         //!< material
    kvector_t m_B_field;                         //!< cached value of magnetic induction
    double m_thickness;                          //!< layer thickness in nanometers
    SafePointerVector<ParticleLayout> m_layouts; //!< independent layouts in this layer
    unsigned int m_n_slices = 1; //!< number of slices to create for graded layer approach
};

#endif // BORNAGAIN_SAMPLE_MULTILAYER_LAYER_H
