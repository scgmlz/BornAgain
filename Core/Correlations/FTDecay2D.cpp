// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Correlations/FTDecay2D.cpp
//! @brief     Implements class FTDistribution2DCauchy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Correlations/FTDecay2D.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Tools/MathFunctions.h"
#include <algorithm>

// ************************************************************************** //
// interface IIFTDecayFunction1D
// ************************************************************************** //

IFTDecayFunction2D::IFTDecayFunction2D(const NodeMeta& meta, const std::vector<double>& PValues)
    : INode(nodeMetaUnion({{"DecayLengthX", "nm", "Half-width along x axis", 0, INF, 1.},
                           {"DecayLengthY", "nm", "Half-width along y axis", 0, INF, 1.},
                           {"Gamma", "rad", "orientation with respect to the first lattice vector",
                            -M_PI_2, +M_PI_2, 0}},
                          meta),
            PValues),
      m_decay_length_x(m_P[0]), m_decay_length_y(m_P[1]), m_gamma(m_P[2])
{
}

//! Calculates bounding values of reciprocal lattice coordinates that contain the centered
//! rectangle with a corner defined by qX and qY
std::pair<double, double>
IFTDecayFunction2D::boundingReciprocalLatticeCoordinates(double qX, double qY, double a, double b,
                                                         double alpha) const
{
    auto q_bounds_1 = transformToRecLatticeCoordinates(qX, qY, a, b, alpha);
    auto q_bounds_2 = transformToRecLatticeCoordinates(qX, -qY, a, b, alpha);
    double qa_max = std::max(std::abs(q_bounds_1.first), std::abs(q_bounds_2.first));
    double qb_max = std::max(std::abs(q_bounds_1.second), std::abs(q_bounds_2.second));
    return {qa_max, qb_max};
}

std::pair<double, double> IFTDecayFunction2D::transformToRecLatticeCoordinates(double qX, double qY,
                                                                               double a, double b,
                                                                               double alpha) const
{
    double qa = (a * qX * std::cos(m_gamma) - a * qY * std::sin(m_gamma)) / M_TWOPI;
    double qb = (b * qX * std::cos(alpha - m_gamma) + b * qY * std::sin(alpha - m_gamma)) / M_TWOPI;
    return {qa, qb};
}

// ************************************************************************** //
// class FTDecayFunction2DCauchy
// ************************************************************************** //

FTDecayFunction2DCauchy::FTDecayFunction2DCauchy(const std::vector<double> P)
    : IFTDecayFunction2D({"FTDecayFunction2DCauchy", "class_tooltip", {}}, P)
{
}

FTDecayFunction2DCauchy::FTDecayFunction2DCauchy(double decay_length_x, double decay_length_y,
                                                 double gamma)
    : FTDecayFunction2DCauchy(std::vector<double>{decay_length_x, decay_length_y, gamma})
{
}

FTDecayFunction2DCauchy* FTDecayFunction2DCauchy::clone() const
{
    return new FTDecayFunction2DCauchy(m_decay_length_x, m_decay_length_y, m_gamma);
}

double FTDecayFunction2DCauchy::evaluate(double qx, double qy) const
{
    double sum_sq = qx * qx * m_decay_length_x * m_decay_length_x
                    + qy * qy * m_decay_length_y * m_decay_length_y;
    return M_TWOPI * m_decay_length_x * m_decay_length_y * std::pow(1.0 + sum_sq, -1.5);
}

// ************************************************************************** //
// class FTDecayFunction2DGauss
// ************************************************************************** //

FTDecayFunction2DGauss::FTDecayFunction2DGauss(const std::vector<double> P)
    : IFTDecayFunction2D({"FTDecayFunction2DGauss", "class_tooltip", {}}, P)
{
}

FTDecayFunction2DGauss::FTDecayFunction2DGauss(double decay_length_x, double decay_length_y,
                                               double gamma)
    : FTDecayFunction2DGauss(std::vector<double>{decay_length_x, decay_length_y, gamma})
{
}

FTDecayFunction2DGauss* FTDecayFunction2DGauss::clone() const
{
    return new FTDecayFunction2DGauss(m_decay_length_x, m_decay_length_y, m_gamma);
}

double FTDecayFunction2DGauss::evaluate(double qx, double qy) const
{
    double sum_sq = qx * qx * m_decay_length_x * m_decay_length_x
                    + qy * qy * m_decay_length_y * m_decay_length_y;
    return M_TWOPI * m_decay_length_x * m_decay_length_y * std::exp(-sum_sq / 2.0);
}

// ************************************************************************** //
// class FTDecayFunction2DVoigt
// ************************************************************************** //

//! Constructor of two-dimensional pseudo-Voigt decay function in reciprocal space.
//! @param decay_length_x: the decay length in nanometers along x-axis of the distribution
//! @param decay_length_y: the decay length in nanometers along y-axis of the distribution
//! @param eta: parameter [0,1] to balance between Cauchy (eta=0.0) and Gauss (eta=1.0)
//! @param gamma: distribution orientation with respect to the first lattice vector in radians

FTDecayFunction2DVoigt::FTDecayFunction2DVoigt(const std::vector<double> P)
    : IFTDecayFunction2D(
        {"FTDecayFunction2DVoigt", "class_tooltip", {{"Eta", "", "para_tooltip", -INF, +INF, 0}}},
        P),
      m_eta(m_P[0])
{
}

FTDecayFunction2DVoigt::FTDecayFunction2DVoigt(double decay_length_x, double decay_length_y,
                                               double gamma, double eta)
    : FTDecayFunction2DVoigt(std::vector<double>{decay_length_x, decay_length_y, gamma, eta})
{
}

FTDecayFunction2DVoigt* FTDecayFunction2DVoigt::clone() const
{
    return new FTDecayFunction2DVoigt(m_decay_length_x, m_decay_length_y, m_eta, m_gamma);
}

double FTDecayFunction2DVoigt::evaluate(double qx, double qy) const
{
    double sum_sq = qx * qx * m_decay_length_x * m_decay_length_x
                    + qy * qy * m_decay_length_y * m_decay_length_y;
    return M_TWOPI * m_decay_length_x * m_decay_length_y
           * (m_eta * std::exp(-sum_sq / 2.0) + (1.0 - m_eta) * std::pow(1.0 + sum_sq, -1.5));
}
