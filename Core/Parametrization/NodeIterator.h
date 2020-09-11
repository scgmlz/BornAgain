// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/NodeIterator.h
//! @brief     Defines classes IteratorState, IteratorMemento and NodeIterator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARAMETRIZATION_NODEITERATOR_H
#define BORNAGAIN_CORE_PARAMETRIZATION_NODEITERATOR_H

#include "Core/Parametrization/INode.h"
#include <ostream>
#include <stack>
#include <vector>

//! Holds state of iterator at single level for SampleTreeIterator.
//! @ingroup samples_internal

class IteratorState
{
public:
    IteratorState(const INode* single_element);
    IteratorState(std::vector<const INode*> samples);

    virtual ~IteratorState() {}

    const INode* getCurrent() const { return m_samples[m_position]; }
    bool isEnd() const { return m_position >= m_samples.size(); }
    void next() { ++m_position; }

    friend std::ostream& operator<<(std::ostream& output_stream,
                                    IteratorState const& iterator_state)
    {
        return output_stream << "memento state " << iterator_state.m_position << " "
                             << iterator_state.m_samples.size();
    }

private:
    std::vector<const INode*> m_samples;
    size_t m_position;

    IteratorState();
};

//! Holds all iterator states encountered for SampleTreeIterator.
//! @ingroup samples_internal

class IteratorMemento
{
public:
    IteratorMemento() {}
    virtual ~IteratorMemento() {}

    void push_state(const IteratorState& state) { m_state_stack.push(state); }
    void pop_state() { m_state_stack.pop(); }
    IteratorState& get_state() { return m_state_stack.top(); }
    bool empty() const { return m_state_stack.empty(); }
    void reset()
    {
        while (!m_state_stack.empty())
            m_state_stack.pop();
    }
    const INode* getCurrent() { return m_state_stack.top().getCurrent(); }
    void next() { m_state_stack.top().next(); }
    size_t size() const { return m_state_stack.size(); }

protected:
    std::stack<IteratorState> m_state_stack;
};

//! Iterator through INode tree of objects.
//!
//! Usage example:
//!    SampleTreeIterator<Strategy> it(&sample);
//!    it.first();
//!    while( !it.is_done() ) {
//!        INode *p_sample = it.get_current();
//!        it.next();
//!     }
//! @ingroup samples_internal

template <class Strategy> class BA_CORE_API_ NodeIterator
{
public:
    NodeIterator(const INode* root);
    virtual ~NodeIterator() {}

    void first();
    void next();
    const INode* getCurrent();
    bool isDone() const;
    int depth() const;

protected:
    Strategy m_strategy;
    IteratorMemento m_memento_itor;
    const INode* mp_root;
};

template <class Strategy>
inline NodeIterator<Strategy>::NodeIterator(const INode* root) : mp_root(root)
{
}

template <class Strategy> inline void NodeIterator<Strategy>::first()
{
    m_memento_itor = m_strategy.first(mp_root);
}

template <class Strategy> inline void NodeIterator<Strategy>::next()
{
    m_strategy.next(m_memento_itor);
}

template <class Strategy> inline const INode* NodeIterator<Strategy>::getCurrent()
{
    return m_memento_itor.getCurrent();
}

template <class Strategy> inline bool NodeIterator<Strategy>::isDone() const
{
    return m_memento_itor.size() == 0;
}

template <class Strategy> inline int NodeIterator<Strategy>::depth() const
{
    return static_cast<int>(m_memento_itor.size());
}

#endif // BORNAGAIN_CORE_PARAMETRIZATION_NODEITERATOR_H
