// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/AdjustMinimizerStrategy.h
//! @brief     Defines class AdjustMinimizerStrategy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ADJUSTMINIMIZERSTRATEGY_H
#define ADJUSTMINIMIZERSTRATEGY_H

#include "IFitStrategy.h"

//! Strategy modifies mimimizer settings before running minimization round.
//! @ingroup fitting

class BA_CORE_API_ AdjustMinimizerStrategy : public IFitStrategy
{
public:
    AdjustMinimizerStrategy();

    AdjustMinimizerStrategy(const std::string& minimizerName,
                               const std::string& algorithmName="",
                               const std::string& optionString="");

    virtual AdjustMinimizerStrategy* clone() const;

    void setMinimizer(const std::string& minimizerName,
                      const std::string& algorithmName="",
                      const std::string& optionString="");

    virtual void execute();

protected:
    virtual std::string toString() const;
    AdjustMinimizerStrategy(const AdjustMinimizerStrategy &other);

private:
    std::string m_minimizerName;
    std::string m_algorithmName;
    std::string m_optionString;
};

#endif // ADJUSTMINIMIZERSTRATEGY_H
