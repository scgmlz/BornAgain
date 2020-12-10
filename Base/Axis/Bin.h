//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Axis/Bin.h
//! @brief     Defines structs Bin1D, Bin1DCVector
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_BASE_AXIS_BIN_H
#define BORNAGAIN_BASE_AXIS_BIN_H

#include "Base/Vector/Vectors3D.h"

struct Bin1D {
    Bin1D() : m_lower(0), m_upper(0) {}
    Bin1D(double lower, double upper) : m_lower(lower), m_upper(upper) {}
    double m_lower; //!< lower bound of the bin
    double m_upper; //!< upper bound of the bin
    double center() const { return (m_lower + m_upper) / 2.0; }
    double binSize() const { return m_upper - m_lower; }
};

//! Checks if value is contained in bin:
//! value in [m_lower, m_upper)
bool BinContains(const Bin1D& bin, double value);

//! An one-dimensional range of kvector_t's.
//! @ingroup tools_internal

struct Bin1DKVector {
    Bin1DKVector() : m_q_lower(), m_q_upper() {}
    Bin1DKVector(const kvector_t lower, const kvector_t upper)
        : m_q_lower(lower), m_q_upper(upper) {}
    Bin1DKVector(double wavelength, const Bin1D& alpha_bin, const Bin1D& phi_bin);

    kvector_t center() const { return (m_q_lower + m_q_upper) / 2.0; }
    kvector_t span() const { return m_q_upper - m_q_lower; }
    kvector_t m_q_lower; //!< lower bound of the bin
    kvector_t m_q_upper; //!< upper bound of the bin
};

//! An one-dimensional range of cvector_t's.
//! @ingroup tools_internal

class Bin1DCVector {
public:
    Bin1DCVector() : m_q_lower(), m_q_upper() {}
    Bin1DCVector(cvector_t lower, cvector_t upper) : m_q_lower(lower), m_q_upper(upper) {}
    Bin1DCVector(double wavelength, const Bin1D& alpha_bin, const Bin1D& phi_bin);
    cvector_t center() const { return (m_q_lower + m_q_upper) / 2.0; }
    cvector_t span() const { return m_q_upper - m_q_lower; }
    cvector_t m_q_lower; //!< lower bound of the bin
    cvector_t m_q_upper; //!< upper bound of the bin
};

#endif // BORNAGAIN_BASE_AXIS_BIN_H
