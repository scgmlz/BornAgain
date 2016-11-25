// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/IShareable.h
//! @brief     Defines the class ISharable (used for SWIG smart pointers)
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISHAREABLE_H
#define ISHAREABLE_H

//! @class IShareable
//! @ingroup tools_internal
//! @brief Dummy interface used to construct INamedShared and IParameterizedShared
class BA_CORE_API_ IShareable
{
private:
    //! Default constructor, made private since this class should never by instantiated
    IShareable() {}
};

#endif // ISHAREABLE_H
