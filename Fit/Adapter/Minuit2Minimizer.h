//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Adapter/Minuit2Minimizer.h
//! @brief     Declares class Minuit2Minimizer.
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
#ifndef BORNAGAIN_FIT_ADAPTER_MINUIT2MINIMIZER_H
#define BORNAGAIN_FIT_ADAPTER_MINUIT2MINIMIZER_H

#include "Fit/Adapter/MinimizerAdapter.h"
#include <memory>

namespace ROOT::Minuit2 {
class Minuit2Minimizer;
}

//! Wrapper for the CERN ROOT facade of the Minuit2 minimizer.
//! See Minuit2 user manual https://root.cern.ch/root/htmldoc/guides/minuit2/Minuit2.pdf.
//! @ingroup fitting_internal

class Minuit2Minimizer : public MinimizerAdapter {
public:
    Minuit2Minimizer(const std::string& algorithmName = "Migrad");
    ~Minuit2Minimizer();

    //! Sets minimization strategy (0-low, 1-medium, 2-high minimization quality).
    //! At low quality number of function calls will be economized.
    void setStrategy(int value);
    int strategy() const;

    //! Sets error definition factor for parameter error calculation.
    //! If objective function (OF) is the usual chisquare function and if the user wants the usual
    //! one-standard-deviation errors, then the error definition should be 1.0. If OF is a
    //! negative-log-likelihood function, then 0.5. If OF is a chisquare, but the user wants
    //! two-standard-deviation errors, 4.0.
    void setErrorDefinition(double value);
    double errorDefinition() const;

    //! Sets tolerance on the function value at the minimum.
    //! Minimization will stop when the estimated vertical distance to the minimum (EDM) is less
    //! than 0.001*tolerance*ErrorDef. Here ErrorDef=1.0 for chi squared fit and ErrorDef=0.5
    //! for negative log likelihood fit.
    void setTolerance(double value);
    double tolerance() const;

    //! Sets relative floating point arithmetic precision.
    //! Should be adjusted when the user knows that objectiove function value is not
    //! calculated to the nominal machine accuracy. Typical values are between 10^-5 and 10^-14.
    void setPrecision(double value);
    double precision() const;

    //! Sets minimizer internal print level.
    //! Default value is 0 (silent).
    void setPrintLevel(int value);
    int printLevel() const;

    //! Sets maximum number of objective function calls.
    void setMaxFunctionCalls(int value);
    int maxFunctionCalls() const;

    std::string statusToString() const override;
    std::map<std::string, std::string> statusMap() const override;

    bool requiresResiduals() override;

protected:
    void propagateOptions() override;
    const root_minimizer_t* rootMinimizer() const override;

private:
    std::unique_ptr<ROOT::Minuit2::Minuit2Minimizer> m_minuit2_minimizer;
};

#endif // BORNAGAIN_FIT_ADAPTER_MINUIT2MINIMIZER_H
#endif // USER_API
