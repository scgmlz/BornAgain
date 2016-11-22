// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/IFitStrategy.h
//! @brief     Defines interface class IFitStrategy, and class FitStrategyDefault
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IFITSTRATEGY_H
#define IFITSTRATEGY_H

#include "INamed.h"

class FitSuiteImpl;

//! Interface to concrete fit strategy.
//! Concrete implementation should manipulate with fit parameters/data and then call minimizer.
//! @ingroup fitting_internal

class BA_CORE_API_ IFitStrategy : public INamed
{
public:
    explicit IFitStrategy(const std::string& name);
    IFitStrategy& operator=(const IFitStrategy &other) = delete;
    virtual ~IFitStrategy() {}

    virtual IFitStrategy* clone() const =0;

    virtual void init(FitSuiteImpl* fit_suite);
    virtual void execute() =0;

    friend std::ostream &operator<<(std::ostream &ostr, const IFitStrategy &m) {
        ostr << m.toString(); return ostr; }

protected:
    IFitStrategy(const IFitStrategy &other);

    virtual std::string toString() const;
    FitSuiteImpl* m_kernel;
};


//! Default fit strategy just let FitSuite to run it's minimization round.
//! @ingroup fitting

class BA_CORE_API_ FitStrategyDefault : public IFitStrategy
{
public:
    FitStrategyDefault();
    virtual FitStrategyDefault* clone() const;
    virtual void execute();

protected:
    FitStrategyDefault(const FitStrategyDefault &other);
};

#endif // IFITSTRATEGY_H
