// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/GSLMultiMinimizer.h
//! @brief     Declares class GSLMultiMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_FIT_ROOTADAPTER_GSLMULTIMINIMIZER_H
#define BORNAGAIN_FIT_ROOTADAPTER_GSLMULTIMINIMIZER_H

#include "Fit/RootAdapter/RootMinimizerAdapter.h"

namespace ROOT
{
namespace Math
{
class GSLMinimizer;
}
} // namespace ROOT

//! Wrapper for the CERN ROOT facade of the GSL multi minimizer family (gradient descent based).
//! @ingroup fitting_internal

class BA_CORE_API_ GSLMultiMinimizer : public RootMinimizerAdapter
{
public:
    explicit GSLMultiMinimizer(const std::string& algorithmName = "ConjugateFR");
    ~GSLMultiMinimizer();

    //! Sets minimizer internal print level.
    void setPrintLevel(int value);
    int printLevel() const;

    //! Sets maximum number of iterations. This is an internal minimizer setting which has
    //! no direct relation to the number of objective function calls (e.g. numberOfIteraction=5
    //! might correspond to ~100 objective function calls).
    void setMaxIterations(int value);
    int maxIterations() const;

    std::string statusToString() const override;

protected:
    void propagateOptions() override;
    const root_minimizer_t* rootMinimizer() const override;

private:
    std::unique_ptr<ROOT::Math::GSLMinimizer> m_gsl_minimizer;
};

#endif // BORNAGAIN_FIT_ROOTADAPTER_GSLMULTIMINIMIZER_H
