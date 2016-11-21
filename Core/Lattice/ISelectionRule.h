// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Lattice/ISelectionRule.h
//! @brief     Defines classes ISelectionRule, SimpleSelectionRule
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISELECTIONRULE_H
#define ISELECTIONRULE_H

#include "Vectors3D.h"

//! Pure virtual base class for selection rules.
//! @ingroup samples_internal

class BA_CORE_API_ ISelectionRule
{
public:
    virtual ~ISelectionRule() {}

    virtual ISelectionRule* clone() const=0;

    virtual bool coordinateSelected(const ivector_t& coordinate) const=0;
};

//! Selection rule (v*q)%modulus!=0, defined by vector v(a,b,c) and modulus.
//! @ingroup samples_internal

class SimpleSelectionRule : public ISelectionRule
{
public:
    SimpleSelectionRule(int a, int b, int c, int modulus);
    virtual ~SimpleSelectionRule() {}

    virtual SimpleSelectionRule* clone() const;

    virtual bool coordinateSelected(const ivector_t& coordinate) const;
private:
    int m_a, m_b, m_c;
    int m_mod;
};

inline SimpleSelectionRule::SimpleSelectionRule(int a, int b, int c, int modulus)
    : m_a(a), m_b(b), m_c(c), m_mod(modulus) {}

inline SimpleSelectionRule* SimpleSelectionRule::clone() const
{
    return new SimpleSelectionRule(m_a, m_b, m_c, m_mod);
}

inline bool SimpleSelectionRule::coordinateSelected(const ivector_t& coordinate) const
{
    return (m_a*coordinate[0]+m_b*coordinate[1]+m_c*coordinate[2])%m_mod == 0;
}

#endif // ISELECTIONRULE_H
