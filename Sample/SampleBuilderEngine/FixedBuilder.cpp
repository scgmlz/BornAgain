//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/SampleBuilderEngine/FixedBuilder.cpp
//! @brief     Implements class FixedBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/SampleBuilderEngine/FixedBuilder.h"
#include "Sample/Multilayer/MultiLayer.h"

FixedBuilder::FixedBuilder(const MultiLayer& sample) : m_sample(sample.clone()) {}

MultiLayer* FixedBuilder::buildSample() const {
    return m_sample->clone();
}
