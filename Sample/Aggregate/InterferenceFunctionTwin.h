//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Aggregate/InterferenceFunctionTwin.h
//! @brief     Defines class InterferenceFunctionTwin.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTIONTWIN_H
#define BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTIONTWIN_H

#include "Sample/Aggregate/IInterferenceFunction.h"

//! Interference function for two particles at a mean distance and given standard deviation
//! from each other in a given direction.
//! @ingroup interference

class InterferenceFunctionTwin : public IInterferenceFunction {
public:
    InterferenceFunctionTwin(const kvector_t& direction, double mean_distance, double std_dev);

    InterferenceFunctionTwin* clone() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    kvector_t direction() const;
    double meanDistance() const;
    double stdDev() const;

private:
    double iff_without_dw(const kvector_t q) const final;

    kvector_t m_direction;
    double m_distance;
    double m_std_dev;
};

#endif // BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTIONTWIN_H
