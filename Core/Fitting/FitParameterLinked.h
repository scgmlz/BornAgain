// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitParameterLinked.h
//! @brief     Defines class FitParameterLinked.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITPARAMETERLINKED_H
#define FITPARAMETERLINKED_H

#include "FitParameter.h"
#include <vector>

class ParameterPool;
class RealParameter;

//! Fittable parameter, linked to other parameters from pools.
//! @ingroup fitting_internal

class BA_CORE_API_ FitParameterLinked : public FitParameter
{
public:
    FitParameterLinked() {}
    FitParameterLinked(
        const std::string& name, double value, const AttLimits& lim = AttLimits::limitless(),
        double step = 0.0);
    ~FitParameterLinked() final;

    FitParameterLinked* clone() const;

    void setValue(double value) final;

    void addParameter(RealParameter* par);

    void addMatchedParametersFromPool(
        const ParameterPool* pool, const std::string& wildcard = std::string());

    friend std::ostream& operator<<(std::ostream& ostr, const FitParameterLinked& m)
    {
        m.print(ostr);
        return ostr;
    }

private:
    void print(std::ostream& ostr) const;

    std::vector<RealParameter*> m_pool_parameters; //!< linked parameters from pools
};

#endif // FITPARAMETERLINKED_H
