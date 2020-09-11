// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/IRegistry.h
//! @brief     Defines templated registry for ICloneable objects
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_IREGISTRY_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_IREGISTRY_H

#include "Core/Basics/Exceptions.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

//! @class IRegistry
//! @ingroup tools_internal
//! @brief Templated object registry.

template <class ValueType> class IRegistry
{
public:
    const ValueType* getItem(const std::string& key) const
    {
        auto it = m_data.find(key);
        if (it == m_data.end())
            throw Exceptions::UnknownClassRegistrationException(
                "IRegistry::createItem() -> Error. Not existing item key '" + key + "'");
        return it->second.get();
    }

    std::vector<std::string> keys()
    {
        std::vector<std::string> result;
        for (auto it = m_data.begin(); it != m_data.end(); ++it)
            result.push_back(it->first);
        return result;
    }

    size_t size() const { return m_data.size(); }

protected:
    void add(const std::string& key, ValueType* item)
    {
        if (m_data.find(key) != m_data.end())
            throw Exceptions::ExistingClassRegistrationException(
                "IRegistry::createItem() -> Error. Already existing item with key '" + key + "'");
        m_data[key] = std::unique_ptr<ValueType>(item);
    }

private:
    std::map<std::string, std::unique_ptr<ValueType>> m_data;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_IREGISTRY_H
