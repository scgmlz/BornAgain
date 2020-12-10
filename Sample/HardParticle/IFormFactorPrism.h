//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/IFormFactorPrism.h
//! @brief     Defines interface IFormFactorPrism.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_HARDPARTICLE_IFORMFACTORPRISM_H
#define BORNAGAIN_SAMPLE_HARDPARTICLE_IFORMFACTORPRISM_H

#include "Sample/Scattering/IBornFF.h"
#include <memory>

class Prism;

//! A prism with a polygonal base, for form factor computation.

class IFormFactorPrism : public IBornFF {
public:
    IFormFactorPrism(const NodeMeta& meta, const std::vector<double>& PValues);
    ~IFormFactorPrism();

    double bottomZ(const IRotation& rotation) const final;
    double topZ(const IRotation& rotation) const final;

    complex_t evaluate_for_q(cvector_t q) const override;
    double volume() const override;
    double radialExtension() const override;
    double getHeight() const;

protected:
    void setPrism(bool symmetry_Ci, const std::vector<kvector_t>& vertices);
    virtual double height() const = 0; // TODO mv parameter m_height back from children to this

private:
    std::unique_ptr<Prism> pimpl;
};

#endif // BORNAGAIN_SAMPLE_HARDPARTICLE_IFORMFACTORPRISM_H
#endif // USER_API
