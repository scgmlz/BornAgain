// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Vector/WavevectorInfo.h
//! @brief     Defines WavevectorInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_VECTOR_WAVEVECTORINFO_H
#define BORNAGAIN_CORE_VECTOR_WAVEVECTORINFO_H

#include "Core/Vector/Vectors3D.h"

class Transform3D;

//! Holds all wavevector information relevant for calculating form factors.
//! @ingroup formfactors_internal

class BA_CORE_API_ WavevectorInfo
{
public:
    static WavevectorInfo GetZeroQ();
    WavevectorInfo(cvector_t ki, cvector_t kf, double wavelength)
        : m_ki(ki), m_kf(kf), m_vacuum_wavelength(wavelength)
    {
    }
    WavevectorInfo(kvector_t ki, kvector_t kf, double wavelength)
        : m_ki(ki.complex()), m_kf(kf.complex()), m_vacuum_wavelength(wavelength)
    {
    }

    WavevectorInfo transformed(const Transform3D& transform) const;
    cvector_t getKi() const { return m_ki; }
    cvector_t getKf() const { return m_kf; }
    cvector_t getQ() const { return m_ki - m_kf; }
    double getWavelength() const { return m_vacuum_wavelength; }

private:
    WavevectorInfo();
    cvector_t m_ki;
    cvector_t m_kf;
    double m_vacuum_wavelength;
};

#endif // BORNAGAIN_CORE_VECTOR_WAVEVECTORINFO_H
