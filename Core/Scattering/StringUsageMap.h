// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/StringUsageMap.h
//! @brief     Defines and implements class StringUsageMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef STRINGUSAGEMAP_H
#define STRINGUSAGEMAP_H

#include <map>
#include <string>

//! Counts how often a string is used.
//! @ingroup tools_internal

class BA_CORE_API_ StringUsageMap
{
public:
    typedef std::map<std::string, int> nstringmap_t;
    typedef nstringmap_t::iterator iterator_t;

    StringUsageMap() {}
    ~StringUsageMap() {}

    //! Adds string to the map, or increments usage counter
    void add(const std::string& name)
    {
        m_current_string = name;
        iterator_t it = m_nstringmap.find(name);
        if (it != m_nstringmap.end())
            it->second++;
        else
            m_nstringmap.insert(make_pair(name, 1));
    }

    //! access to the map of strings
    iterator_t begin() { return m_nstringmap.begin(); }
    iterator_t end() { return m_nstringmap.end(); }
    int& operator[](const std::string& name) { return m_nstringmap[name]; }

    //! Returns current string
    std::string get_current() const { return m_current_string; }

private:
    std::string m_current_string;
    nstringmap_t m_nstringmap;
};

#endif // STRINGUSAGEMAP_H
