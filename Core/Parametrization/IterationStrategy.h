// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/IterationStrategy.h
//! @brief     Defines class IterationStrategy and children.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ITERATIONSTRATEGY_H
#define ITERATIONSTRATEGY_H

#include "ISample.h"

class IteratorMemento;

//! Abstract base class of PreorderStrategy and PostorderStrategy, for use in INodeVisitor.
class BA_CORE_API_ IterationStrategy
{
public:
    virtual ~IterationStrategy() {}

    virtual IterationStrategy* clone() const = 0;

    virtual IteratorMemento first(const INode* p_root) = 0;
    virtual void next(IteratorMemento& iterator_stack) const = 0;
    virtual bool isDone(IteratorMemento& iterator_stack) const = 0;
};

class BA_CORE_API_ PreorderStrategy : public IterationStrategy
{
public:
    PreorderStrategy();

    virtual PreorderStrategy* clone() const;

    virtual ~PreorderStrategy();
    virtual IteratorMemento first(const INode* p_root);
    virtual void next(IteratorMemento& iterator_stack) const;
    virtual bool isDone(IteratorMemento& iterator_stack) const;
};

class BA_CORE_API_ PostorderStrategy : public IterationStrategy
{
public:
    PostorderStrategy();

    virtual PostorderStrategy* clone() const;

    virtual ~PostorderStrategy();
    virtual IteratorMemento first(const INode* p_root);
    virtual void next(IteratorMemento& iterator_stack) const;
    virtual bool isDone(IteratorMemento& iterator_stack) const;
};

#endif // ITERATIONSTRATEGY_H
