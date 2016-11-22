// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IResolutionFunction2D.h
//! @brief     Defines interface class IResolutionFunction2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IRESOLUTIONFUNCTION2D_H
#define IRESOLUTIONFUNCTION2D_H

#include "IParameterized.h"

//! Interface providing two-dimensional resolution function.
//! @ingroup algorithms_internal

class BA_CORE_API_ IResolutionFunction2D : public IParameterized
{
public:
    virtual ~IResolutionFunction2D() {}

    virtual double evaluateCDF(double x, double y) const =0;
    virtual IResolutionFunction2D* clone() const =0;
};

#endif // IRESOLUTIONFUNCTION2D_H
