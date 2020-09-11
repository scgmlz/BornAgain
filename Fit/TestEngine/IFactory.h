// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/TestEngine/IFactory.h
//! @brief     Defines interface class IFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_FIT_TESTENGINE_IFACTORY_H
#define BORNAGAIN_FIT_TESTENGINE_IFACTORY_H

#include <cassert>
#include <functional>
#include <iostream> // debug
#include <map>
#include <memory>
#include <sstream>

//! Base class for all factories.
//! @ingroup tools_internal

template <class Key, class AbstractProduct> class IFactory
{
public:
    //! function which will be used to create object of AbstractProduct base type
    typedef typename std::function<AbstractProduct*()> CreateItemCallback;

    //! map for correspondance between object identifier and object creation function
    typedef std::map<Key, CreateItemCallback> CallbackMap_t;

    //! Creates object by calling creation function corresponded to given identifier
    AbstractProduct* createItem(const Key& item_key) const
    {
        auto it = m_callbacks.find(item_key);
        assert(it != m_callbacks.end());
        return (it->second)();
    }

#ifndef SWIG
    std::unique_ptr<AbstractProduct> createItemPtr(const Key& item_key) const
    {
        return std::unique_ptr<AbstractProduct>{createItem(item_key)};
    }
#endif

    //! Registers object's creation function
    bool registerItem(const Key& item_key, CreateItemCallback CreateFn)
    {
        assert(m_callbacks.find(item_key) == m_callbacks.end());
        return m_callbacks.insert(make_pair(item_key, CreateFn)).second;
    }

    bool contains(const Key& item_key) const
    {
        return m_callbacks.find(item_key) != m_callbacks.end();
    }

    //! Returns number of registered objects
    size_t size() const { return m_callbacks.size(); }

protected:
    CallbackMap_t m_callbacks; //!< map of correspondence of objectsId and creation functions
};

//! Returns new instance of class T.
//!
//! This templated function is used in catalogs in form of a function pointer
//! 'create_new<T>', with no function arguments supplied. Equivalently, we could
//! use a lambda function '[](){return new T;}'.

template <class T> T* create_new()
{
    return new T();
}

#endif // BORNAGAIN_FIT_TESTENGINE_IFACTORY_H
