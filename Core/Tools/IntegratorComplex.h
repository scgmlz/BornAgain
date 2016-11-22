// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/IntegratorComplex.h
//! @brief     Defines and implements class template IntegratorComplex.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTEGRATORCOMPLEX_H
#define INTEGRATORCOMPLEX_H

#include "IntegratorReal.h"


//! Alias template for member function with signature complex_t f(double)
template <class T>
using complex_integrand = complex_t (T::*)(double) const;


//! Template class to integrate complex class member functions.
//!
//! Wraps an two integrators from the GNU Scientific Library.
//! Since this class holds a persistent workspace, we need at least one instance per thread.
//! Standard usage for integration inside a class T:
//! - Create a handle to an integrator:
//!      'auto integrator = make_integrator_complex(this, mem_function)'
//! - Call: 'integrator.integrate(lmin, lmax)'
//! @ingroup tools_internal

template <class T> class IntegratorComplex
{
public:
    //! to integrate p_member_function, which must belong to p_object
    IntegratorComplex(const T *p_object, complex_integrand<T> p_member_function);
    ~IntegratorComplex() {}

    //! perform the actual integration over the range [lmin, lmax]
    complex_t integrate(double lmin, double lmax);

private:
    double real(double value) const;
    double imag(double value) const;
    const T *mp_object_pointer;
    complex_integrand<T> mp_member_function;
    P_integrator_real<IntegratorComplex<T>> mP_real_integrator;
    P_integrator_real<IntegratorComplex<T>> mP_imag_integrator;
};


//! Alias template for handle to a real integrator
template <class T>
using P_integrator_complex = std::unique_ptr<IntegratorComplex<T>>;


//! Template function to create an integrator object.
//! @ingroup tools_internal

template <class T>
P_integrator_complex<T> make_integrator_complex(const T *object, complex_integrand<T> mem_function)
{
    P_integrator_complex<T> P_integrator(new IntegratorComplex<T>(object, mem_function));
    return P_integrator;
}

// ************************************************************************** //
// Implementation
// ************************************************************************** //

template<class T> IntegratorComplex<T>::IntegratorComplex(
        const T *p_object, complex_integrand<T> p_member_function)
    : mp_object_pointer { p_object }
    , mp_member_function { p_member_function }
{
    mP_real_integrator = make_integrator_real(this, &IntegratorComplex<T>::real);
    mP_imag_integrator = make_integrator_real(this, &IntegratorComplex<T>::imag);
}

template<class T> complex_t IntegratorComplex<T>::integrate(
        double lmin, double lmax)
{
   double real = mP_real_integrator->integrate(lmin, lmax);
   double imag = mP_imag_integrator->integrate(lmin, lmax);
   return complex_t(real, imag);
}

template<class T> double IntegratorComplex<T>::real(double value) const
{
    return (mp_object_pointer->*mp_member_function)(value).real();
}

template<class T> double IntegratorComplex<T>::imag(double value) const
{
    return (mp_object_pointer->*mp_member_function)(value).imag();
}

#endif // INTEGRATORCOMPLEX_H
