// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/DecoratedFormFactor/IFormFactorDecorator.h
//! @brief     Defines and implements pure virtual interface class IFormFactorDecorator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IFORMFACTORDECORATOR_H
#define IFORMFACTORDECORATOR_H

#include "IFormFactor.h"

//! Encapsulates another formfactor and adds extra functionality
//! (a scalar factor, a Debye-Waller factor, a position-dependent phase factor, ...).
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
    void accept(ISampleVisitor* visitor) const override = 0;

    void setAmbientMaterial(const IMaterial& material) override
    {
        mp_form_factor->setAmbientMaterial(material);
    }

    double getVolume() const override { return mp_form_factor->getVolume(); }

    double getRadialExtension() const override { return mp_form_factor->getRadialExtension(); }

protected:
    IFormFactor* mp_form_factor;
};

#endif // IFORMFACTORDECORATOR_H
