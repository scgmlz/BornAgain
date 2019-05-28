// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/UnitConverterUtils.h
//! @brief     Declares utilities for unit converters.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef UNITCONVERTERUTILS_H
#define UNITCONVERTERUTILS_H

#include "IUnitConverter.h"

class Instrument;
class Simulation;
template<class T> class OutputData;

//! Namespace enclosing a number of utilities/helpers for unit converters

namespace UnitConverterUtils {

inline AxesUnits substituteDefaultUnits(const IUnitConverter& converter, AxesUnits units)
{
    return units == AxesUnits::DEFAULT ? converter.defaultUnits()
                                       : units;
}

//! Returns zero-valued output data array in specified units
BA_CORE_API_ std::unique_ptr<OutputData<double>> createOutputData(const IUnitConverter& converter,
                                                                  AxesUnits units);

//! Helper factory function to use in GISASSimulation. Depending on the type of detector,
//! returns either FlatConverter or SphericalConverter.
BA_CORE_API_ std::unique_ptr<IUnitConverter> createConverterForGISAS(const Instrument& instrument);

BA_CORE_API_ std::unique_ptr<IUnitConverter> createConverter(const Simulation& simulation);
}

#endif // UNITCONVERTERUTILS_H
