// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/Layer.h
//! @brief     Defines class Layer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_LAYER_H
#define BORNAGAIN_CORE_MULTILAYER_LAYER_H

#include "Core/Material/Material.h"
#include "Core/Scattering/ISample.h"
#include "Core/Tools/SafePointerVector.h"

class ILayout;

//! A layer, with thickness (in nanometer) and material.
//! @ingroup samples

class BA_CORE_API_ Layer : public ISample
{
public:
    Layer(Material material, double thickness = 0);

    ~Layer() override;

    Layer* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    void setThickness(double thickness);
    double thickness() const { return m_thickness; }

    const Material* material() const override final { return &m_material; }
    void setMaterial(Material material);

    void addLayout(const ILayout& decoration);
    size_t numberOfLayouts() const { return m_layouts.size(); }
    std::vector<const ILayout*> layouts() const;

    std::vector<const INode*> getChildren() const override final;

    void registerThickness(bool make_registered = true);

    void setNumberOfSlices(unsigned int n_slices) { m_n_slices = n_slices; }
    unsigned int numberOfSlices() const { return m_n_slices; }

private:
    Material m_material;                  //!< material
    kvector_t m_B_field;                  //!< cached value of magnetic induction
    double m_thickness;                   //!< layer thickness in nanometers
    SafePointerVector<ILayout> m_layouts; //!< independent layouts in this layer
    unsigned int m_n_slices = 1;          //!< number of slices to create for graded layer approach
};

#endif // BORNAGAIN_CORE_MULTILAYER_LAYER_H
