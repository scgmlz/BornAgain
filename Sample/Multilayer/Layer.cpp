//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Multilayer/Layer.cpp
//! @brief     Implements class Layer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Multilayer/Layer.h"
#include "Param/Base/ParameterPool.h"
#include "Param/Base/RealParameter.h"
#include "Sample/Aggregate/ParticleLayout.h"

//! Constructor of a layer with thickness and material
//! @param material: material the layer is made of
//! @param thickness: thickness of a layer in nanometers
Layer::Layer(Material material, double thickness)
    : m_material(std::move(material)), m_thickness(thickness) {
    setName("Layer");
    registerThickness();
}

Layer::~Layer() = default;

Layer* Layer::clone() const {
    Layer* result = new Layer(m_material, m_thickness);
    result->setName(getName());
    result->m_B_field = m_B_field;
    result->m_n_slices = m_n_slices;
    for (const auto* layout : layouts())
        result->addLayout(*layout);
    return result;
}

//! Sets layer thickness in nanometers.
void Layer::setThickness(double thickness) {
    if (thickness < 0.)
        throw std::runtime_error("Layer thickness cannot be negative");
    m_thickness = thickness;
}

void Layer::setMaterial(Material material) {
    m_material = std::move(material);
}

void Layer::addLayout(const ParticleLayout& layout) {
    ParticleLayout* clone = layout.clone();
    m_layouts.push_back(clone);
    registerChild(clone);
}

std::vector<const ParticleLayout*> Layer::layouts() const {
    std::vector<const ParticleLayout*> result;
    for (const auto* layout : m_layouts)
        result.push_back(layout);
    return result;
}

std::vector<const INode*> Layer::getChildren() const {
    std::vector<const INode*> result;
    for (auto layout : m_layouts)
        result.push_back(layout);
    return result;
}

void Layer::registerThickness(bool make_registered) {
    if (make_registered) {
        if (!parameter("Thickness"))
            registerParameter("Thickness", &m_thickness).setUnit("nm").setNonnegative();
    } else {
        removeParameter("Thickness");
    }
}
