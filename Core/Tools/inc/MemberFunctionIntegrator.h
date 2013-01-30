#ifndef MEMBERFUNCTIONINTEGRATOR_H_
#define MEMBERFUNCTIONINTEGRATOR_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   MemberFunctionIntegrator.h
//! @brief  Definition of MemberFunctionIntegrator template
//! @author Scientific Computing Group at FRM II
//! @date   Nov 26, 2012

#include "gsl/gsl_integration.h"

template <class C> class MemberFunctionIntegrator
{
public:
    //! member function type
    typedef double (C::*mem_function)(double, void*) const;

    //! structure holding the object and possible extra parameters
    struct CallBackHolder {
        const C *m_object_pointer;
        mem_function m_member_function;
        void *m_data;
    };

    //! constructor taking a member function and the object whose member function to integrate
    MemberFunctionIntegrator();
    MemberFunctionIntegrator(mem_function p_member_function, const C *const p_object);
    ~MemberFunctionIntegrator();

    //! perform the actual integration over the range [lmin, lmax]
    double integrate(double lmin, double lmax, void *params);

    //! set integrand
    void setIntegrand(mem_function member_function) { m_member_function = member_function; }
    void setIntegrand(mem_function member_function, const C *const p_object) { m_member_function = member_function; mp_object = p_object; }

private:
    //! static function that can be passed to gsl integrator
    static double StaticCallBack(double d, void *v) {
        CallBackHolder *p_cb = static_cast<CallBackHolder *>(v);
        mem_function mf = p_cb->m_member_function;
        return (p_cb->m_object_pointer->*mf)(d, p_cb->m_data);
    }
    mem_function m_member_function; //!< the member function to integrate
    const C *mp_object; //!< the object whose member function to integrate
    gsl_integration_workspace *m_gsl_workspace;
};

template<class C> MemberFunctionIntegrator<C>::MemberFunctionIntegrator(
        mem_function p_member_function, const C *const p_object)
: m_member_function(p_member_function)
, mp_object(p_object)
, m_gsl_workspace(0)
{
    m_gsl_workspace = gsl_integration_workspace_alloc(200);
}

template<class C> MemberFunctionIntegrator<C>::MemberFunctionIntegrator()
: m_member_function(0)
, mp_object(0)
, m_gsl_workspace(0)
{
    m_gsl_workspace = gsl_integration_workspace_alloc(200);
}

template<class C> MemberFunctionIntegrator<C>::~MemberFunctionIntegrator()
{
    gsl_integration_workspace_free(m_gsl_workspace);
}



template<class C> double MemberFunctionIntegrator<C>::integrate(
        double lmin, double lmax, void* params)
{
    assert(mp_object);
    assert(m_member_function);

    CallBackHolder cb = { mp_object, m_member_function, params };

    gsl_function f;
    f.function = StaticCallBack;
    f.params = &cb;

//    gsl_integration_workspace *ws = gsl_integration_workspace_alloc(200);
//    double result, error;
//    gsl_integration_qag(&f, lmin, lmax, 1e-10, 1e-8, 50, 1, ws, &result, &error);
//    gsl_integration_workspace_free(ws);

    double result, error;
    gsl_integration_qag(&f, lmin, lmax, 1e-10, 1e-8, 50, 1, m_gsl_workspace, &result, &error);

    return result;
}

#endif /* MEMBERFUNCTIONINTEGRATOR_H_ */
