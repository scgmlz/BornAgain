//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Aggregate/InterferenceFunctionNone.h
//! @brief     Defines class InterferenceFunctionNone.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTIONNONE_H
#define BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTIONNONE_H

#include "Sample/Aggregate/IInterferenceFunction.h"

//! Default interference function (i.e. absence of any interference).
//! @ingroup interference

class InterferenceFunctionNone : public IInterferenceFunction {
public:
    InterferenceFunctionNone();

    InterferenceFunctionNone* clone() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

private:
    double iff_without_dw(const kvector_t q) const final;
};

#endif // BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTIONNONE_H
