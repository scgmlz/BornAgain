// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SpecularComputation.h
//! @brief     Defines class SpecularComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SPECULARCOMPUTATION_H
#define SPECULARCOMPUTATION_H

#include "INoncopyable.h"
#include <memory>
#include <vector>

class MultiLayer;
class LayerSpecularInfo;
class ProgressHandler;
class SimulationElement;
class SimulationOptions;

//! Computes the specular scattering.
//! Controlled by MainComputation.
//! @ingroup algorithms_internal

class SpecularComputation final : public INoncopyable
{
public:
    SpecularComputation();

    void eval(
        ProgressHandler* progress, bool polarized,
        const std::vector<SimulationElement>::iterator& begin_it,
        const std::vector<SimulationElement>::iterator& end_it);
    void setSpecularInfo(const LayerSpecularInfo& specular_info);

private:
    std::unique_ptr<LayerSpecularInfo> mP_specular_info;
};


#endif // SPECULARCOMPUTATION_H
