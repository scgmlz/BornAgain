// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MatrixFresnelMap.cpp
//! @brief     Implements class MatrixFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MatrixFresnelMap.h"
#include "ILayerRTCoefficients.h"
#include "MatrixRTCoefficients.h"
#include "MultiLayer.h"
#include "SimulationElement.h"
#include "SpecularData.h"
#include "SpecularMagnetic.h"
#include "SpecularSimulationElement.h"

namespace {
std::vector<MatrixRTCoefficients> calculateCoefficients(const MultiLayer& multilayer,
                                                        kvector_t kvec);

const std::vector<MatrixRTCoefficients>&
getCoefficientsFromCache(kvector_t kvec, const MultiLayer& multilayer,
                         MatrixFresnelMap::CoefficientHash& hash_table);
}

MatrixFresnelMap::MatrixFresnelMap() = default;

MatrixFresnelMap::~MatrixFresnelMap() = default;

std::unique_ptr<const ILayerRTCoefficients>
MatrixFresnelMap::getOutCoefficients(const SimulationElement& sim_element, size_t layer_index) const
{
    return getCoefficients(-sim_element.getMeanKf(), layer_index, *mP_inverted_multilayer,
                           m_hash_table_out);
}

void MatrixFresnelMap::fillSpecularData(SpecularSimulationElement& sim_element) const
{
    const auto& kvec = sim_element.getKi();
    if (m_use_cache)
        sim_element.setSpecular(
            SpecularData(getCoefficientsFromCache(kvec, *mP_multilayer, m_hash_table_in)));
    else
        sim_element.setSpecular(SpecularData(calculateCoefficients(*mP_multilayer, kvec)));
}

std::unique_ptr<const ILayerRTCoefficients>
MatrixFresnelMap::getCoefficients(const kvector_t& kvec, size_t layer_index) const
{
    return getCoefficients(kvec, layer_index, *mP_multilayer, m_hash_table_in);
}

std::unique_ptr<const ILayerRTCoefficients>
MatrixFresnelMap::getCoefficients(const kvector_t& kvec, size_t layer_index,
                                  const MultiLayer& multilayer, CoefficientHash& hash_table) const
{
    if (!m_use_cache) {
        auto coeffs = calculateCoefficients(multilayer, kvec);
        return std::make_unique<MatrixRTCoefficients>(coeffs[layer_index]);
    }
    const auto& coef_vector = getCoefficientsFromCache(kvec, multilayer, hash_table);
    return std::make_unique<MatrixRTCoefficients>(coef_vector[layer_index]);
}

void MatrixFresnelMap::setMultilayer(const MultiLayer& multilayer)
{
    IFresnelMap::setMultilayer(multilayer);
    mP_inverted_multilayer.reset(multilayer.cloneInvertB());
}

namespace {
std::vector<MatrixRTCoefficients> calculateCoefficients(const MultiLayer& multilayer,
                                                        kvector_t kvec)
{
    std::vector<MatrixRTCoefficients> coeffs;
    SpecularMagnetic::execute(multilayer, kvec, coeffs);
    return coeffs;
}

const std::vector<MatrixRTCoefficients>&
getCoefficientsFromCache(kvector_t kvec, const MultiLayer& multilayer,
                         MatrixFresnelMap::CoefficientHash& hash_table)
{
    auto it = hash_table.find(kvec);
    if (it == hash_table.end())
        it = hash_table.insert({kvec, calculateCoefficients(multilayer, kvec)}).first;
    return it->second;
}
}

