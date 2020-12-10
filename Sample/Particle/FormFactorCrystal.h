//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Particle/FormFactorCrystal.h
//! @brief     Defines class FormFactorCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_PARTICLE_FORMFACTORCRYSTAL_H
#define BORNAGAIN_SAMPLE_PARTICLE_FORMFACTORCRYSTAL_H

#include "Sample/Lattice/Lattice3D.h"
#include "Sample/Scattering/IBornFF.h"

//! The form factor of a MesoCrystal.
//! @ingroup formfactors

class FormFactorCrystal : public IFormFactor {
public:
    FormFactorCrystal(const Lattice3D& lattice, const IFormFactor& basis_form_factor,
                      const IFormFactor& meso_form_factor, double position_variance = 0.0);
    ~FormFactorCrystal() override;

    FormFactorCrystal* clone() const override {
        return new FormFactorCrystal(m_lattice, *m_basis_form_factor, *m_meso_form_factor,
                                     m_position_variance);
    }

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    void setAmbientMaterial(const Material& material) override {
        m_basis_form_factor->setAmbientMaterial(material);
    }

    double volume() const override { return m_meso_form_factor->volume(); }
    double radialExtension() const override { return m_meso_form_factor->radialExtension(); }

    double bottomZ(const IRotation& rotation) const override;

    double topZ(const IRotation& rotation) const override;

    complex_t evaluate(const WavevectorInfo& wavevectors) const override;
#ifndef SWIG
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const override;
#endif

private:
    void calculateLargestReciprocalDistance();
    complex_t debyeWallerFactor(const kvector_t& q_i) const;

    Lattice3D m_lattice;
    IFormFactor* m_basis_form_factor;
    IFormFactor* m_meso_form_factor; //!< The outer shape of this mesocrystal
    double m_position_variance;
    double m_max_rec_length;
};

#endif // BORNAGAIN_SAMPLE_PARTICLE_FORMFACTORCRYSTAL_H
