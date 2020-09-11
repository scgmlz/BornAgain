// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunctionTwin.h
//! @brief     Defines class InterferenceFunctionTwin.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTIONTWIN_H
#define BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTIONTWIN_H

#include "Core/Aggregate/IInterferenceFunction.h"

//! Interference function for two particles at a mean distance and given standard deviation
//! from each other in a given direction.
//! @ingroup interference

class BA_CORE_API_ InterferenceFunctionTwin : public IInterferenceFunction
{
public:
    InterferenceFunctionTwin(const kvector_t& direction, double mean_distance, double std_dev);

    InterferenceFunctionTwin* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    kvector_t direction() const;
    double meanDistance() const;
    double stdDev() const;

private:
    double iff_without_dw(const kvector_t q) const override final;

    kvector_t m_direction;
    double m_distance;
    double m_std_dev;
};

#endif // BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTIONTWIN_H
