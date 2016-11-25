// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/FormFactorCrystal.h
//! @brief     Defines class FormFactorCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORCRYSTAL_H
#define FORMFACTORCRYSTAL_H

#include "IFormFactorBorn.h"
#include "Lattice.h"

//! The formfactor of a MesoCrystal.
//! @ingroup formfactors

class BA_CORE_API_ FormFactorCrystal : public IFormFactor
{
public:
    FormFactorCrystal(
        const Lattice& lattice, const IFormFactor& basis_form_factor,
        const IFormFactor& meso_form_factor);
    ~FormFactorCrystal() override final;

    FormFactorCrystal* clone() const override final
    {
        return new FormFactorCrystal(m_lattice, *mp_basis_form_factor, *mp_meso_form_factor);
    }

    void accept(ISampleVisitor* visitor) const override final { visitor->visit(this); }

    double getVolume() const override final { return mp_meso_form_factor->getVolume(); }
    double getRadialExtension() const override final
    {
        return mp_meso_form_factor->getRadialExtension();
    }

    complex_t evaluate(const WavevectorInfo& wavevectors) const override final;
#ifndef SWIG
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const override final;
#endif

private:
    void calculateLargestReciprocalDistance();

    Lattice m_lattice;
    IFormFactor* mp_basis_form_factor;
    IFormFactor* mp_meso_form_factor; //!< The outer shape of this mesocrystal
    double m_max_rec_length;
};

#endif // FORMFACTORCRYSTAL_H
