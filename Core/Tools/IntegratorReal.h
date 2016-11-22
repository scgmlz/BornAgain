// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/IntegratorReal.h
//! @brief     Defines and implements class template IntegratorReal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTEGRATORREAL_H
#define INTEGRATORREAL_H

#include <gsl/gsl_integration.h>
#include <memory>

//! Alias template for member function with signature double f(double)
template <class T>
using real_integrand = double (T::*)(double) const;


//! Template class to integrate class member functions.
//!
//! Wraps an integrator from the GNU Scientific Library.
//! Since this class holds a persistent workspace, we need at least one instance per thread.
//! Standard usage for integration inside a class T:
//! - Create a handle to an integrator: 'auto integrator = make_integrator_real(this, mem_function)'
//! - Call: 'integrator.integrate(lmin, lmax)'
//! @ingroup tools_internal

template <class T> class IntegratorReal
{
public:
    //! structure holding the object and possible extra parameters
    struct CallBackHolder {
        const T *m_object_pointer;
        real_integrand<T> m_member_function;
    };

    //! to integrate p_member_function, which must belong to p_object
    IntegratorReal(const T *p_object, real_integrand<T> p_member_function);
    ~IntegratorReal();

    //! perform the actual integration over the range [lmin, lmax]
    double integrate(double lmin, double lmax);

private:
    //! static function that can be passed to gsl integrator
    static double StaticCallBack(double d, void *v) {
        CallBackHolder *p_cb = static_cast<CallBackHolder *>(v);
        auto mf = static_cast<real_integrand<T>>(p_cb->m_member_function);
        return (p_cb->m_object_pointer->*mf)(d);
    }
    CallBackHolder m_cb;
    gsl_integration_workspace *mp_gsl_workspace;
};


//! Alias template for handle to a real integrator
template <class T>
using P_integrator_real = std::unique_ptr<IntegratorReal<T>>;


//! Template function to create an integrator object.
//! @ingroup tools_internal

template <class T>
P_integrator_real<T> make_integrator_real(const T *object, real_integrand<T> mem_function)
{
    P_integrator_real<T> P_integrator(new IntegratorReal<T>(object, mem_function));
    return P_integrator;
}

// ************************************************************************** //
// Implementation
// ************************************************************************** //

template<class T> IntegratorReal<T>::IntegratorReal(
    const T *p_object, real_integrand<T> p_member_function)
    : mp_gsl_workspace { nullptr }
{
    m_cb = CallBackHolder{ p_object, p_member_function };
    mp_gsl_workspace = gsl_integration_workspace_alloc(200);
}

template<class T> IntegratorReal<T>::~IntegratorReal()
{
    gsl_integration_workspace_free(mp_gsl_workspace);
}

template<class T> double IntegratorReal<T>::integrate(double lmin, double lmax)
{
    gsl_function f;
    f.function = StaticCallBack;
    f.params =&m_cb;

    double result, error;
    gsl_integration_qag(&f, lmin, lmax, 1e-10, 1e-8, 50, 1,  mp_gsl_workspace, &result, &error);

    return result;
}
#endif // INTEGRATORREAL_H
