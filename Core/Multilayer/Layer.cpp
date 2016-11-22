// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/Layer.cpp
//! @brief     Implements class Layer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Layer.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "ILayout.h"
#include "IMaterial.h"
#include "ParameterPool.h"
#include "RealParameter.h"

Layer::Layer()
    : mp_material(nullptr), m_thickness(0)
{
    initialize();
}

Layer::Layer(const IMaterial& material, double thickness)
    : mp_material(nullptr), m_thickness(thickness)
{
    setMaterial(material);
    initialize();
}

Layer::Layer(const Layer& other) : ICompositeSample()
{
    m_thickness = other.m_thickness;
    mp_material = nullptr;
    if (other.mp_material)
        mp_material = other.mp_material->clone();
    for (size_t i=0; i<other.getNumberOfLayouts();++i)
        addLayoutPtr(other.getLayout(i)->clone());
    setNumberOfLayers(other.getNumberOfLayers());
    initialize();
}

Layer::~Layer()
{
    delete mp_material;
}

Layer* Layer::cloneInvertB() const
{
    Layer* p_clone = new Layer(*mp_material->cloneInverted(), m_thickness);
    for (size_t i=0; i<getNumberOfLayouts(); ++i)
        p_clone->addLayoutPtr(getLayout(i)->cloneInvertB());
    p_clone->setNumberOfLayers(getNumberOfLayers());
    p_clone->init_parameters();
    return p_clone;
}

std::string Layer::to_str(int indent) const
{
    std::stringstream ss;
    ss << std::string(4*indent, '.') << " " << getName() << " "
       << (getMaterial() ? getMaterial()->getName() : "0_MATERIAL") << " "
       << getRefractiveIndex() << " " << *getParameterPool() << "\n";
    for( const ISample* child: getChildren() )
        ss << child->to_str(indent+1);
    return ss.str();
}

//! Sets layer thickness in nanometers.
void Layer::setThickness(double thickness)
{
    if (thickness < 0.)
        throw Exceptions::DomainErrorException("Layer thickness cannot be negative");
    m_thickness = thickness;
}

//! Sets _material_ of the layer.
void Layer::setMaterial(const IMaterial& material)
{
    delete mp_material;
    mp_material = material.clone();
}

complex_t Layer::getRefractiveIndex() const
{
    return mp_material ? mp_material->getRefractiveIndex() : 1.0;
}

complex_t Layer::getRefractiveIndex2() const
{
    return getRefractiveIndex()*getRefractiveIndex();
}

void Layer::addLayout(const ILayout& decoration)
{
    addLayoutPtr(decoration.clone());
}

const ILayout* Layer::getLayout(size_t i) const
{
    if (i>=m_layouts.size())
        return nullptr;
    return m_layouts[i];
}

double Layer::getTotalParticleSurfaceDensity(size_t layout_index) const
{
    if (getNumberOfLayouts()==0 || layout_index>=getNumberOfLayouts())
        return 0.0;
    return getLayout(layout_index)->getTotalParticleSurfaceDensity();
}

double Layer::getTotalAbundance() const
{
    double total_abundance = 0.0;
    for (size_t i=0; i<getNumberOfLayouts(); ++i)
        total_abundance += getLayout(i)->getTotalAbundance();
    return total_abundance;
}

void Layer::init_parameters()
{
    getParameterPool()->clear(); // non-trivially needed
    registerParameter(BornAgain::Thickness, &m_thickness).setUnit("nm").setNonnegative();
}

//! Prints description.
void Layer::print(std::ostream& ostr) const
{
    ICompositeSample::print(ostr);
    ostr << "-->Layer{" <<  *getMaterial() << "}";
}

void Layer::addLayoutPtr(ILayout* layout)
{
    if( !layout )
        return;
    m_layouts.push_back(layout);
    registerChild(layout);
}

void Layer::initialize()
{
    setName(BornAgain::LayerType);
    init_parameters();
}
