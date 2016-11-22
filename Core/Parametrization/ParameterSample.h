// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ParameterSample.h
//! @brief     Defines class ParameterSample.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERSAMPLE_H
#define PARAMETERSAMPLE_H

//! Represents a sampled parameter value with its weight.

class ParameterSample
{
public:
    double value;
    double weight;
};

#endif // PARAMETERSAMPLE_H
