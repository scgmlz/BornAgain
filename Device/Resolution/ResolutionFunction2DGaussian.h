//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Resolution/ResolutionFunction2DGaussian.h
//! @brief     Defines class ResolutionFunction2DGaussian.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_DEVICE_RESOLUTION_RESOLUTIONFUNCTION2DGAUSSIAN_H
#define BORNAGAIN_DEVICE_RESOLUTION_RESOLUTIONFUNCTION2DGAUSSIAN_H

#include "Device/Resolution/IResolutionFunction2D.h"

//! Simple gaussian two-dimensional resolution function.
//! @ingroup algorithms_internal

class ResolutionFunction2DGaussian : public IResolutionFunction2D {
public:
    ResolutionFunction2DGaussian(double sigma_x, double sigma_y);

    virtual double evaluateCDF(double x, double y) const;

    ResolutionFunction2DGaussian* clone() const {
        return new ResolutionFunction2DGaussian(m_sigma_x, m_sigma_y);
    }

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    double getSigmaX() const { return m_sigma_x; }
    double getSigmaY() const { return m_sigma_y; }

private:
    ResolutionFunction2DGaussian& operator=(const ResolutionFunction2DGaussian&);

    double m_sigma_x;
    double m_sigma_y;
};

#endif // BORNAGAIN_DEVICE_RESOLUTION_RESOLUTIONFUNCTION2DGAUSSIAN_H
