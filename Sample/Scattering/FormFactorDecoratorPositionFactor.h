//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Scattering/FormFactorDecoratorPositionFactor.h
//! @brief     Defines class FormFactorDecoratorPositionFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_SCATTERING_FORMFACTORDECORATORPOSITIONFACTOR_H
#define BORNAGAIN_SAMPLE_SCATTERING_FORMFACTORDECORATORPOSITIONFACTOR_H

#include "Sample/Scattering/IFormFactorDecorator.h"

//! Decorates a form factor with a position dependent phase factor.
//! @ingroup formfactors_internal

class FormFactorDecoratorPositionFactor : public IFormFactorDecorator {
public:
    FormFactorDecoratorPositionFactor(const IFormFactor& ff, const kvector_t& position);

    FormFactorDecoratorPositionFactor* clone() const final {
        return new FormFactorDecoratorPositionFactor(*m_ff, m_position);
    }

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    double bottomZ(const IRotation& rotation) const final;

    double topZ(const IRotation& rotation) const final;

    complex_t evaluate(const WavevectorInfo& wavevectors) const final;
#ifndef SWIG
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const final;
#endif

private:
    complex_t getPositionFactor(const WavevectorInfo& wavevectors) const;

    kvector_t m_position;
};

#endif // BORNAGAIN_SAMPLE_SCATTERING_FORMFACTORDECORATORPOSITIONFACTOR_H
#endif // USER_API
