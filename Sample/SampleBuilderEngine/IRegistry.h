//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/SampleBuilderEngine/IRegistry.h
//! @brief     Defines templated registry for ICloneable objects
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
#ifndef BORNAGAIN_SAMPLE_SAMPLEBUILDERENGINE_IREGISTRY_H
#define BORNAGAIN_SAMPLE_SAMPLEBUILDERENGINE_IREGISTRY_H

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

//! @class IRegistry
//! @ingroup tools_internal
//! @brief Templated object registry.

template <class ValueType> class IRegistry {
public:
    const ValueType* getItem(const std::string& key) const {
        auto it = m_data.find(key);
        if (it == m_data.end())
            throw std::runtime_error("Key '" + key + "' not found in registry");
        return it->second.get();
    }

    std::vector<std::string> keys() const {
        std::vector<std::string> result;
        for (const auto& it : m_data)
            result.push_back(it.first);
        return result;
    }

    size_t size() const { return m_data.size(); }

protected:
    void add(const std::string& key, ValueType* item) {
        if (m_data.find(key) != m_data.end())
            throw std::runtime_error("Key '" + key + "' already in registry");
        m_data[key] = std::unique_ptr<ValueType>(item);
    }

private:
    std::map<std::string, std::unique_ptr<ValueType>> m_data;
};

#endif // BORNAGAIN_SAMPLE_SAMPLEBUILDERENGINE_IREGISTRY_H
#endif // USER_API
