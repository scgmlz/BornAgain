// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MultiLayer.h
//! @brief     Defines class MultiLayer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MULTILAYER_H
#define MULTILAYER_H

#include "ISample.h"
#include "SafePointerVector.h"
#include "Vectors3D.h"
#include "ZLimits.h"

#include <functional>

class ILayout;
class Layer;
class LayerInterface;
class LayerRoughness;

//! Our sample model: a stack of layers one below the other.
//! @ingroup samples

//! Example of system of 4 layers (3 interfaces):
//!
//!  ambience    layer #0
//!  ---------   interface #0    z=0.0
//!  Fe, 20A     layer #1
//!  ---------   interface #1    z=-20.0
//!  Cr, 40A     layer #2
//!  ---------   interface #2    z=-60.0
//!  substrate   layer #3

class BA_CORE_API_ MultiLayer : public ISample
{
public:
    MultiLayer();
    ~MultiLayer() override;

    //! Returns a clone of multilayer with clones of all layers and
    //! interfaces between layers
    MultiLayer* clone() const final override;

    void accept(INodeVisitor* visitor) const final override { visitor->visit(this); }

    size_t numberOfLayers() const { return m_layers.size(); }

    //! Adds object to multilayer
    void addLayer(const Layer& layer);

    //! Adds layer with top roughness
    void addLayerWithTopRoughness(const Layer& layer, const LayerRoughness& roughness);

    //! Returns layer with given index
    const Layer* layer(size_t i_layer) const;

    //! Returns interface with given index
    const LayerInterface* layerInterface(size_t i_interface) const;

    //! Sets cross correlation length of roughnesses between interfaces
    void setCrossCorrLength(double crossCorrLength);

    //! Returns cross correlation length of roughnesses between interfaces
    double crossCorrLength() const { return m_crossCorrLength; }

    //! Sets the external field applied to the multilayer (units: A/m)
    void setExternalField(kvector_t ext_field);

    //! Returns the external field applied to the multilayer (units: A/m)
    kvector_t externalField() const { return m_ext_field; }

    std::vector<const INode*> getChildren() const final override;

    void setRoughnessModel(std::string strategy);

    std::string roughnessModel() const { return m_roughness_model; }

private:
    //! Registers some class members for later access via parameter pool
    void init_parameters();

    //! Adds the layer with simultaneous registration in parent class
    void addAndRegisterLayer(Layer* child);

    //! Adds the interface with simultaneous registration in parent class
    void addAndRegisterInterface(LayerInterface* child);

    //! Handles correct registration of layer thicknesses (not needed for top and bottom layer)
    void handleLayerThicknessRegistration();

    //! Checks index of layer w.r.t. vector length
    size_t check_layer_index(size_t i_layer) const;

    //! Checks index of interface w.r.t. vector length
    size_t check_interface_index(size_t i_interface) const;

    //! stack of layers [nlayers]
    SafePointerVector<Layer> m_layers;
    //! stack of layer interfaces [nlayers-1]
    SafePointerVector<LayerInterface> m_interfaces;
    //! cross correlation length (in z direction) between different layers
    double m_crossCorrLength;
    //! external magnetic field (in A/m)
    kvector_t m_ext_field;

    std::string m_roughness_model;
};

#endif // MULTILAYER_H
