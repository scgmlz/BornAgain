// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/SimAnMinimizer.h
//! @brief     Declares class SimAnMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SIMANMINIMIZER_H
#define SIMANMINIMIZER_H

#include "RootMinimizerAdapter.h"

namespace BA_ROOT { namespace Math { class GSLSimAnMinimizer; } }

//! Wrapper for ROOT GSL simmulated annealing minimizer
//! @ingroup fitting_internal

class BA_CORE_API_ SimAnMinimizer : public RootMinimizerAdapter {
public:
    SimAnMinimizer();
    ~SimAnMinimizer();

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

    std::map<std::string, std::string> statusMap() const;
    virtual bool isGradientBasedAgorithm() { return false; }

protected:
    void propagateOptions();
    const root_minimizer_t* rootMinimizer() const;

private:
    std::unique_ptr<BA_ROOT::Math::GSLSimAnMinimizer> m_siman_minimizer;
};

#endif // SIMANMINIMIZER_H
