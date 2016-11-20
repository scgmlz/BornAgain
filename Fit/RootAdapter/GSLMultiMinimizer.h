// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/GSLMultiMinimizer.h
//! @brief     Declares class GSLMultiMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GSLMULTIMINIMIZER_H
#define GSLMULTIMINIMIZER_H

#include "RootMinimizerAdapter.h"
#include "MinimizerConstants.h"

namespace BA_ROOT { namespace Math { class GSLMinimizer; } }

//! Wrapper for the GSL multi minimizer family (gradient descent based).
//! @ingroup fitting_internal

class BA_CORE_API_ GSLMultiMinimizer : public RootMinimizerAdapter {
public:
    explicit GSLMultiMinimizer(const std::string &algorithmName = AlgorithmNames::ConjugateFR);
    ~GSLMultiMinimizer();

    //! Sets minimizer internal print level.
    void setPrintLevel(int value);
    int printLevel() const;

    //! Sets maximum number of iterations. This is an internal minimizer setting which has
    //! no direct relation to the number of objective function calls (e.g. numberOfIteraction=5
    //! might correspond to ~100 objective function calls).
    void setMaxIterations(int value);
    int maxIterations() const;

    std::string statusToString() const;

protected:
    void propagateOptions();
    const root_minimizer_t* rootMinimizer() const;

private:
    std::unique_ptr<BA_ROOT::Math::GSLMinimizer> m_gsl_minimizer;
};

#endif // GSLMULTIMINIMIZER_H
