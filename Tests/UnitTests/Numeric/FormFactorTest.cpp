#include "Tests/UnitTests/Numeric/FormFactorTest.h"
#include "Tests/GTestWrapper/google_test.h" // tests segfault under Linux/clang-9.0.1 if this include is missing

using ::testing::Combine;
using ::testing::Values;
using ::testing::internal::ParamGenerator;

namespace formFactorTest
{

const complex_t I{0, 1};

auto qlist = testing::Combine(
    testing::Values(cvector_t({1, 0, 0}), cvector_t({0, 1, 0}), cvector_t({0, 0, 1}),
                    cvector_t({1, 1, 0}), cvector_t({1, 0, 1}), cvector_t({0, 1, 1}),
                    cvector_t({0, .25, 1}), cvector_t({-.2, 0, 1}), cvector_t({.25, -.2, 1}),
                    cvector_t({1, 1, 1})),
    testing::Values(cvector_t({1, 0, 0}), cvector_t({0, 1, 0}), cvector_t({0, 0, 1}),
                    cvector_t({1, 1, 0}), cvector_t({1, 0, 1}), cvector_t({1, 0, 1}),
                    cvector_t({1, 1, 1})),
    testing::Values(1e-19, 1e-17, 1e-15, 1e-13, 1e-11, 1e-9, 1e-6, 1e-3, .03, 1., 1e1, 1e2, 1e3,
                    1e4),
    testing::Values(-1e-15, +1e-14, -1e-13 * I, -1e-11, 1e-9 * I, -1e-7, -1e-5 * I, 1e-3, +1e-2,
                    .1 + .1 * I, -.99 + .3 * I, .999, -.9999));

void run_test_for_many_q(std::function<void(cvector_t)> run_one_test, double qmag_min,
                         double qmag_max)
{
    ParamGenerator<std::tuple<cvector_t, cvector_t, double, complex_t>> gen = qlist;
    for (auto it : gen) {
        cvector_t qdir = std::get<0>(it);
        cvector_t qdev = std::get<1>(it);
        double qmag = std::get<2>(it);
        complex_t qeps = std::get<3>(it);
        const cvector_t q = qmag * (qdir + qeps * qdev).unit();

        if (q.mag() <= qmag_min || q.mag() >= qmag_max)
            continue;

        run_one_test(q);
    }
}

} // namespace formFactorTest
