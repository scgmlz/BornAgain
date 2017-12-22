#include "SpecularComputationTerm.h"
#include "SimulationElement.h"
#include "IFresnelMap.h"
#include "ILayerRTCoefficients.h"
#include "MultiLayer.h"

SpecularComputationTerm::SpecularComputationTerm(const MultiLayer* p_multi_layer,
                                                 const IFresnelMap* p_fresnel_map)
    : IComputationTerm(p_multi_layer, p_fresnel_map)
{}

void SpecularComputationTerm::evalSingle(SimulationElement& element) const
{
    mp_fresnel_map->fillSpecularData(element);
    const ILayerRTCoefficients& layer_data = element.specularData()->operator [](0);
    element.setIntensity(std::norm(layer_data.getScalarR()));
}

bool SpecularComputationTerm::checkComputation() const {
    return !mp_multilayer->requiresMatrixRTCoefficients();
}
