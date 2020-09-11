// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayerInterface.h
//! @brief     Defines class LayerInterface.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_LAYERINTERFACE_H
#define BORNAGAIN_CORE_MULTILAYER_LAYERINTERFACE_H

#include "Core/Scattering/ISample.h"
#include <memory>

class LayerRoughness;

//! Interface between two layers, possibly with roughness.
//! @ingroup samples_internal

class BA_CORE_API_ LayerInterface : public ISample
{
public:
    virtual ~LayerInterface();

    LayerInterface* clone() const;

    virtual void accept(INodeVisitor* visitor) const { visitor->visit(this); }

    //! Creates smooth interface between two layers
    static LayerInterface* createSmoothInterface(const Layer* top_layer, const Layer* bottom_layer);

    //! Creates rough interface between two layers
    static LayerInterface* createRoughInterface(const Layer* top_layer, const Layer* bottom_layer,
                                                const LayerRoughness& roughness);

    //! Sets roughness of the interface.
    void setRoughness(const LayerRoughness& roughness);

    //! Returns roughness of the interface.
    const LayerRoughness* getRoughness() const;

    const Layer* topLayer() const;

    const Layer* bottomLayer() const;

    std::vector<const INode*> getChildren() const;

private:
    void setLayersTopBottom(const Layer* top_layer, const Layer* bottom_layer);
    LayerInterface();

    const Layer* m_topLayer;                     //!< pointer to the layer above interface
    const Layer* m_bottomLayer;                  //!< pointer to the layer below interface
    std::unique_ptr<LayerRoughness> m_roughness; //!< roughness of the interface
};

inline const LayerRoughness* LayerInterface::getRoughness() const
{
    return m_roughness.get();
}

inline const Layer* LayerInterface::topLayer() const
{
    return m_topLayer;
}

inline const Layer* LayerInterface::bottomLayer() const
{
    return m_bottomLayer;
}

#endif // BORNAGAIN_CORE_MULTILAYER_LAYERINTERFACE_H
