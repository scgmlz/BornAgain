#include "Complex.h"
#include "Vectors3D.h"
#include <functional>

//! Facilities for FormFactorSpecializationTest and FormFactorSymmetryTest.

namespace formFactorTest
{
    void run_test_for_many_q(
        std::function<void(cvector_t)> run_one_test, double qmag_min, double qmag_max);
}
