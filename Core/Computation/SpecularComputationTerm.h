// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SpecularComputationTerm.h
//! @brief     Defines functor SpecularComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARCOMPUTATIONTERM_H_
#define SPECULARCOMPUTATIONTERM_H_

#include "SpecularScalarStrategy.h"
#include "SpecularMagneticStrategy.h"

#include <memory>
#include <vector>

class DelayedProgressCounter;
class MatrixRTCoefficients_v2;
class ProgressHandler;
class SpecularSimulationElement;
class Slice;

//! Computes the specular scattering.
//! Used by SpecularComputation.
//! @ingroup algorithms_internal

class SpecularComputationTerm
{
public:
    SpecularComputationTerm();
    virtual ~SpecularComputationTerm();

    void setProgressHandler(ProgressHandler* p_progress);
    void compute(SpecularSimulationElement& elem, const std::vector<Slice>& slices) const;

protected:
    virtual void eval(SpecularSimulationElement& elem, const std::vector<Slice>& slices) const = 0;

private:
    std::unique_ptr<DelayedProgressCounter> mP_progress_counter;
};

class SpecularScalarTerm : public SpecularComputationTerm
{
public:
    SpecularScalarTerm(SpecularScalarStrategy* strategy);
private:
    ~SpecularScalarTerm() override;
protected:
    void eval(SpecularSimulationElement& elem, const std::vector<Slice>& slices) const override;

    SpecularScalarStrategy* m_Strategy;
};

class SpecularMatrixTerm : public SpecularComputationTerm
{
public:
    SpecularMatrixTerm(SpecularMagneticStrategy* strategy);
private:
    ~SpecularMatrixTerm() override;
protected:
    void eval(SpecularSimulationElement& elem, const std::vector<Slice>& slices) const override;
    double intensity(const SpecularSimulationElement& elem,
                     const MatrixRTCoefficients_v2& coeff) const;

    SpecularMagneticStrategy* m_Strategy;
};

#endif /* SPECULARCOMPUTATIONTERM_H_ */
