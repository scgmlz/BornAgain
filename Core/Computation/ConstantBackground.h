//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ConstantBackground.h
//! @brief     Defines class ConstantBackground.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_CORE_COMPUTATION_CONSTANTBACKGROUND_H
#define BORNAGAIN_CORE_COMPUTATION_CONSTANTBACKGROUND_H

#include "Core/Computation/IBackground.h"

//! Class representing a constant background signal
//!
//! @ingroup simulation

class ConstantBackground : public IBackground {
public:
    ConstantBackground(const std::vector<double> P);
    ConstantBackground(double background_value);

    ConstantBackground* clone() const final;

    double backgroundValue() const { return m_background_value; }

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    double addBackground(double intensity) const final;

private:
    const double& m_background_value;
};

#endif // BORNAGAIN_CORE_COMPUTATION_CONSTANTBACKGROUND_H
