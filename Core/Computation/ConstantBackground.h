// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ConstantBackground.h
//! @brief     Defines class ConstantBackground.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CONSTANTBACKGROUND_H
#define CONSTANTBACKGROUND_H

#include "IBackground.h"

//! Class representing a constant background signal
//!
//! @ingroup simulation

class BA_CORE_API_ ConstantBackground : public IBackground
{
public:
    ConstantBackground(double background_value);
    ~ConstantBackground();
    ConstantBackground* clone() const override final;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    void addBackGround(std::vector<SimulationElement>::iterator start,
                       std::vector<SimulationElement>::iterator end) const override final;
private:
    void init_parameters();

    double m_background_value;
};

#endif // CONSTANTBACKGROUND_H
