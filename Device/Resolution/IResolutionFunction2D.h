//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Resolution/IResolutionFunction2D.h
//! @brief     Defines interface class IResolutionFunction2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef USER_API
#ifndef BORNAGAIN_DEVICE_RESOLUTION_IRESOLUTIONFUNCTION2D_H
#define BORNAGAIN_DEVICE_RESOLUTION_IRESOLUTIONFUNCTION2D_H

#include "Base/Types/ICloneable.h"
#include "Param/Node/INode.h"

//! Interface providing two-dimensional resolution function.
//! @ingroup algorithms_internal

class IResolutionFunction2D : public ICloneable, public INode {
public:
    IResolutionFunction2D() = default;
    IResolutionFunction2D(const NodeMeta& meta, const std::vector<double>& PValues);

    virtual ~IResolutionFunction2D() {}

    virtual double evaluateCDF(double x, double y) const = 0;
    virtual IResolutionFunction2D* clone() const = 0;
};

#endif // BORNAGAIN_DEVICE_RESOLUTION_IRESOLUTIONFUNCTION2D_H
#endif // USER_API
