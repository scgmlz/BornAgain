// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Wrap/WinDllMacros.h
//! @brief     Defines macroses for building dll.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BORNAGAIN_WRAP_WINDLLMACROS_H
#define BORNAGAIN_WRAP_WINDLLMACROS_H

#ifdef _WIN32

#ifdef BA_CORE_BUILD_DLL

#define BA_CORE_API_ __declspec(dllexport)
#else
#define BA_CORE_API_ __declspec(dllimport)
#endif // BA_CORE_BUILD_DLL

#endif // _WIN32

#ifndef BA_CORE_API_
#define BA_CORE_API_
#endif

#endif // BORNAGAIN_WRAP_WINDLLMACROS_H
