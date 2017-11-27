// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ConstantBackground.cpp
//! @brief     Implements class ConstantBackground.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ConstantBackground.h"
#include "RealParameter.h"
#include "SimulationElement.h"


ConstantBackground::ConstantBackground(double background_value)
    : m_background_value(background_value)
{
    setName(BornAgain::ConstantBackgroundType);
    init_parameters();
}

ConstantBackground::~ConstantBackground() =default;

ConstantBackground* ConstantBackground::clone() const
{
    return new ConstantBackground(m_background_value);
}

void ConstantBackground::addBackGround(std::vector<SimulationElement>::iterator start,
                                       std::vector<SimulationElement>::iterator end) const
{
    for (auto it=start; it != end; it++) {
        it->addIntensity(m_background_value);
    }
}

void ConstantBackground::init_parameters()
{
    registerParameter(BornAgain::BackgroundValue, &m_background_value).setNonnegative();
}
