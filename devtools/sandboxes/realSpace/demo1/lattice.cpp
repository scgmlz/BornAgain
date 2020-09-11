// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      dev-tools/sandboxes/realSpace/demo1/lattice.cpp
//! @brief     Implements Lattice class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "lattice.h"
#include <QTime>
#include <QtGlobal>
#include <qmath.h>

Lattice::Lattice() : n(0) {}

Lattice::Lattice(uint n_, uint nn) : super(nn), n(n_) {}

uint Lattice::index(int ix, int iy)
{
    int nx = n, ny = n;
    Q_ASSERT(-nx <= ix && ix <= +nx);
    Q_ASSERT(-ny <= iy && iy <= +ny);
    uint i = (2 * nx + 1) * (iy + ny) + (ix + nx);
    Q_ASSERT(static_cast<int>(i) < count());
    return i;
}

int Lattice::ix(uint i)
{
    int nr = 2 * n + 1;
    return i % nr - n;
}

int Lattice::iy(uint i)
{
    int nr = 2 * n + 1;
    return i / nr - n;
}

Lattice squareLattice(uint n, float sigma)
{
    using RealSpace::Vector3D;

    auto rand01 = [&]() -> float {
        static bool seeded = false;
        if (!seeded) {
            seeded = true;
            qsrand(QTime::currentTime().msec());
        }
        return qrand() / float(RAND_MAX);
    };

    auto place00 = [&]() -> Vector3D {
        // https://www.taygeta.com/random/gaussian.html
        float x01, y01, w;

        do {
            x01 = 2.f * rand01() - 1.f;
            y01 = 2.f * rand01() - 1.f;
            w = x01 * x01 + y01 * y01;
        } while (w >= 1.f);

        w = sqrt(-2.f * qLn(w) / w);
        return Vector3D(x01 * w * sigma, y01 * w * sigma, 0.01);
    };

    auto placeHere = [&](const Vector3D& here) -> Vector3D { return place00() + here; };

    auto placeXY = [&](float x, float y) -> Vector3D { return placeHere(Vector3D(x, y, 0)); };

    uint nn = (2 * n + 1) * (2 * n + 1); // total number

    auto mesh = Lattice(n, nn);

    auto get = [&](int ix, int iy) -> const Vector3D& { return mesh.at(mesh.index(ix, iy)); };
    (void)get;

    auto isMade = [&](int ix, int iy) -> bool {
        return Vector3D::_0 != mesh.at(mesh.index(ix, iy));
    };

    auto put = [&](int ix, int iy) {
        if (!isMade(ix, iy))
            mesh[mesh.index(ix, iy)] = placeXY(ix, iy);
    };

    auto growBy1Quadrant = [&](uint n, int mx, int my) {
        Q_ASSERT(n > 0);
        Q_ASSERT(1 == qAbs(mx) && 1 == qAbs(my));

        put(0 * mx, n * my);
        put(n * mx, 0 * my);

        for (uint i = 1; i < n; ++i) {
            put(i * mx, n * my);
            put(n * mx, i * my);
        }

        put(n * mx, n * my);
    };

    auto growBy1 = [&](uint n) {
        Q_ASSERT(n > 0);
        growBy1Quadrant(n, +1, +1);
        growBy1Quadrant(n, +1, -1);
        growBy1Quadrant(n, -1, +1);
        growBy1Quadrant(n, -1, -1);
    };

    auto growTo = [&](uint n) {
        for (uint i = 1; i <= n; ++i)
            growBy1(i);
    };

    growTo(n);
    return mesh;
}
