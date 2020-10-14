// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Types/ICloneable.h
//! @brief     Defines and implements the standard mix-in ICloneable.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_BASE_TYPES_ICLONEABLE_H
#define BORNAGAIN_BASE_TYPES_ICLONEABLE_H

//! Interface for polymorphic classes that should not be copied, except by explicit cloning.
//!
//! Child classes of ICloneable must provide clone().

//! @ingroup tools_internal

class ICloneable
{
public:
    ICloneable() = default;
    virtual ~ICloneable() = default;

    ICloneable(const ICloneable&) = delete;
    ICloneable(ICloneable&&) = default;

    virtual ICloneable* clone() const = 0;
    virtual void transferToCPP() {} //!< Used for Python overriding of clone (see swig/tweaks.py)
};

#endif // BORNAGAIN_BASE_TYPES_ICLONEABLE_H
