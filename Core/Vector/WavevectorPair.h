// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Vector/WavevectorPair.h
//! @brief     Defines WavevectorPair.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef WAVEVECTORINFO_H
#define WAVEVECTORINFO_H

#include "Complex.h"
#include "Vectors3D.h"

class Transform3D;

//! Holds all wavevector information relevant for calculating form factors.
//! @ingroup formfactors_internal

class BA_CORE_API_ WavevectorPair
{
public:
    WavevectorPair() {} // TODO: stop abuse for q=0, then =delete
    WavevectorPair(cvector_t ki, cvector_t kf) : m_ki(ki), m_kf(kf) {}
    WavevectorPair(kvector_t ki, kvector_t kf) : m_ki(ki.complex()), m_kf(kf.complex()) {}

    WavevectorPair newZZ(complex_t kiz, complex_t kfz) const;
    WavevectorPair transformed(const Transform3D& transform) const;
    cvector_t getKf() const { return m_kf; }
    cvector_t getQ() const { return m_ki - m_kf; }
    double K2() const { return m_ki.mag2(); }

private:
    cvector_t m_ki;
    cvector_t m_kf;
};

#endif // WAVEVECTORINFO_H
