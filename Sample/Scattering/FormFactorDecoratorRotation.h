//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Scattering/FormFactorDecoratorRotation.h
//! @brief     Defines class FormFactorDecoratorRotation.
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
#ifndef BORNAGAIN_SAMPLE_SCATTERING_FORMFACTORDECORATORROTATION_H
#define BORNAGAIN_SAMPLE_SCATTERING_FORMFACTORDECORATORROTATION_H

#include "Base/Vector/Transform3D.h"
#include "Sample/Scattering/IFormFactorDecorator.h"

class IRotation;

//! Equips a form factor with a rotation.
//! @ingroup formfactors_internal

class FormFactorDecoratorRotation : public IFormFactorDecorator {
public:
    //! Constructor, setting form factor and rotation.
    FormFactorDecoratorRotation(const IFormFactor& ff, const IRotation& rotation);

    FormFactorDecoratorRotation* clone() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    double bottomZ(const IRotation& rotation) const final;

    double topZ(const IRotation& rotation) const final;

    complex_t evaluate(const WavevectorInfo& wavevectors) const final;
#ifndef SWIG
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const final;
#endif

private:
    Transform3D m_transform;
    //! Private constructor for cloning.
    FormFactorDecoratorRotation(const IFormFactor& ff, const Transform3D& transform);
};

#endif // BORNAGAIN_SAMPLE_SCATTERING_FORMFACTORDECORATORROTATION_H
#endif // USER_API
