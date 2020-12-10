//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Correlations/IPeakShape.h
//! @brief     Defines the interface IPeakShape and subclasses.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_CORRELATIONS_IPEAKSHAPE_H
#define BORNAGAIN_SAMPLE_CORRELATIONS_IPEAKSHAPE_H

#include "Sample/Scattering/ISampleNode.h"

//! Abstract base class class that defines the peak shape of a Bragg peak.
//!
//! @ingroup samples_internal

class IPeakShape : public ISampleNode {
public:
    IPeakShape() = default;
    IPeakShape(const NodeMeta& meta, const std::vector<double>& PValues);

    virtual ~IPeakShape();

    virtual IPeakShape* clone() const = 0;

    //! Evaluates the peak shape at q from a reciprocal lattice point at q_lattice_point
    virtual double evaluate(const kvector_t q, const kvector_t q_lattice_point) const = 0;

    //! Indicates if the peak shape encodes angular disorder, in which case all peaks in a
    //! spherical shell are needed
    virtual bool angularDisorder() const { return false; }
};

//! Class that implements an isotropic Gaussian peak shape of a Bragg peak.
//!
//! @ingroup samples_internal

class IsotropicGaussPeakShape : public IPeakShape {
public:
    IsotropicGaussPeakShape(double max_intensity, double domainsize);
    ~IsotropicGaussPeakShape() override;

    IsotropicGaussPeakShape* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    double evaluate(const kvector_t q, const kvector_t q_lattice_point) const override;

private:
    double evaluate(const kvector_t q) const;
    double m_max_intensity;
    double m_domainsize;
};

//! An isotropic Lorentzian peak shape of a Bragg peak.
//!
//! @ingroup samples_internal

class IsotropicLorentzPeakShape : public IPeakShape {
public:
    IsotropicLorentzPeakShape(double max_intensity, double domainsize);
    ~IsotropicLorentzPeakShape() override;

    IsotropicLorentzPeakShape* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    double evaluate(const kvector_t q, const kvector_t q_lattice_point) const override;

private:
    double evaluate(const kvector_t q) const;
    double m_max_intensity;
    double m_domainsize;
};

//! A peak shape that is Gaussian in the radial direction and
//! uses the Mises-Fisher distribution in the angular direction.
//!
//! @ingroup samples_internal

class GaussFisherPeakShape : public IPeakShape {
public:
    GaussFisherPeakShape(double max_intensity, double radial_size, double kappa);
    ~GaussFisherPeakShape() override;

    GaussFisherPeakShape* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    double evaluate(const kvector_t q, const kvector_t q_lattice_point) const override;

    bool angularDisorder() const override { return true; }

private:
    double m_max_intensity;
    double m_radial_size;
    double m_kappa;
};

//! A peak shape that is Lorentzian in the radial direction and uses the
//! Mises-Fisher distribution in the angular direction.
//!
//! @ingroup samples_internal

class LorentzFisherPeakShape : public IPeakShape {
public:
    LorentzFisherPeakShape(double max_intensity, double radial_size, double kappa);
    ~LorentzFisherPeakShape() override;

    LorentzFisherPeakShape* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    double evaluate(const kvector_t q, const kvector_t q_lattice_point) const override;

    bool angularDisorder() const override { return true; }

private:
    double m_max_intensity;
    double m_radial_size;
    double m_kappa;
};

//! A peak shape that is Gaussian in the radial direction and a convolution of a
//! Mises-Fisher distribution with a Mises distribution on the two-sphere.
//!
//! @ingroup samples_internal

class MisesFisherGaussPeakShape : public IPeakShape {
public:
    MisesFisherGaussPeakShape(double max_intensity, double radial_size, kvector_t zenith,
                              double kappa_1, double kappa_2);
    ~MisesFisherGaussPeakShape() override;

    MisesFisherGaussPeakShape* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    double evaluate(const kvector_t q, const kvector_t q_lattice_point) const override;

    bool angularDisorder() const override { return true; }

private:
    double m_max_intensity;
    double m_radial_size;
    kvector_t m_zenith;
    double m_kappa_1, m_kappa_2;

    double integrand(double phi) const;
    mutable double m_theta, m_phi;
    mutable kvector_t m_ux, m_uy, m_up;
};

//! A peak shape that is a convolution of a Mises-Fisher distribution with a 3d Gaussian.
//!
//! @ingroup samples_internal

class MisesGaussPeakShape : public IPeakShape {
public:
    MisesGaussPeakShape(double max_intensity, double radial_size, kvector_t zenith, double kappa);
    ~MisesGaussPeakShape() override;

    MisesGaussPeakShape* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    double evaluate(const kvector_t q, const kvector_t q_lattice_point) const override;

    bool angularDisorder() const override { return true; }

private:
    double m_max_intensity;
    double m_radial_size;
    kvector_t m_zenith;
    double m_kappa;

    double integrand(double phi) const;
    mutable double m_theta, m_phi, m_qr;
    mutable kvector_t m_ux, m_uy, m_p;
};

#endif // BORNAGAIN_SAMPLE_CORRELATIONS_IPEAKSHAPE_H
#endif // USER_API
