// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/ISampleIteratorStrategy.cpp
//! @brief     Implements strategies for the class SampleTreeIterator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ISampleIteratorStrategy.h"
#include "Exceptions.h"
#include "SampleTreeIterator.h"

SampleIteratorPreorderStrategy::SampleIteratorPreorderStrategy() {}

SampleIteratorPreorderStrategy* SampleIteratorPreorderStrategy::clone() const
{
    return new SampleIteratorPreorderStrategy();
}

SampleIteratorPreorderStrategy::~SampleIteratorPreorderStrategy() {}

IteratorMemento SampleIteratorPreorderStrategy::first(const ISample* p_root)
{
    IteratorMemento iterator_stack;
    iterator_stack.push_state(IteratorState(p_root));
    return iterator_stack;
}

void SampleIteratorPreorderStrategy::next(IteratorMemento& iterator_stack) const
{
    const ISample* p_sample = iterator_stack.getCurrent();
    if (!p_sample) {
        throw Exceptions::NullPointerException("CompositeIteratorPreorderStrategy::next(): "
                                               "Error! Null object in the tree of objects");
    }
    std::vector<const ISample*> children = p_sample->getChildren();
    if (children.size() > 0) {
        iterator_stack.push_state(IteratorState(children));
        return;
    }
    iterator_stack.next();
    while (!iterator_stack.empty() && iterator_stack.get_state().isEnd()) {
        iterator_stack.pop_state();
        if (!iterator_stack.empty())
            iterator_stack.next();
    }
}

bool SampleIteratorPreorderStrategy::isDone(IteratorMemento& iterator_stack) const
{
    return iterator_stack.empty();
}


SampleIteratorPostorderStrategy::SampleIteratorPostorderStrategy() {}

SampleIteratorPostorderStrategy* SampleIteratorPostorderStrategy::clone() const
{
    return new SampleIteratorPostorderStrategy();
}

SampleIteratorPostorderStrategy::~SampleIteratorPostorderStrategy() {}

IteratorMemento SampleIteratorPostorderStrategy::first(const ISample* p_root)
{
    IteratorMemento iterator_stack;
    iterator_stack.push_state(IteratorState(p_root));
    std::vector<const ISample*> children = p_root->getChildren();
    while (children.size() > 0) {
        iterator_stack.push_state(IteratorState(children));
        children = iterator_stack.getCurrent()->getChildren();
    }
    return iterator_stack;
}

void SampleIteratorPostorderStrategy::next(IteratorMemento& iterator_stack) const
{
    iterator_stack.next();
    if (iterator_stack.get_state().isEnd()) {
        iterator_stack.pop_state();
        return;
    }
    std::vector<const ISample*> children = iterator_stack.getCurrent()->getChildren();
    while (children.size() > 0) {
        iterator_stack.push_state(IteratorState(children));
        children = iterator_stack.getCurrent()->getChildren();
    }
}

bool SampleIteratorPostorderStrategy::isDone(IteratorMemento& iterator_stack) const
{
    return iterator_stack.empty();
}
