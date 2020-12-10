//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/MaterialKeyHandler.h
//! @brief     Defines class MaterialKeyHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_CORE_EXPORT_MATERIALKEYHANDLER_H
#define BORNAGAIN_CORE_EXPORT_MATERIALKEYHANDLER_H

#include <map>
#include <string>
#include <vector>

class Material;

//! Stores Material instances, associates them with given tag, and provides unique keys.
//! @ingroup tools_internal

class MaterialKeyHandler {
public:
    void insertMaterial(const Material* sample);

    const std::map<const std::string, const Material*>& materialMap() const;
    const std::string& mat2key(const Material* sample) const;

private:
    std::map<const Material*, const Material*> m_Mat2Unique;
    std::map<const std::string, const Material*> m_Key2Mat;
};

#endif // BORNAGAIN_CORE_EXPORT_MATERIALKEYHANDLER_H
#endif // USER_API
