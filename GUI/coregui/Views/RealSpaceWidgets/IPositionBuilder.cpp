// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/IPositionBuilder.cpp
//! @brief     Implements subclasses of IPositionBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/RealSpaceWidgets/IPositionBuilder.h"
#include "Core/Lattice/Lattice2D.h"
#include "Core/includeIncludes/InterferenceFunctions.h"
#include "GUI/coregui/Views/RealSpaceWidgets/RealSpace2DParacrystalUtils.h"
#include <cmath>
#include <random>

namespace
{
std::vector<std::vector<double>> Generate2DLatticePoints(double l1, double l2, double alpha,
                                                         double xi, unsigned n1, unsigned n2);
}

IPositionBuilder::~IPositionBuilder() = default;

std::vector<std::vector<double>> IPositionBuilder::generatePositions(double layer_size,
                                                                     double density) const
{
    std::vector<std::vector<double>> positions = generatePositionsImpl(layer_size, density);
    double pos_var = positionVariance();
    if (pos_var > 0.0) {
        // random generator and distribution
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::normal_distribution<double> dis(0.0, std::sqrt(pos_var));
        for (auto& position : positions) {
            for (auto& coordinate : position)
                coordinate += dis(gen);
        }
    }
    return positions;
}

DefaultPositionBuilder::DefaultPositionBuilder() = default;

DefaultPositionBuilder::~DefaultPositionBuilder() = default;

std::vector<std::vector<double>> DefaultPositionBuilder::generatePositionsImpl(double, double) const
{
    std::vector<double> origin = {0.0, 0.0};
    return {origin};
}

double DefaultPositionBuilder::positionVariance() const
{
    return 0.0;
}

RandomPositionBuilder::RandomPositionBuilder() = default;

RandomPositionBuilder::~RandomPositionBuilder() = default;

std::vector<std::vector<double>> RandomPositionBuilder::generatePositionsImpl(double layer_size,
                                                                              double density) const
{
    std::vector<std::vector<double>> lattice_positions;
    std::vector<double> position;

    // to compute total number of particles we use the total particle density
    // and multiply by the area of the layer
    int num_particles = static_cast<int>(density * (2 * layer_size) * (2 * layer_size));

    // random generator and distribution
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    for (int i = 1; i <= num_particles; ++i) {
        // generate random x and y coordinates
        position.push_back(dis(gen) * 2 * layer_size - layer_size); // x
        position.push_back(dis(gen) * 2 * layer_size - layer_size); // y

        lattice_positions.push_back(position);
        position.clear();
    }
    return lattice_positions;
}

double RandomPositionBuilder::positionVariance() const
{
    return 0.0; // no need for extra randomness here
}

Lattice1DPositionBuilder::Lattice1DPositionBuilder(const InterferenceFunction1DLattice* p_iff)
    : mP_iff(p_iff->clone())
{
}

Lattice1DPositionBuilder::~Lattice1DPositionBuilder() = default;

std::vector<std::vector<double>> Lattice1DPositionBuilder::generatePositionsImpl(double layer_size,
                                                                                 double) const
{
    const double length = mP_iff->getLength();
    const double xi = mP_iff->getXi();

    // Take the maximum possible integer multiple of the lattice vector required
    // for populating particles correctly within the 3D model's boundaries
    unsigned n1 =
        length == 0.0 ? 2 : static_cast<unsigned>(2.0 * layer_size * std::sqrt(2.0) / length);

    return Generate2DLatticePoints(length, 0.0, 0.0, xi, n1, 1u);
}

double Lattice1DPositionBuilder::positionVariance() const
{
    return mP_iff->positionVariance();
}

Lattice2DPositionBuilder::Lattice2DPositionBuilder(const InterferenceFunction2DLattice* p_iff)
    : mP_iff(p_iff->clone())
{
}

Lattice2DPositionBuilder::~Lattice2DPositionBuilder() = default;

std::vector<std::vector<double>> Lattice2DPositionBuilder::generatePositionsImpl(double layer_size,
                                                                                 double) const
{
    auto& lattice = mP_iff->lattice();
    double l1 = lattice.length1();
    double l2 = lattice.length2();
    double alpha = lattice.latticeAngle();
    double xi = lattice.rotationAngle();

    // Estimate the limits n1 and n2 of the maximum integer multiples of the lattice vectors
    // required for populating particles correctly within the 3D model's boundaries
    unsigned n1, n2;
    double sina = std::abs(std::sin(alpha));
    if (sina <= 1e-4) {
        n1 = l1 == 0.0 ? 2 : static_cast<unsigned>(2.0 * layer_size * std::sqrt(2.0) / l1);
        n2 = l2 == 0.0 ? 2 : static_cast<unsigned>(2.0 * layer_size * std::sqrt(2.0) / l2);
    } else {
        n1 = l1 == 0.0 ? 2 : static_cast<unsigned>(2.0 * layer_size * std::sqrt(2.0) / l1 / sina);
        n2 = l2 == 0.0 ? 2 : static_cast<unsigned>(2.0 * layer_size * std::sqrt(2.0) / l2 / sina);
    }
    return Generate2DLatticePoints(l1, l2, alpha, xi, n1, n2);
}

double Lattice2DPositionBuilder::positionVariance() const
{
    return mP_iff->positionVariance();
}

ParaCrystal2DPositionBuilder::ParaCrystal2DPositionBuilder(
    const InterferenceFunction2DParaCrystal* p_iff)
    : mP_iff(p_iff->clone())
{
}

ParaCrystal2DPositionBuilder::~ParaCrystal2DPositionBuilder() = default;

std::vector<std::vector<double>>
ParaCrystal2DPositionBuilder::generatePositionsImpl(double layer_size, double) const
{
    return RealSpace2DParacrystalUtils::Compute2DParacrystalLatticePositions(mP_iff.get(),
                                                                             layer_size);
}

double ParaCrystal2DPositionBuilder::positionVariance() const
{
    return mP_iff->positionVariance();
}

Finite2DLatticePositionBuilder::Finite2DLatticePositionBuilder(
    const InterferenceFunctionFinite2DLattice* p_iff)
    : mP_iff(p_iff->clone())
{
}

Finite2DLatticePositionBuilder::~Finite2DLatticePositionBuilder() = default;

std::vector<std::vector<double>>
Finite2DLatticePositionBuilder::generatePositionsImpl(double layer_size, double) const
{
    auto& lattice = mP_iff->lattice();
    double l1 = lattice.length1();
    double l2 = lattice.length2();
    double alpha = lattice.latticeAngle();
    double xi = lattice.rotationAngle();

    unsigned n1, n2;
    double sina = std::abs(std::sin(alpha));
    if (sina <= 1e-4) {
        n1 = l1 == 0.0 ? 2 : static_cast<unsigned>(2.0 * layer_size * std::sqrt(2.0) / l1);
        n2 = l2 == 0.0 ? 2 : static_cast<unsigned>(2.0 * layer_size * std::sqrt(2.0) / l2);
    } else {
        n1 = l1 == 0.0 ? 2 : static_cast<unsigned>(2.0 * layer_size * std::sqrt(2.0) / l1 / sina);
        n2 = l2 == 0.0 ? 2 : static_cast<unsigned>(2.0 * layer_size * std::sqrt(2.0) / l2 / sina);
    }
    n1 = std::min(n1, mP_iff->numberUnitCells1());
    n2 = std::min(n2, mP_iff->numberUnitCells2());

    return Generate2DLatticePoints(l1, l2, alpha, xi, n1, n2);
}

double Finite2DLatticePositionBuilder::positionVariance() const
{
    return mP_iff->positionVariance();
}

RadialParacrystalPositionBuilder::RadialParacrystalPositionBuilder(
    const InterferenceFunctionRadialParaCrystal* p_iff)
    : mP_iff(p_iff->clone())
{
}

RadialParacrystalPositionBuilder::~RadialParacrystalPositionBuilder() = default;

std::vector<std::vector<double>>
RadialParacrystalPositionBuilder::generatePositionsImpl(double layer_size, double) const
{
    std::vector<std::vector<double>> lattice_positions;

    double distance = mP_iff->peakDistance();

    // Estimate the limit n of the integer multiple i of the peakDistance required
    // for populating particles correctly within the 3D model's boundaries
    int n = distance <= 0.0 ? 1 : static_cast<int>(layer_size * std::sqrt(2.0) / distance);

    lattice_positions.resize(static_cast<size_t>(2 * n + 1));
    for (auto& it : lattice_positions) {
        it.resize(2);
    }

    lattice_positions[0][0] = 0.0; // x coordinate of reference particle - at the origin
    lattice_positions[0][1] = 0.0; // y coordinate of reference particle - at the origin

    for (int i = 1; i <= n; ++i) {
        // positions of particles located along +x (store at odd index)
        unsigned i_left = static_cast<unsigned>(std::max(0, 2 * i - 3));

        double offset = mP_iff->randomSample();
        lattice_positions[static_cast<size_t>(2 * i - 1)][0] =
            lattice_positions[i_left][0] + distance + offset;
        lattice_positions[static_cast<size_t>(2 * i - 1)][1] = 0.0;

        // positions of particles located along -x (store at even index)
        unsigned i_right = static_cast<unsigned>(2 * (i - 1));

        offset = mP_iff->randomSample();
        lattice_positions[static_cast<size_t>(2 * i)][0] =
            lattice_positions[i_right][0] - distance + offset;
        lattice_positions[static_cast<size_t>(2 * i)][1] = 0.0;
    }
    return lattice_positions;
}

double RadialParacrystalPositionBuilder::positionVariance() const
{
    return mP_iff->positionVariance();
}

namespace
{
std::vector<std::vector<double>> Generate2DLatticePoints(double l1, double l2, double alpha,
                                                         double xi, unsigned n1, unsigned n2)
{
    std::vector<std::vector<double>> lattice_positions;
    std::vector<double> position;

    unsigned nn1 = std::max(1u, n1);
    unsigned nn2 = std::max(1u, n2);
    int n1m = -static_cast<int>((nn1 - 1) / 2);
    int n1M = static_cast<int>(nn1 / 2);
    int n2m = -static_cast<int>((nn2 - 1) / 2);
    int n2M = static_cast<int>(nn2 / 2);

    for (int i = n1m; i <= n1M; ++i) {
        for (int j = n2m; j <= n2M; ++j) {
            // For calculating lattice position vector v, we use: v = i*l1 + j*l2
            // where l1 and l2 are the lattice vectors,
            position.push_back(i * l1 * std::cos(xi)
                               + j * l2 * std::cos(alpha + xi)); // x coordinate
            position.push_back(i * l1 * std::sin(xi)
                               + j * l2 * std::sin(alpha + xi)); // y coordinate

            lattice_positions.push_back(position);
            position.clear();
        }
    }
    return lattice_positions;
}
} // namespace
