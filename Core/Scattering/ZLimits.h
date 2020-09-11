// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/ZLimits.h
//! @brief     Defines class ZLimits.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SCATTERING_ZLIMITS_H
#define BORNAGAIN_CORE_SCATTERING_ZLIMITS_H

#include "Wrap/WinDllMacros.h"
#include <iostream>

//! Vertical extension of a particle, specified by bottom and top z coordinate.
struct ParticleLimits {
    double m_bottom;
    double m_top;
};

//! Helper class that represents a onesided limit
//!
//! @ingroup intern

struct BA_CORE_API_ OneSidedLimit {
    bool m_limitless;
    double m_value;
};

//! Class that contains upper and lower limits of the z-coordinate for the slicing of
//! form factors.
//!
//! @ingroup intern

class BA_CORE_API_ ZLimits
{
public:
    ZLimits();
    ZLimits(double min, double max);
    ZLimits(OneSidedLimit lower_limit, OneSidedLimit upper_limit);

    bool isFinite() const;

    OneSidedLimit lowerLimit() const;
    OneSidedLimit upperLimit() const;

private:
    OneSidedLimit m_lower;
    OneSidedLimit m_upper;
};

OneSidedLimit MinLimit(const OneSidedLimit& left, const OneSidedLimit& right);
OneSidedLimit MaxLimit(const OneSidedLimit& left, const OneSidedLimit& right);
bool operator==(const OneSidedLimit& left, const OneSidedLimit& right);
bool operator!=(const OneSidedLimit& left, const OneSidedLimit& right);

std::ostream& operator<<(std::ostream& ostr, const OneSidedLimit& limit);

BA_CORE_API_ ZLimits ConvexHull(const ZLimits& left, const ZLimits& right);
BA_CORE_API_ bool operator==(const ZLimits& left, const ZLimits& right);
BA_CORE_API_ bool operator!=(const ZLimits& left, const ZLimits& right);

BA_CORE_API_ std::ostream& operator<<(std::ostream& ostr, const ZLimits& limits);

#endif // BORNAGAIN_CORE_SCATTERING_ZLIMITS_H
