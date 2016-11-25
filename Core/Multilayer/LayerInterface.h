// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayerInterface.h
//! @brief     Defines class LayerInterface.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYERINTERFACE_H
#define LAYERINTERFACE_H

#include "ICompositeSample.h"
class LayerRoughness;

//! Interface between two layers, possibly with roughness.
//! @ingroup samples_internal

class BA_CORE_API_ LayerInterface : public ICompositeSample
{
public:
    virtual ~LayerInterface();

    LayerInterface* clone() const;

    virtual void accept(ISampleVisitor* visitor) const { visitor->visit(this); }

    //! Creates smooth interface between two layers
    static LayerInterface*
    createSmoothInterface(const Layer* p_layer_top, const Layer* p_layer_bottom);

    //! Creates rough interface between two layers
    static LayerInterface* createRoughInterface(
        const Layer* p_layer_top, const Layer* p_layer_bottom, const LayerRoughness& roughness);

    //! Sets link to the layer above the interface.
    void setLayerTop(const Layer* p_layer_top) { m_LayerTop = p_layer_top; }

    //! Sets link to the layer below the interface.
    void setLayerBottom(const Layer* p_layer_bottom) { m_LayerBottom = p_layer_bottom; }

    //! Sets links to the layers above and below the interface.
    void setLayersTopBottom(const Layer* p_layer_top, const Layer* p_layer_bottom)
    {
        setLayerTop(p_layer_top);
        setLayerBottom(p_layer_bottom);
    }

    //! Sets roughness of the interface.
    void setRoughness(const LayerRoughness& roughness);

    //! Returns roughness of the interface.
    const LayerRoughness* getRoughness() const { return m_roughness; }

    //! Returns top layer.
    const Layer* getLayerTop() const { return m_LayerTop; }

    //! Returns bottom layer.
    const Layer* getLayerBottom() const { return m_LayerBottom; }

protected:
    void print(std::ostream& ostr) const;

private:
    LayerInterface();

    LayerRoughness* m_roughness; //!< roughness of the interface
    const Layer* m_LayerTop; //!< pointer to the layer above interface
    const Layer* m_LayerBottom; //!< pointer to the layer below interface
};

#endif // LAYERINTERFACE_H
