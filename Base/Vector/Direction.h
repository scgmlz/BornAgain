//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Vector/Direction.h
//! @brief     Defines class Direction.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_BASE_VECTOR_DIRECTION_H
#define BORNAGAIN_BASE_VECTOR_DIRECTION_H

#include "Base/Vector/Vectors3D.h"

kvector_t vecOfLambdaAlphaPhi(double _lambda, double _alpha, double _phi);

//! A direction in three-dimensional space.

class Direction {
public:
    Direction(double alpha, double phi) : m_alpha(alpha), m_phi(phi) {}
    Direction() : Direction(0, 0) {} // needed by Swig

    void setAlpha(double alpha) { m_alpha = alpha; }
    void setPhi(double phi) { m_phi = phi; }

    double alpha() const { return m_alpha; }
    double phi() const { return m_phi; }

    //! Returns Cartesian 3D vector
    kvector_t vector() const;

private:
    double m_alpha;
    double m_phi;
};

#endif // BORNAGAIN_BASE_VECTOR_DIRECTION_H
