// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Vector/SomeFormFactors.cpp
//! @brief     Implements namespace someff with some form factor functions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Vector/SomeFormFactors.h"

//! Returns the form factor of a sphere of radius R.
//!
//! Used by the hard sphere and by several soft sphere classes.

complex_t someff::ffSphere(cvector_t q, double R)
{
    complex_t q1 =
        sqrt(q.x() * q.x() + q.y() * q.y() + q.z() * q.z()); // NO sesquilinear dot product!
    complex_t qR = q1 * R;

    if (std::abs(qR) < 1e-4) { // relative error is O(qR^4) with small prefactor
        // expand sin(qR)-qR*cos(qR) up to qR^5
        return 4 * M_PI / 3 * pow(R, 3) * (1. - 0.1 * pow(qR, 2));
    }
    return 4 * M_PI * pow(q1, -3) * (sin(qR) - qR * cos(qR));
}
