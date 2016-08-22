// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/DecoratedLayerDWBASimulation.h
//! @brief     Defines class DecoratedLayerDWBASimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DECORATEDLAYERDWBASIMULATION_H
#define DECORATEDLAYERDWBASIMULATION_H

#include "LayerDWBASimulation.h"

class IInterferenceFunctionStrategy;

//! Calculates scattering cross sections in DWBA for one layer with particles in/on it.
//! @ingroup algorithms_internal

class BA_CORE_API_ DecoratedLayerDWBASimulation : public LayerDWBASimulation
{
public:
    DecoratedLayerDWBASimulation(const Layer* p_layer, size_t layout_index=0);
    ~DecoratedLayerDWBASimulation() final;

    void run() final;

private:
    void runProtected() final;
    IInterferenceFunctionStrategy* createAndInitStrategy() const;
    void calculateCoherentIntensity(const IInterferenceFunctionStrategy* p_strategy);
    size_t m_layout_index;
};

#endif // DECORATEDLAYERDWBASIMULATION_H
