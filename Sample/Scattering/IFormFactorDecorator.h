//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Scattering/IFormFactorDecorator.h
//! @brief     Defines and implements interface class IFormFactorDecorator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_SCATTERING_IFORMFACTORDECORATOR_H
#define BORNAGAIN_SAMPLE_SCATTERING_IFORMFACTORDECORATOR_H

#include "Sample/Scattering/IFormFactor.h"

//! Encapsulates another formfactor and adds extra functionality
//! (a scalar factor, a position-dependent phase factor, ...).
//!
//! This class is designed according to the Decorator Pattern.
//! It inherits from IFormFactor _and_ has a member of type IFormFactor*.
//!
//! @ingroup formfactors_internal

class IFormFactorDecorator : public IFormFactor {
public:
    IFormFactorDecorator(const IFormFactor& ff) : m_ff(ff.clone()) {}
    ~IFormFactorDecorator() override { delete m_ff; }
    IFormFactorDecorator* clone() const override = 0;

    void setAmbientMaterial(const Material& material) override {
        m_ff->setAmbientMaterial(material);
    }

    double volume() const override { return m_ff->volume(); }

    double radialExtension() const override { return m_ff->radialExtension(); }

    double bottomZ(const IRotation& rotation) const override { return m_ff->bottomZ(rotation); }

    double topZ(const IRotation& rotation) const override { return m_ff->topZ(rotation); }

    const IFormFactor* getFormFactor() const { return m_ff; }

protected:
    IFormFactor* m_ff;
};

#endif // BORNAGAIN_SAMPLE_SCATTERING_IFORMFACTORDECORATOR_H
#endif // USER_API
