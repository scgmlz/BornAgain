// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/IResolutionFunction2D.h
//! @brief     Defines interface class IResolutionFunction2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_DETECTOR_IRESOLUTIONFUNCTION2D_H
#define BORNAGAIN_CORE_DETECTOR_IRESOLUTIONFUNCTION2D_H

#include "Core/Basics/ICloneable.h"
#include "Core/Parametrization/INode.h"

//! Interface providing two-dimensional resolution function.
//! @ingroup algorithms_internal

class BA_CORE_API_ IResolutionFunction2D : public ICloneable, public INode
{
public:
    IResolutionFunction2D() = default;
    IResolutionFunction2D(const NodeMeta& meta, const std::vector<double>& PValues);

    virtual ~IResolutionFunction2D() {}

    virtual double evaluateCDF(double x, double y) const = 0;
    virtual IResolutionFunction2D* clone() const = 0;
};

#endif // BORNAGAIN_CORE_DETECTOR_IRESOLUTIONFUNCTION2D_H
