// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/SimAnMinimizer.h
//! @brief     Declares class SimAnMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_FIT_ROOTADAPTER_SIMANMINIMIZER_H
#define BORNAGAIN_FIT_ROOTADAPTER_SIMANMINIMIZER_H

#include "Fit/RootAdapter/RootMinimizerAdapter.h"

namespace ROOT
{
namespace Math
{
class GSLSimAnMinimizer;
}
} // namespace ROOT

//! Wrapper for the CERN ROOT facade of the GSL simmulated annealing minimizer.
//! @ingroup fitting_internal

class BA_CORE_API_ SimAnMinimizer : public RootMinimizerAdapter
{
public:
    SimAnMinimizer();
    ~SimAnMinimizer() override;

    //! Sets minimizer internal print level.
    //! Default value is 0 (silent).
    void setPrintLevel(int value);
    int printLevel() const;

    //! Sets maximum number of iterations to try at each step.
    void setMaxIterations(int value);
    int maxIterations() const;

    //! Sets number of iterations at each temperature.
    void setIterationsAtEachTemp(int value);
    int iterationsAtEachTemp() const;

    //! Sets max step size used in random walk.
    void setStepSize(double value);
    double stepSize() const;

    //! Sets Boltzmann distribution parameter: k.
    void setBoltzmannK(double value);
    double boltzmannK() const;

    //! Sets Boltzmann distribution parameter: initial temperature.
    void setBoltzmannInitialTemp(double value);
    double boltzmannInitialTemp() const;

    //! Sets Boltzmann distribution parameter: mu.
    void setBoltzmannMu(double value);
    double boltzmannMu() const;

    //! Sets Boltzmann distribution parameter: minimal temperature.
    void setBoltzmannMinTemp(double value);
    double boltzmannMinTemp() const;

    std::map<std::string, std::string> statusMap() const override;

protected:
    void propagateOptions() override;
    const root_minimizer_t* rootMinimizer() const override;

private:
    std::unique_ptr<ROOT::Math::GSLSimAnMinimizer> m_siman_minimizer;
};

#endif // BORNAGAIN_FIT_ROOTADAPTER_SIMANMINIMIZER_H
