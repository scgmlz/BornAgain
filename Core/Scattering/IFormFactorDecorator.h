// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/IFormFactorDecorator.h
//! @brief     Defines and implements pure virtual interface class IFormFactorDecorator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SCATTERING_IFORMFACTORDECORATOR_H
#define BORNAGAIN_CORE_SCATTERING_IFORMFACTORDECORATOR_H

#include "Core/Scattering/IFormFactor.h"

//! Encapsulates another formfactor and adds extra functionality
//! (a scalar factor, a position-dependent phase factor, ...).
//!
//! This class is designed according to the Decorator Pattern.
//! It inherits from IFormFactor _and_ has a member of type IFormFactor*.
//!
//! @ingroup formfactors_internal

class BA_CORE_API_ IFormFactorDecorator : public IFormFactor
{
public:
    IFormFactorDecorator(const IFormFactor& form_factor) : mp_form_factor(form_factor.clone()) {}
    ~IFormFactorDecorator() override { delete mp_form_factor; }
    IFormFactorDecorator* clone() const override = 0;

    void setAmbientMaterial(Material material) override
    {
        mp_form_factor->setAmbientMaterial(material);
    }

    double volume() const override { return mp_form_factor->volume(); }

    double radialExtension() const override { return mp_form_factor->radialExtension(); }

    double bottomZ(const IRotation& rotation) const override
    {
        return mp_form_factor->bottomZ(rotation);
    }

    double topZ(const IRotation& rotation) const override { return mp_form_factor->topZ(rotation); }

    const IFormFactor* getFormFactor() const { return mp_form_factor; }

protected:
    IFormFactor* mp_form_factor;
};

#endif // BORNAGAIN_CORE_SCATTERING_IFORMFACTORDECORATOR_H
