// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Mask/InfinitePlane.h
//! @brief     Defines class InfinitePlane.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INFINITEPLANE_H
#define INFINITEPLANE_H

#include "IShape2D.h"

//! The infinite plane is used for masking everything once and forever.
//! @ingroup tools

class BA_CORE_API_ InfinitePlane : public IShape2D {
public:
    InfinitePlane() : IShape2D("InfinitePlane") {}
    InfinitePlane* clone() const { return new InfinitePlane(); }

    bool contains(double, double) const { return true; }
    bool contains(const Bin1D&, const Bin1D&) const { return true; }
};

#endif // INFINITEPLANE_H
