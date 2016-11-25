// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/IFitStrategy.cpp
//! @brief     Implements classes IFitStrategy and FitStrategyDefault
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IFitStrategy.h"
#include "FitSuiteImpl.h"
#include <stdexcept>

IFitStrategy::IFitStrategy(const std::string& name) : INamed(name), m_kernel(nullptr) {}

void IFitStrategy::init(FitSuiteImpl* fit_suite) { m_kernel = fit_suite; }

std::string IFitStrategy::toString() const { return getName(); }

IFitStrategy::IFitStrategy(const IFitStrategy& other) : INamed(other) { m_kernel = other.m_kernel; }

// ----------------------------------------------------------------------------

FitStrategyDefault::FitStrategyDefault() : IFitStrategy("DefaultFitStrategy") {}

FitStrategyDefault* FitStrategyDefault::clone() const { return new FitStrategyDefault(*this); }

void FitStrategyDefault::execute()
{
    if (!m_kernel)
        throw std::runtime_error("FitStrategyDefault::execute() -> FitSuite doesn't exists");

    m_kernel->minimize();
}

FitStrategyDefault::FitStrategyDefault(const FitStrategyDefault& other) : IFitStrategy(other) {}
