// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/ICompositeSample.h
//! @brief     Defines interface class ICompositeSample.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICOMPOSITESAMPLE_H
#define ICOMPOSITESAMPLE_H

#include "ISample.h"

//! Pure virtual base class for tree-like composite samples.
//!
//! Inherited by IAbstractParticle, IClusteredParticle, ILayout, ILayer, IMultiLayer.
//!
//! @ingroup samples_internal

class BA_CORE_API_ ICompositeSample : public ISample
{
public:
    ICompositeSample() {}
    virtual ~ICompositeSample();

    virtual ICompositeSample* clone() const = 0;

    virtual void accept(ISampleVisitor* visitor) const = 0;

    //! Registers child in the container.
    void registerChild(ISample* sample);

    //! Removes registered child from the container
    void deregisterChild(ISample* sample);

    //! Returns child pointer by index (with range checking)
    ISample* operator[](size_t index);

    //! Returns child pointer by index (with range checking)
    const ISample* operator[](size_t index) const;

    //! Returns a vector of children (const).
    std::vector<const ISample*> getChildren() const final;

    //! Returns number of children.
    size_t size() const final { return m_samples.size(); }

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    virtual std::string addParametersToExternalPool(
        const std::string& path, ParameterPool* external_pool, int copy_number = -1) const;

private:
    //! Check child index
    bool childIndexInRange(size_t index) const { return index < m_samples.size(); }

    //! List of registered children.
    std::vector<ISample*> m_samples;
};

#endif // ICOMPOSITESAMPLE_H
