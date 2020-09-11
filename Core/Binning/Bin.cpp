// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Binning/Bin.cpp
//! @brief     Implements structs Bin1D, Bin1DCVector
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Binning/Bin.h"

bool BinContains(const Bin1D& bin, double value)
{
    if (bin.getBinSize() == 0.0)
        return false;
    double coordinate = (value - bin.m_lower) / bin.getBinSize();
    if (coordinate < 0.0)
        return false;
    if (coordinate >= 1.0)
        return false;
    return true;
}

//! creation on Bin1DKVector from alpha and phi bins
Bin1DKVector::Bin1DKVector(double wavelength, const Bin1D& alpha_bin, const Bin1D& phi_bin)
    : m_q_lower(), m_q_upper()
{
    m_q_lower = vecOfLambdaAlphaPhi(wavelength, alpha_bin.m_lower, phi_bin.m_lower);
    m_q_upper = vecOfLambdaAlphaPhi(wavelength, alpha_bin.m_upper, phi_bin.m_upper);
}

//! creation on Bin1DCVector from alpha and phi bins
Bin1DCVector::Bin1DCVector(double wavelength, const Bin1D& alpha_bin, const Bin1D& phi_bin)
    : m_q_lower(), m_q_upper()
{
    m_q_lower = vecOfLambdaAlphaPhi(wavelength, alpha_bin.m_lower, phi_bin.m_lower).complex();
    m_q_upper = vecOfLambdaAlphaPhi(wavelength, alpha_bin.m_upper, phi_bin.m_upper).complex();
}
