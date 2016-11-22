// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitStrategyAdjustParameters.h
//! @brief     Defines classes FitStrategyAdjustParameters and related
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSTRATEGYADJUSTPARAMETERS_H
#define FITSTRATEGYADJUSTPARAMETERS_H

#include "IFitStrategy.h"
#include <vector>

//! Strategy which fixes/releases fit parameters and call minimizer.
//! @ingroup fitting

class BA_CORE_API_ FitStrategyAdjustParameters : public IFitStrategy
{
public:
    FitStrategyAdjustParameters(const std::string& name) : IFitStrategy(name) { clear(); }

    FitStrategyAdjustParameters() : IFitStrategy("FitSuiteStrategyAdjustParameters") { clear(); }

    virtual ~FitStrategyAdjustParameters(){}

    virtual FitStrategyAdjustParameters* clone() const {
        return new FitStrategyAdjustParameters(*this); }

    virtual void execute();

    virtual FitStrategyAdjustParameters& fix_all() {
        m_fix_all = true; return *this; }

    virtual FitStrategyAdjustParameters& release_all() {
        m_release_all = true; return *this; }

    virtual FitStrategyAdjustParameters& fix(std::string parname ) {
        m_pars_to_fix.push_back(parname);
        return *this; }

    virtual FitStrategyAdjustParameters& release(std::string parname ) {
        m_pars_to_release.push_back(parname);
        return *this; }

    virtual void setPreserveOriginalValues(bool preserve_values) {
        m_preserve_original_values = preserve_values; }

    virtual void clear() {
        m_fix_all = false;
        m_release_all = false;
        m_preserve_original_values = false;
        m_pars_to_fix.clear();
        m_pars_to_release.clear(); }

protected:
    FitStrategyAdjustParameters(const FitStrategyAdjustParameters& other);

    bool m_fix_all;
    bool m_release_all;
    std::vector<std::string> m_pars_to_fix;
    std::vector<std::string> m_pars_to_release;
    //! if it's true, strategy will set back values of parameters as they were
    //! before minimization round
    bool m_preserve_original_values;
};


//! Strategy which fixes certain fit parameters leaving other released.
//! @ingroup fitting

class BA_CORE_API_ FitStrategyFixParameters : public FitStrategyAdjustParameters
{
public:
    FitStrategyFixParameters() : FitStrategyAdjustParameters("FixStrategyFixParameters") {
        m_fix_all = false;
        m_release_all = true; }

    FitStrategyFixParameters(const std::vector<std::string> &pars)
        : FitStrategyAdjustParameters("FixStrategyFixParameters") {
        m_fix_all = false;
        m_release_all = true;
        setFixed(pars);  }

    virtual ~FitStrategyFixParameters(){}
    virtual FitStrategyFixParameters *clone() const { return new FitStrategyFixParameters(*this); }

    virtual void clear() {
        FitStrategyAdjustParameters::clear();
        m_release_all = true; }

    virtual void setFixed(const std::vector<std::string> &pars) { m_pars_to_fix = pars; }

};


//! Strategy which releases certain fit parameters leaving other fixed.
//! @ingroup fitting

class BA_CORE_API_ FitStrategyReleaseParameters : public FitStrategyAdjustParameters
{
public:
    FitStrategyReleaseParameters()
        : FitStrategyAdjustParameters("FixStrategyReleaseParameters")
    {
        m_fix_all = true;
        m_release_all = false;
    }

    FitStrategyReleaseParameters(const std::vector<std::string> &pars)
        : FitStrategyAdjustParameters("FixStrategyReleaseParameters") {
        m_fix_all = true;
        m_release_all = false;
        setReleased(pars); }


    virtual ~FitStrategyReleaseParameters(){}
    virtual FitStrategyReleaseParameters* clone() const {
        return new FitStrategyReleaseParameters(*this); }

    virtual void clear() {
        FitStrategyAdjustParameters::clear();
        m_fix_all = true; }

    virtual void setReleased(const std::vector<std::string>& pars) { m_pars_to_release = pars; }
};

#endif // FITSTRATEGYADJUSTPARAMETERS_H
