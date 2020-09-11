// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/OrderedMap.h
//! @brief     Defines class OrderedMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_EXPORT_ORDEREDMAP_H
#define BORNAGAIN_CORE_EXPORT_ORDEREDMAP_H

#include "Core/Basics/Assert.h"
#include <iostream>
#include <list>
#include <stdexcept>
#include <unordered_map>

//! @class OrderedMap
//! @ingroup tools_internal
//! @brief Ordered map which saves the order of insertion

template <class Key, class Object> class OrderedMap
{
public:
    typedef std::pair<Key, Object> entry_t;
    typedef std::list<entry_t> list_t;
    typedef typename list_t::iterator iterator;
    typedef typename list_t::const_iterator const_iterator;
    typedef std::unordered_map<Key, iterator> map_t;

    OrderedMap() {}
    virtual ~OrderedMap() {}

    void clear()
    {
        m_map.clear();
        m_list.clear();
    }

    const_iterator begin() const { return m_list.begin(); }
    const_iterator end() const { return m_list.end(); }
    iterator begin() { return m_list.begin(); }
    iterator end() { return m_list.end(); }

    size_t size()
    {
        ASSERT(m_list.size() == m_map.size());
        return m_list.size();
    }

    // if such key exists, pair will be deleted, and new pair appended to the end
    void insert(const Key& key, const Object& object)
    {
        erase(key);
        iterator it = m_list.insert(m_list.end(), std::make_pair(key, object));
        m_map[key] = it;
    }

    iterator find(const Key& key)
    {
        iterator result = m_list.end();
        if (m_map.find(key) != m_map.end()) {
            result = m_map[key];
        }
        return result;
    }

    const_iterator find(const Key& key) const
    {
        const_iterator result = m_list.end();
        if (m_map.find(key) != m_map.end()) {
            result = m_map[key];
        }
        return result;
    }

    size_t erase(const Key& key)
    {
        size_t result(0);
        if (m_map.find(key) == m_map.end())
            return result;
        iterator it = m_map[key];
        m_list.erase(it);
        m_map.erase(key);
        return 1;
    }

    const Object& value(const Key& key)
    {
        typename map_t::const_iterator mit = m_map.find(key);
        if (mit == m_map.end()) {
            throw std::runtime_error("OrderedMap::value() -> No such key");
        }
        const_iterator it = mit->second;
        return (*it).second;
    }

    const Object& operator[](const Key& key) { return value(key); }

private:
    map_t m_map;
    list_t m_list;
};

#endif // BORNAGAIN_CORE_EXPORT_ORDEREDMAP_H
