//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Term/SpecularComputationTerm.h
//! @brief     Defines classes SpecularComputationTerm, SpecularScalarTerm, SpecularMatrixTerm
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
#ifndef BORNAGAIN_CORE_TERM_SPECULARCOMPUTATIONTERM_H
#define BORNAGAIN_CORE_TERM_SPECULARCOMPUTATIONTERM_H

#include "Sample/Specular/ISpecularStrategy.h"
#include <memory>
#include <vector>

class DelayedProgressCounter;
class MatrixRTCoefficients_v2;
class ProgressHandler;
class SpecularSimulationElement;
class Slice;

//! Computes the specular scattering.
//! Used by SpecularComputation.
//!
//! Abstract base class of SpecularScalarTerm, SpecularMatrixTerm
//!
//! @ingroup algorithms_internal

class SpecularComputationTerm {
public:
    SpecularComputationTerm(std::unique_ptr<ISpecularStrategy> strategy);
    virtual ~SpecularComputationTerm();

    SpecularComputationTerm(const SpecularComputationTerm& other) = delete;
    SpecularComputationTerm& operator=(const SpecularComputationTerm& other) = delete;

    void setProgressHandler(ProgressHandler* p_progress);
    void computeIntensity(SpecularSimulationElement& elem, const std::vector<Slice>& slices) const;

protected:
    virtual void eval(SpecularSimulationElement& elem, const std::vector<Slice>& slices) const = 0;

    std::unique_ptr<ISpecularStrategy> m_Strategy;

private:
    std::unique_ptr<DelayedProgressCounter> m_progress_counter;
};

//! Computes the specular scattering for a scalar sample
//! Used by SpecularComputation.
//! @ingroup algorithms_internal

class SpecularScalarTerm : public SpecularComputationTerm {
public:
    SpecularScalarTerm(std::unique_ptr<ISpecularStrategy> strategy);

private:
    ~SpecularScalarTerm() override;

    void eval(SpecularSimulationElement& elem, const std::vector<Slice>& slices) const override;
};

//! Computes the specular scattering for a magnetic sample
//! Used by SpecularComputation.
//! @ingroup algorithms_internal

class SpecularMatrixTerm : public SpecularComputationTerm {
public:
    SpecularMatrixTerm(std::unique_ptr<ISpecularStrategy> strategy);

private:
    ~SpecularMatrixTerm() override;

    void eval(SpecularSimulationElement& elem, const std::vector<Slice>& slices) const override;
};

#endif // BORNAGAIN_CORE_TERM_SPECULARCOMPUTATIONTERM_H
#endif // USER_API
