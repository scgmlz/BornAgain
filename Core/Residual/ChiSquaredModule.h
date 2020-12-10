//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Residual/ChiSquaredModule.h
//! @brief     Defines class ChiSquaredModule.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_DEVICE_INSTRUMENT_CHISQUAREDMODULE_H
#define BORNAGAIN_DEVICE_INSTRUMENT_CHISQUAREDMODULE_H

#include "Core/Residual/IChiSquaredModule.h"

//! Calculation of chi2 between two data sets.
//! @ingroup fitting

class ChiSquaredModule : public IChiSquaredModule {
public:
    ChiSquaredModule() {}
    ChiSquaredModule(const ChiSquaredModule& other) : IChiSquaredModule(other) {}
    virtual ~ChiSquaredModule() {}

    virtual ChiSquaredModule* clone() const { return new ChiSquaredModule(*this); }

    virtual double residual(double a, double b, double weight);
};

#endif // BORNAGAIN_DEVICE_INSTRUMENT_CHISQUAREDMODULE_H
