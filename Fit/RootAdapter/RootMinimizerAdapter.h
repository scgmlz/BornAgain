// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/RootMinimizerAdapter.h
//! @brief     Declares class RootMinimizerAdapter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_FIT_ROOTADAPTER_ROOTMINIMIZERADAPTER_H
#define BORNAGAIN_FIT_ROOTADAPTER_ROOTMINIMIZERADAPTER_H

#include "Fit/Minimizer/IMinimizer.h"
#include "Fit/Minimizer/MinimizerInfo.h"
#include "Fit/Minimizer/MinimizerOptions.h"
#include <memory>
#include <string>

namespace Fit
{
class Parameters;
class Parameter;
class ObjectiveFunctionAdapter;
class MinimizerResult;
} // namespace Fit

namespace ROOT
{
namespace Math
{
class Minimizer;
}
} // namespace ROOT

//! Pure virtual interface that adapts the CERN ROOT minimizer to our IMinimizer.
//! @ingroup fitting_internal

class BA_CORE_API_ RootMinimizerAdapter : public IMinimizer
{
public:
    typedef ROOT::Math::Minimizer root_minimizer_t;

    virtual ~RootMinimizerAdapter() override;

    Fit::MinimizerResult minimize_scalar(fcn_scalar_t fcn, Fit::Parameters parameters) override;
    Fit::MinimizerResult minimize_residual(fcn_residual_t fcn, Fit::Parameters parameters) override;

    //! Returns name of the minimizer.
    std::string minimizerName() const override final;

    //! Returns name of the minimization algorithm.
    std::string algorithmName() const override final;

    void setParameters(const Fit::Parameters& parameters);

    double minValue() const override final;

    MinimizerOptions& options() { return m_options; }
    const MinimizerOptions& options() const { return m_options; }

    //! Returns string representation of current minimizer status.
    virtual std::string statusToString() const;

    //! Returns true if minimizer provides error and error matrix
    bool providesError() const;

    //! Returns map of string representing different minimizer statuses
    virtual std::map<std::string, std::string> statusMap() const;

    //! Sets option string to the minimizer
    void setOptions(const std::string& optionString) override final;

protected:
    RootMinimizerAdapter(const MinimizerInfo& minimizerInfo);

    Fit::MinimizerResult minimize(Fit::Parameters parameters);

    void propagateResults(Fit::Parameters& parameters);

    virtual void setParameter(unsigned int index, const Fit::Parameter& par);
    size_t fitDimension() const;
    std::vector<double> parValuesAtMinimum() const;
    std::vector<double> parErrorsAtMinimum() const;

    virtual void propagateOptions() = 0;
    virtual const root_minimizer_t* rootMinimizer() const = 0;
    root_minimizer_t* rootMinimizer();

    template <class T>
    OptionContainer::option_t addOption(const std::string& optionName, T value,
                                        const std::string& description = "");

    template <class T> void setOptionValue(const std::string& optionName, T value);

    template <class T> T optionValue(const std::string& optionName) const;

private:
    MinimizerOptions m_options;
    MinimizerInfo m_minimizerInfo;
    std::unique_ptr<Fit::ObjectiveFunctionAdapter> m_adapter;
    bool m_status;
};

template <class T>
OptionContainer::option_t RootMinimizerAdapter::addOption(const std::string& optionName, T value,
                                                          const std::string& description)
{
    return m_options.addOption(optionName, value, description);
}

template <class T> void RootMinimizerAdapter::setOptionValue(const std::string& optionName, T value)
{
    m_options.setOptionValue(optionName, value);
}

template <class T> T RootMinimizerAdapter::optionValue(const std::string& optionName) const
{
    return m_options.optionValue<T>(optionName);
}

#endif // BORNAGAIN_FIT_ROOTADAPTER_ROOTMINIMIZERADAPTER_H
