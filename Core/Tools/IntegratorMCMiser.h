
// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/IntegratorMCMiser.h
//! @brief     Defines and implements template class IntegratorMCMiser.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTEGRATORMCMISER_H
#define INTEGRATORMCMISER_H

#include <gsl/gsl_monte_miser.h>
#include <memory>

//! Alias template for member function with signature double f(double)
template <class T>
using miser_integrand = double (T::*)(double *, size_t, void*) const;


//! Template class to use Monte Carlo MISER integration of class member functions.
//!
//! Wraps an integrator from GNU Scientific Library.
//! Since this class holds a persistent workspace, we need at least one instance per thread.
//! Standard usage for integration inside a class T:
//! - Create a handle to an integrator:
//!       'auto integrator = make_integrator_miser(this, mem_function, dimension)'
//! - Call: 'integrator.integrate(lmin, lmax, data, nbr_points)'
//! @ingroup tools_internal

template <class T> class IntegratorMCMiser
{
public:
    //! structure holding the object and possible extra parameters
    struct CallBackHolder {
        const T *m_object_pointer;
        miser_integrand<T> m_member_function;
        void *m_data;
    };

    //! to integrate p_member_function, which must belong to p_object
    IntegratorMCMiser(const T *p_object, miser_integrand<T> p_member_function, size_t dim);
    ~IntegratorMCMiser();

    //! perform the actual integration over the ranges [min_array, max_array]
    double integrate(double *min_array, double *max_array, void* params,
                     size_t nbr_points);

private:
    //! static function that can be passed to gsl integrator
    static double StaticCallBack(double *d_array, size_t dim, void *v) {
        CallBackHolder *p_cb = static_cast<CallBackHolder *>(v);
        auto mf = static_cast<miser_integrand<T>>(p_cb->m_member_function);
        return (p_cb->m_object_pointer->*mf)(d_array, dim, p_cb->m_data);
    }
    const T *mp_object;
    miser_integrand<T> m_member_function;
    size_t m_dim; //!< dimension of the integration
    gsl_monte_miser_state *m_gsl_workspace;
    gsl_rng *m_random_gen;
};


//! Alias template for handle to a miser integrator
template <class T>
using P_integrator_miser = std::unique_ptr<IntegratorMCMiser<T>>;


//! Template function to create an integrator object
//! @ingroup tools_internal

template <class T> P_integrator_miser<T>
make_integrator_miser(const T *object, miser_integrand<T> mem_function, size_t dim)
{
    P_integrator_miser<T> P_integrator(new IntegratorMCMiser<T>(object, mem_function, dim));
    return P_integrator;
}

// ************************************************************************** //
// Implementation
// ************************************************************************** //

template<class T> IntegratorMCMiser<T>::IntegratorMCMiser(
        const T *p_object, miser_integrand<T> p_member_function, size_t dim)
    : mp_object(p_object)
    , m_member_function(p_member_function)
    , m_dim(dim)
    , m_gsl_workspace { nullptr }
{
    m_gsl_workspace = gsl_monte_miser_alloc(m_dim);

    const gsl_rng_type * random_type;
    gsl_rng_env_setup();
    random_type = gsl_rng_default;
    m_random_gen = gsl_rng_alloc(random_type);
}

template<class T> IntegratorMCMiser<T>::~IntegratorMCMiser()
{
    gsl_monte_miser_free(m_gsl_workspace);
    gsl_rng_free(m_random_gen);
}

template<class T> double IntegratorMCMiser<T>::integrate(
        double *min_array, double *max_array, void* params, size_t nbr_points)
{
    CallBackHolder cb = { mp_object, m_member_function, params };

    gsl_monte_function f;
    f.f = StaticCallBack;
    f.dim = m_dim;
    f.params = &cb;

    double result, error;
    gsl_monte_miser_integrate(&f, min_array, max_array, m_dim, nbr_points,
                                    m_random_gen, m_gsl_workspace, &result, &error);
    return result;
}

#endif // INTEGRATORMCMISER_H
