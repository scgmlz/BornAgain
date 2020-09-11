// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Correlations/FTDistributions1D.cpp
//! @brief     Implements interface class IFTDistribution2D and children thereof.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Correlations/FTDistributions1D.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Tools/MathFunctions.h"
#include <limits>

namespace
{
const double CosineDistributionFactor = 1.0 / 3.0 - 2.0 / M_PI / M_PI;
}

// ************************************************************************** //
// interface IFTDistribution1D
// ************************************************************************** //

IFTDistribution1D::IFTDistribution1D(const NodeMeta& meta, const std::vector<double>& PValues)
    : INode(nodeMetaUnion({{"Omega", "nm", "Half-width", 0, INF, 1.}}, meta), PValues),
      m_omega(m_P[0])
{
}

// ************************************************************************** //
// class FTDistribution1DCauchy
// ************************************************************************** //

FTDistribution1DCauchy::FTDistribution1DCauchy(const std::vector<double> P)
    : IFTDistribution1D({"FTDistribution1DCauchy", "class_tooltip", {}}, P)
{
}

FTDistribution1DCauchy::FTDistribution1DCauchy(double omega)
    : FTDistribution1DCauchy(std::vector<double>{omega})
{
}

FTDistribution1DCauchy* FTDistribution1DCauchy::clone() const
{
    return new FTDistribution1DCauchy(m_omega);
}

double FTDistribution1DCauchy::evaluate(double q) const
{
    double sum_sq = q * q * m_omega * m_omega;
    return 1.0 / (1.0 + sum_sq);
}

double FTDistribution1DCauchy::qSecondDerivative() const
{
    return 2.0 * m_omega * m_omega;
}

std::unique_ptr<IDistribution1DSampler> FTDistribution1DCauchy::createSampler() const
{
    return std::make_unique<Distribution1DCauchySampler>(1 / m_omega);
}

// ************************************************************************** //
// class FTDistribution1DGauss
// ************************************************************************** //

FTDistribution1DGauss::FTDistribution1DGauss(const std::vector<double> P)
    : IFTDistribution1D({"FTDistribution1DGauss", "class_tooltip", {}}, P)
{
}

FTDistribution1DGauss::FTDistribution1DGauss(double omega)
    : FTDistribution1DGauss(std::vector<double>{omega})
{
}

FTDistribution1DGauss* FTDistribution1DGauss::clone() const
{
    return new FTDistribution1DGauss(m_omega);
}

double FTDistribution1DGauss::evaluate(double q) const
{
    double sum_sq = q * q * m_omega * m_omega;
    return std::exp(-sum_sq / 2.0);
}

double FTDistribution1DGauss::qSecondDerivative() const
{
    return m_omega * m_omega;
}

std::unique_ptr<IDistribution1DSampler> FTDistribution1DGauss::createSampler() const
{
    return std::make_unique<Distribution1DGaussSampler>(0.0, m_omega);
}

// ************************************************************************** //
// class FTDistribution1DGate
// ************************************************************************** //

FTDistribution1DGate::FTDistribution1DGate(const std::vector<double> P)
    : IFTDistribution1D({"FTDistribution1DGate", "class_tooltip", {}}, P)
{
}

FTDistribution1DGate::FTDistribution1DGate(double omega)
    : FTDistribution1DGate(std::vector<double>{omega})
{
}

FTDistribution1DGate* FTDistribution1DGate::clone() const
{
    return new FTDistribution1DGate(m_omega);
}

double FTDistribution1DGate::evaluate(double q) const
{
    return MathFunctions::sinc(q * m_omega);
}

double FTDistribution1DGate::qSecondDerivative() const
{
    return m_omega * m_omega / 3.0;
}

std::unique_ptr<IDistribution1DSampler> FTDistribution1DGate::createSampler() const
{
    return std::make_unique<Distribution1DGateSampler>(-m_omega, m_omega);
}

// ************************************************************************** //
// class FTDistribution1DTriangle
// ************************************************************************** //

FTDistribution1DTriangle::FTDistribution1DTriangle(const std::vector<double> P)
    : IFTDistribution1D({"FTDistribution1DTriangle", "class_tooltip", {}}, P)
{
}

FTDistribution1DTriangle::FTDistribution1DTriangle(double omega)
    : FTDistribution1DTriangle(std::vector<double>{omega})
{
}

FTDistribution1DTriangle* FTDistribution1DTriangle::clone() const
{
    return new FTDistribution1DTriangle(m_omega);
}

double FTDistribution1DTriangle::evaluate(double q) const
{
    double sincqw2 = MathFunctions::sinc(q * m_omega / 2.0);
    return sincqw2 * sincqw2;
}

double FTDistribution1DTriangle::qSecondDerivative() const
{
    return m_omega * m_omega / 6.0;
}

std::unique_ptr<IDistribution1DSampler> FTDistribution1DTriangle::createSampler() const
{
    return std::make_unique<Distribution1DTriangleSampler>(m_omega);
}

// ************************************************************************** //
// class FTDistribution1DCosine
// ************************************************************************** //

FTDistribution1DCosine::FTDistribution1DCosine(const std::vector<double> P)
    : IFTDistribution1D({"FTDistribution1DCosine", "class_tooltip", {}}, P)
{
}

FTDistribution1DCosine::FTDistribution1DCosine(double omega)
    : FTDistribution1DCosine(std::vector<double>{omega})
{
}

FTDistribution1DCosine* FTDistribution1DCosine::clone() const
{
    return new FTDistribution1DCosine(m_omega);
}

double FTDistribution1DCosine::evaluate(double q) const
{
    double qw = std::abs(q * m_omega);
    if (std::abs(1.0 - qw * qw / M_PI / M_PI) < std::numeric_limits<double>::epsilon())
        return 0.5;
    return MathFunctions::sinc(qw) / (1.0 - qw * qw / M_PI / M_PI);
}

double FTDistribution1DCosine::qSecondDerivative() const
{
    return CosineDistributionFactor * m_omega * m_omega;
}

std::unique_ptr<IDistribution1DSampler> FTDistribution1DCosine::createSampler() const
{
    return std::make_unique<Distribution1DCosineSampler>(m_omega);
}

// ************************************************************************** //
// class FTDistribution1DVoigt
// ************************************************************************** //

FTDistribution1DVoigt::FTDistribution1DVoigt(const std::vector<double> P)
    : IFTDistribution1D(
        {"FTDistribution1DVoigt", "class_tooltip", {{"Eta", "", "para_tooltip", -INF, +INF, 0}}},
        P),
      m_eta(m_P[1])
{
}

FTDistribution1DVoigt::FTDistribution1DVoigt(double omega, double eta)
    : FTDistribution1DVoigt(std::vector<double>{omega, eta})
{
}

FTDistribution1DVoigt* FTDistribution1DVoigt::clone() const
{
    return new FTDistribution1DVoigt(m_omega, m_eta);
}

double FTDistribution1DVoigt::evaluate(double q) const
{
    double sum_sq = q * q * m_omega * m_omega;
    return m_eta * std::exp(-sum_sq / 2.0) + (1.0 - m_eta) * 1.0 / (1.0 + sum_sq);
}

double FTDistribution1DVoigt::qSecondDerivative() const
{
    return (2.0 - m_eta) * m_omega * m_omega;
}

std::unique_ptr<IDistribution1DSampler> FTDistribution1DVoigt::createSampler() const
{
    // TODO Need to implement 1D Voigt

    std::ostringstream ostr;
    ostr << "FTDistribution1DVoigt::createSampler() -> Error in class initialization";
    ostr << "\n\n Has not been implemented yet...stay tuned!";
    throw Exceptions::ClassInitializationException(ostr.str());
}
