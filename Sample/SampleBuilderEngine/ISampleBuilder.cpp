//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/SampleBuilderEngine/ISampleBuilder.cpp
//! @brief     Implements interface ISampleBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/SampleBuilderEngine/ISampleBuilder.h"

ISampleBuilder::ISampleBuilder() {
    setName("SampleBuilder");
}

ISampleBuilder::~ISampleBuilder() = default;
