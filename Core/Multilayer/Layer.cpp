// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/Layer.cpp
//! @brief     Implements class Layer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/Layer.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Correlations/ILayout.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/RealParameter.h"

//! Constructor of a layer with thickness and material
//! @param material: material the layer is made of
//! @param thickness: thickness of a layer in nanometers
Layer::Layer(Material material, double thickness)
    : m_material(std::move(material)), m_thickness(thickness)
{
    setName("Layer");
    registerThickness();
}

Layer::~Layer() {}

Layer* Layer::clone() const
{
    Layer* p_result = new Layer(m_material, m_thickness);
    p_result->setName(getName());
    p_result->m_B_field = m_B_field;
    p_result->m_n_slices = m_n_slices;
    for (auto p_layout : layouts())
        p_result->addLayout(*p_layout);
    return p_result;
}

//! Sets layer thickness in nanometers.
void Layer::setThickness(double thickness)
{
    if (thickness < 0.)
        throw Exceptions::DomainErrorException("Layer thickness cannot be negative");
    m_thickness = thickness;
}

void Layer::setMaterial(Material material)
{
    m_material = std::move(material);
}

void Layer::addLayout(const ILayout& layout)
{
    ILayout* clone = layout.clone();
    m_layouts.push_back(clone);
    registerChild(clone);
}

std::vector<const ILayout*> Layer::layouts() const
{
    std::vector<const ILayout*> result;
    for (auto p_layout : m_layouts)
        result.push_back(p_layout);
    return result;
}

std::vector<const INode*> Layer::getChildren() const
{
    std::vector<const INode*> result;
    for (auto layout : m_layouts)
        result.push_back(layout);
    return result;
}

void Layer::registerThickness(bool make_registered)
{
    if (make_registered) {
        if (!parameter("Thickness"))
            registerParameter("Thickness", &m_thickness).setUnit("nm").setNonnegative();
    } else {
        removeParameter("Thickness");
    }
}
