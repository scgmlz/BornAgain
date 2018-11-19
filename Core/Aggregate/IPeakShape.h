// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/IPeakShape.h
//! @brief     Defines the interface IPeakShape and subclasses.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IPEAKSHAPE_H
#define IPEAKSHAPE_H

#include "ISample.h"
#include "Vectors3D.h"

//! Pure virtual interface class that defines the peak shape of a Bragg peak.
//!
//! @ingroup samples_internal

class BA_CORE_API_ IPeakShape : public ISample
{
public:
    virtual ~IPeakShape();

    virtual IPeakShape* clone() const=0;

    //! Evaluates the peak shape at q from a reciprocal lattice point at q_lattice_point
    virtual double evaluate(const kvector_t q, const kvector_t q_lattice_point) const=0;

    //! Indicates if the peak shape encodes angular disorder, in which case all peaks in a
    //! spherical shell are needed
    virtual bool angularDisorder() const { return false; }
};


//! Class that implements an isotropic Gaussian peak shape of a Bragg peak.
//!
//! @ingroup samples_internal

class BA_CORE_API_ IsotropicGaussPeakShape : public IPeakShape
{
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

//! Class that implements an isotropic Lorentzian peak shape of a Bragg peak.
//!
//! @ingroup samples_internal

class BA_CORE_API_ IsotropicLorentzPeakShape : public IPeakShape
{
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

//! Class that implements a peak shape that is Gaussian in the radial direction and
//! uses the von Mises-Fisher distribution in the angular direction.
//!
//! @ingroup samples_internal

class BA_CORE_API_ GaussFisherPeakShape : public IPeakShape
{
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

//! Class that implements a peak shape that is Lorentzian in the radial direction and
//! uses the von Mises-Fisher distribution in the angular direction.
//!
//! @ingroup samples_internal

class BA_CORE_API_ LorentzFisherPeakShape : public IPeakShape
{
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

#endif // IPEAKSHAPE_H
