// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunctionNone.h
//! @brief     Defines class InterferenceFunctionNone.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTIONNONE_H
#define BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTIONNONE_H

#include "Core/Aggregate/IInterferenceFunction.h"

//! Default interference function (i.e. absence of any interference).
//! @ingroup interference

class BA_CORE_API_ InterferenceFunctionNone : public IInterferenceFunction
{
public:
    InterferenceFunctionNone();

    InterferenceFunctionNone* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

private:
    double iff_without_dw(const kvector_t q) const override final;
};

#endif // BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTIONNONE_H
