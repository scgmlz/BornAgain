// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/RootMinimizerFunctions.h
//! @brief     Defines classes RootObjectiveFunction and RootGradientFunction
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ROOTMINIMIZERFUNCTIONS_H
#define ROOTMINIMIZERFUNCTIONS_H

#include "KernelTypes.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "Math/Functor.h"
#include "Math/FitMethodFunction.h"
#pragma GCC diagnostic pop

//! The chi2 function for use in minimizers.
//! @ingroup fitting_internal

class RootObjectiveFunction : public BA_ROOT::Math::Functor
{
 public:
    RootObjectiveFunction(root_objective_t fcn, int ndims )
        : BA_ROOT::Math::Functor(fcn, ndims) {}
};

//! Minimizer function with access to single data element residuals,
//! required by Fumili, Fumili2 and GSLMultiMin minimizers.
//! @ingroup fitting_internal

class RootGradientFunction : public BA_ROOT::Math::FitMethodFunction
{
 public:
    typedef BA_ROOT::Math::BasicFitMethodFunction<BA_ROOT::Math::IMultiGenFunction>::Type_t Type_t;

    RootGradientFunction(root_gradient_t fun_gradient, size_t npars, size_t ndatasize)
        : BA_ROOT::Math::FitMethodFunction((int)npars, (int)ndatasize)
        , m_fun_gradient(fun_gradient) { }

    Type_t Type() const { return BA_ROOT::Math::FitMethodFunction::kLeastSquare; }

    BA_ROOT::Math::IMultiGenFunction* Clone() const {
        return new RootGradientFunction(m_fun_gradient, NDim(), NPoints()); }

    //! evaluation of single data element residual
    double DataElement(const double* pars, unsigned int i_data, double* gradient = 0) const {
        return m_fun_gradient(pars, i_data, gradient);
    }

 private:
    //! evaluation of chi2
    double DoEval(const double* pars) const {
        double chi2 = 0.0;
        for(size_t i_data=0; i_data<NPoints(); ++i_data) {
            double  res = DataElement(pars, (unsigned)i_data);
            chi2 += res*res;
        }
        return chi2/double(NPoints());
    }

    root_gradient_t m_fun_gradient;
};

#endif // ROOTMINIMIZERFUNCTIONS_H
