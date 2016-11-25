// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/IFactory.h
//! @brief     Defines interface class IFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IFACTORY_H
#define IFACTORY_H

#include "Exceptions.h"
#include <functional>
#include <map>
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

    //! map for correspondance between object identifier and object description
    typedef std::map<Key, std::string> DescriptionMap_t;
    typedef typename DescriptionMap_t::iterator iterator;
    typedef typename DescriptionMap_t::const_iterator const_iterator;

    IFactory() {}

    //! Creates object by calling creation function corresponded to given identifier
    AbstractProduct* createItem(const Key& item_key)
    {
        auto it = m_callbacks.find(item_key);
        if (it == m_callbacks.end()) {
            std::ostringstream message;
            message << "IFactory::createItem() -> Error. Unknown item key '" << item_key << "'";
            throw Exceptions::RuntimeErrorException(message.str());
        }
        return (it->second)();
    }

    //! Registers object's creation function and store object description
    bool registerItem(
        const Key& item_key, CreateItemCallback CreateFn, const std::string& itemDescription = "")
    {
        if (m_callbacks.find(item_key) != m_callbacks.end()) {
            std::ostringstream message;
            message << "IFactory::createItem() -> Error. Already registered item key '" << item_key
                    << "'";
            throw Exceptions::RuntimeErrorException(message.str());
        }
        if (itemDescription != "")
            m_descriptions.insert(make_pair(item_key, itemDescription));
        return m_callbacks.insert(make_pair(item_key, CreateFn)).second;
    }

    ~IFactory() {}

    //! Returns number of registered objects
    size_t getNumberOfRegistered() const { return m_callbacks.size(); }

    const_iterator begin() const { return m_descriptions.begin(); }
    const_iterator end() const { return m_descriptions.end(); }

protected:
    CallbackMap_t m_callbacks; //!< map of correspondence of objectsId and creation functions
    DescriptionMap_t m_descriptions; //!< map of correspondence of objectsId and description
};

template <class T> T* create_new() { return new T(); }

#endif // IFACTORY_H
