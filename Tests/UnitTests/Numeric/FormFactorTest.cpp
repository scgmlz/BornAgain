#include "FormFactorTest.h"
#include "google_test.h" // tests segfault under Linux/clang-9.0.1 if this include is missing

namespace
{

const complex_t I{0, 1};

auto main_directions = {
    cvector_t({1, 0, 0}), cvector_t({0, 1, 0}), cvector_t({0, 0, 1}),
    cvector_t({1, 1, 0}), cvector_t({1, 0, 1}), cvector_t({0, 1, 1}),
    cvector_t({0, .25, 1}), cvector_t({-.2, 0, 1}), cvector_t({.25, -.2, 1}),
    cvector_t({1, 1, 1})};

auto deviation_directions = {
    cvector_t({1, 0, 0}), cvector_t({0, 1, 0}), cvector_t({0, 0, 1}),
    cvector_t({1, 1, 0}), cvector_t({1, 0, 1}), cvector_t({1, 0, 1}),
    cvector_t({1, 1, 1}) };

auto magnitudes = {
    1e-19, 1e-17, 1e-15, 1e-13, 1e-11, 1e-9, 1e-6, 1e-3, .03, 1., 1e1, 1e2, 1e3, 1e4};

auto relative_deviations = std::initializer_list<complex_t>{
    -1e-15, +1e-14, -1e-13 * I, -1e-11, 1e-9 * I, -1e-7, -1e-5 * I, 1e-3,
    +1e-2, .1+.1*I, -.99+.3*I, .999, -.9999};

} // namespace

void formFactorTest::run_test_for_many_q(
    std::function<void(cvector_t)> run_one_test, double qmag_min, double qmag_max)
{
    for (const cvector_t qdir : main_directions) {
        for (const cvector_t qdev : deviation_directions) {
            for (const double qmag : magnitudes) {
                for (const complex_t qeps : relative_deviations) {

                    const cvector_t q = qmag * (qdir + qeps * qdev).unit();

                    if (q.mag() <= qmag_min || q.mag() >= qmag_max)
                        continue;

                    run_one_test(q);
                }
            }
        }
    }
}
