// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/RootMinimizerAdapter.h
//! @brief     Declares class RootMinimizerAdapter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ROOTMINIMIZERADAPTER_H
#define ROOTMINIMIZERADAPTER_H

#include "IMinimizer.h"
#include "MinimizerOptions.h"
#include "MinimizerInfo.h"
#include <string>
#include <memory>

class RootObjectiveFunctionAdapter;
class FitParameter;

namespace BA_ROOT { namespace Math { class Minimizer; } }

//! Pure virtual interface that adapts the CERN ROOT minimizer to our IMinimizer.
//! @ingroup fitting_internal

class BA_CORE_API_ RootMinimizerAdapter : public IMinimizer
{
public:
    typedef BA_ROOT::Math::Minimizer root_minimizer_t;

    virtual ~RootMinimizerAdapter();

    virtual void minimize() override;

    //! Returns name of the minimizer.
    std::string minimizerName() const override final;

    //! Returns name of the minimization algorithm.
    std::string algorithmName() const override final;

    void setParameters(const FitParameterSet& parameters) override final;

    void setObjectiveFunction(objective_function_t func) override final;

    void setGradientFunction(gradient_function_t func, int ndatasize) override final;

    double minValue() const override final;

    std::string reportOutcome() const override final;

    MinimizerOptions& options() { return m_options; }
    const MinimizerOptions& options() const { return m_options; }

    //! Returns string representation of current minimizer status.
    virtual std::string statusToString() const;

    //! Returns true if minimizer provides error and error matrix
    bool providesError() const;

    //! Returns map of string representing different minimizer statuses
    virtual std::map<std::string, std::string> statusMap() const;

    //! Propagates results of minimization to fit parameter set
    void propagateResults(FitParameterSet& parameters) override;

    //! Sets option string to the minimizer
    void setOptions(const std::string& optionString) override final;

protected:
    RootMinimizerAdapter(const MinimizerInfo& minimizerInfo);

    virtual bool isGradientBasedAgorithm() { return false;}
    virtual void setParameter(size_t index, const FitParameter *par);
    int fitDimension() const;
    std::vector<double> parValuesAtMinimum() const;
    std::vector<double> parErrorsAtMinimum() const;

    virtual void propagateOptions() = 0;
    virtual const root_minimizer_t* rootMinimizer() const = 0;
    root_minimizer_t* rootMinimizer();

    template<class T>
    OptionContainer::option_t addOption(
        const std::string& optionName, T value, const std::string& description="");

    template<class T>
    void setOptionValue(const std::string& optionName, T value);

    template<class T>
    T optionValue(const std::string& optionName) const;

private:
    MinimizerOptions m_options;
    MinimizerInfo m_minimizerInfo;
    std::unique_ptr<RootObjectiveFunctionAdapter> m_obj_func;
    bool m_status;
};

template<class T>
OptionContainer::option_t RootMinimizerAdapter::addOption(
    const std::string& optionName, T value, const std::string& description)
{
    return m_options.addOption(optionName, value, description);
}

template<class T>
void RootMinimizerAdapter::setOptionValue(const std::string& optionName, T value)
{
    m_options.setOptionValue(optionName, value);
}

template<class T>
T RootMinimizerAdapter::optionValue(const std::string& optionName) const
{
    return m_options.optionValue<T>(optionName);
}

#endif // ROOTMINIMIZERADAPTER_H
