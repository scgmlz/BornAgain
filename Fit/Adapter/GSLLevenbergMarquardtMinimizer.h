//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Adapter/GSLLevenbergMarquardtMinimizer.h
//! @brief     Declares class GSLLevenbergMarquardtMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_FIT_ADAPTER_GSLLEVENBERGMARQUARDTMINIMIZER_H
#define BORNAGAIN_FIT_ADAPTER_GSLLEVENBERGMARQUARDTMINIMIZER_H

#include "Fit/Adapter/MinimizerAdapter.h"

namespace ROOT::Math {
class GSLNLSMinimizer;
}

//! It's a facade to ROOT::Math::GSLNLSMinimizer which, in turn, is a facade to the
//! actual GSL's gsl_multifit_fdfsolver_type
//! (http://www.gnu.org/software/gsl/manual/html_node/Nonlinear-Least_002dSquares-Fitting.html).
//! @ingroup fitting_internal

class GSLLevenbergMarquardtMinimizer : public MinimizerAdapter {
public:
    GSLLevenbergMarquardtMinimizer();
    ~GSLLevenbergMarquardtMinimizer() override;

    //! Sets tolerance on the function value at the minimum.
    void setTolerance(double value);
    double tolerance() const;

    //! Sets minimizer internal print level.
    void setPrintLevel(int value);
    int printLevel() const;

    //! Sets maximum number of iterations. This is an internal minimizer setting which has
    //! no direct relation to the number of objective function calls (e.g. numberOfIteraction=5
    //! might correspond to ~100 objective function calls).
    void setMaxIterations(int value);
    int maxIterations() const;

    std::string statusToString() const override;
    std::map<std::string, std::string> statusMap() const override;

    bool requiresResiduals() override { return true; }

protected:
    void propagateOptions() override;
    const root_minimizer_t* rootMinimizer() const override;
    void setParameter(unsigned int index, const mumufit::Parameter& par) override;

private:
    std::unique_ptr<ROOT::Math::GSLNLSMinimizer> m_gsl_minimizer;
};

#endif // BORNAGAIN_FIT_ADAPTER_GSLLEVENBERGMARQUARDTMINIMIZER_H
#endif // USER_API
