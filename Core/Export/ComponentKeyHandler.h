//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/ComponentKeyHandler.h
//! @brief     Defines class ComponentKeyHandler.
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
#ifndef BORNAGAIN_CORE_EXPORT_COMPONENTKEYHANDLER_H
#define BORNAGAIN_CORE_EXPORT_COMPONENTKEYHANDLER_H

#include <map>
#include <string>
#include <vector>

class IComponent;

//! Stores IComponent instances, associates them with given tag, and provides unique keys.
//! @ingroup tools_internal

class ComponentKeyHandler {
public:
    void insertModel(const std::string& tag, const IComponent* s);

    template <class T> std::vector<const T*> objectsOfType() const;
    std::string obj2key(const IComponent* s) const;

private:
    std::map<std::string, std::vector<const IComponent*>> m_objects;
};

template <class T> std::vector<const T*> ComponentKeyHandler::objectsOfType() const {
    std::vector<const T*> ret;
    for (auto it : m_objects)
        for (const IComponent* s : it.second)
            if (const auto* c = dynamic_cast<const T*>(s); c)
                ret.emplace_back(c);
    return ret;
}

#endif // BORNAGAIN_CORE_EXPORT_COMPONENTKEYHANDLER_H
#endif // USER_API
