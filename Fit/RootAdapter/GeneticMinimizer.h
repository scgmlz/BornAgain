// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/GeneticMinimizer.h
//! @brief     Declares class GeneticMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_FIT_ROOTADAPTER_GENETICMINIMIZER_H
#define BORNAGAIN_FIT_ROOTADAPTER_GENETICMINIMIZER_H

#include "Fit/RootAdapter/RootMinimizerAdapter.h"

namespace ROOT
{
namespace Math
{
class GeneticMinimizer;
}
} // namespace ROOT

//! Wrapper for the CERN ROOT Genetic minimizer.
//! @ingroup fitting_internal

class BA_CORE_API_ GeneticMinimizer : public RootMinimizerAdapter
{
public:
    GeneticMinimizer();
    ~GeneticMinimizer();

    //! Sets tolerance on the function value at the minimum.
    //! Minimization will stop when the estimated vertical distance to the minimum (EDM) is less
    //! than 0.001*tolerance*ErrorDef. Here ErrorDef=1.0 for chi squared fit and ErrorDef=0.5
    //! for negative log likelihood fit.
    void setTolerance(double value);
    double tolerance() const;

    //! Sets minimizer internal print level.
    void setPrintLevel(int value);
    int printLevel() const;

    //! Sets maximum number of iterations to try at each step.
    void setMaxIterations(int value);
    int maxIterations() const;

    //! Sets population size.
    void setPopulationSize(int value);
    int populationSize() const;

    //! Sets random seed.
    void setRandomSeed(int value);
    int randomSeed() const;

    std::string statusToString() const override;
    std::map<std::string, std::string> statusMap() const override;

protected:
    void propagateOptions() override;
    const root_minimizer_t* rootMinimizer() const override;

    using RootMinimizerAdapter::setParameter;
    void setParameter(unsigned int index, const Fit::Parameter& par) override;

private:
    std::unique_ptr<ROOT::Math::GeneticMinimizer> m_genetic_minimizer;
};

#endif // BORNAGAIN_FIT_ROOTADAPTER_GENETICMINIMIZER_H
