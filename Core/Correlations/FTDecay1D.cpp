// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Correlations/FTDecay1D.cpp
//! @brief     Implements class FTDistribution2DCauchy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Correlations/FTDecay1D.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Tools/MathFunctions.h"
#include <algorithm>

// ************************************************************************** //
// interface IIFTDecayFunction1D
// ************************************************************************** //

IFTDecayFunction1D::IFTDecayFunction1D(const NodeMeta& meta, const std::vector<double>& PValues)
    : INode(nodeMetaUnion({{"DecayLength", "nm", "half width", 0, INF, 1.}}, meta), PValues),
      m_decay_length(m_P[0])
{
}

// ************************************************************************** //
// class FTDecayFunction1DCauchy
// ************************************************************************** //

FTDecayFunction1DCauchy::FTDecayFunction1DCauchy(const std::vector<double> P)
    : IFTDecayFunction1D({"FTDecayFunction1DCauchy", "class_tooltip", {}}, P)
{
}

FTDecayFunction1DCauchy::FTDecayFunction1DCauchy(double decay_length)
    : FTDecayFunction1DCauchy(std::vector<double>{decay_length})
{
}

FTDecayFunction1DCauchy* FTDecayFunction1DCauchy::clone() const
{
    return new FTDecayFunction1DCauchy(m_decay_length);
}

double FTDecayFunction1DCauchy::evaluate(double q) const
{
    double sum_sq = q * q * m_decay_length * m_decay_length;
    return m_decay_length * 2.0 / (1.0 + sum_sq);
}

// ************************************************************************** //
// class FTDecayFunction1DGauss
// ************************************************************************** //

FTDecayFunction1DGauss::FTDecayFunction1DGauss(const std::vector<double> P)
    : IFTDecayFunction1D({"FTDecayFunction1DGauss", "class_tooltip", {}}, P)
{
}

FTDecayFunction1DGauss::FTDecayFunction1DGauss(double decay_length)
    : FTDecayFunction1DGauss(std::vector<double>{decay_length})
{
}

FTDecayFunction1DGauss* FTDecayFunction1DGauss::clone() const
{
    return new FTDecayFunction1DGauss(m_decay_length);
}

double FTDecayFunction1DGauss::evaluate(double q) const
{
    double sum_sq = q * q * m_decay_length * m_decay_length;
    return m_decay_length * std::sqrt(M_TWOPI) * std::exp(-sum_sq / 2.0);
}

// ************************************************************************** //
// class FTDecayFunction1DTriangle
// ************************************************************************** //

FTDecayFunction1DTriangle::FTDecayFunction1DTriangle(const std::vector<double> P)
    : IFTDecayFunction1D({"FTDecayFunction1DTriangle", "class_tooltip", {}}, P)
{
}

FTDecayFunction1DTriangle::FTDecayFunction1DTriangle(double decay_length)
    : FTDecayFunction1DTriangle(std::vector<double>{decay_length})
{
}

FTDecayFunction1DTriangle* FTDecayFunction1DTriangle::clone() const
{
    return new FTDecayFunction1DTriangle(m_decay_length);
}

double FTDecayFunction1DTriangle::evaluate(double q) const
{
    double sincqw2 = MathFunctions::sinc(q * m_decay_length / 2.0);
    return m_decay_length * sincqw2 * sincqw2;
}

// ************************************************************************** //
// class FTDecayFunction1DVoigt
// ************************************************************************** //

FTDecayFunction1DVoigt::FTDecayFunction1DVoigt(const std::vector<double> P)
    : IFTDecayFunction1D(
        {"FTDecayFunction1DVoigt", "class_tooltip", {{"Eta", "", "para_tooltip", -INF, +INF, 0}}},
        P),
      m_eta(m_P[0])
{
}

FTDecayFunction1DVoigt::FTDecayFunction1DVoigt(double decay_length, double eta)
    : FTDecayFunction1DVoigt(std::vector<double>{decay_length, eta})
{
}

FTDecayFunction1DVoigt* FTDecayFunction1DVoigt::clone() const
{
    return new FTDecayFunction1DVoigt(m_decay_length, m_eta);
}

double FTDecayFunction1DVoigt::evaluate(double q) const
{
    double sum_sq = q * q * m_decay_length * m_decay_length;
    return m_eta * m_decay_length * std::sqrt(M_TWOPI) * std::exp(-sum_sq / 2.0)
           + (1.0 - m_eta) * m_decay_length * 2.0 / (1.0 + sum_sq);
}
