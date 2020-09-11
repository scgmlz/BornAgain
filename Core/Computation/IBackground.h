// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/IBackground.h
//! @brief     Defines interface IBackground.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_COMPUTATION_IBACKGROUND_H
#define BORNAGAIN_CORE_COMPUTATION_IBACKGROUND_H

#include "Core/Basics/ICloneable.h"
#include "Core/Parametrization/INode.h"

//! Interface for a simulating the background signal
//!
//! @ingroup algorithms_internal

class BA_CORE_API_ IBackground : public ICloneable, public INode
{
public:
    IBackground(const NodeMeta& meta, const std::vector<double>& PValues);
    virtual ~IBackground();
    virtual IBackground* clone() const = 0;

    virtual double addBackGround(double element) const = 0;
};

#endif // BORNAGAIN_CORE_COMPUTATION_IBACKGROUND_H
