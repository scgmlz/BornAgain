// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FormFactorWrapper.h
//! @brief     Defines class FormFactorWrapper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORWRAPPER_H
#define FORMFACTORWRAPPER_H

#include "ICloneable.h"
class IFormFactor;

//! Information about particle form factor and abundance.
//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorWrapper : public ICloneable
{
public:
    FormFactorWrapper(IFormFactor* ff, double abundance) : mp_ff(ff), m_abundance(abundance) {}
    virtual ~FormFactorWrapper();
    virtual FormFactorWrapper* clone() const;
    IFormFactor* mp_ff;
    double m_abundance;
};

#endif // FORMFACTORWRAPPER_H
